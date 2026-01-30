/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:37:49 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/30 16:46:31 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "stubTreatment.h"
# include "binaryTreatment.h"
# include "elfHeaderTreatment.h"
# include "programHeaders.h"
# include "debug.h"
# include "criptography.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>

static void exportWoody(void *map, off_t mapsize) {
    int fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 0755);
    if (fd < 0) {
        munmap(map, mapsize);
        close(fd);
        ft_error(7, NULL);
    }
    if (write(fd, map, mapsize) != mapsize) {
        munmap(map, mapsize);
        close(fd);
        ft_error(8, NULL);
    }
    close(fd);
}

int main(int argc, char **argv) {
    if (argc != 2 || !binaryFormatChecks(argv[1]))
        ft_error(0, NULL);
    
    void    *map = readFile(argv[1]); // mmap
    off_t   size = fileSize(argv[1]); // tamanho de mmap
    if (map == NULL)
        ft_error(1, NULL);
    if (!elfhBasicChecks(map, size) || (long)size < (long)sizeof(elf64_header_map)) // formato de elfh
        ft_error(2, NULL);
    // compruebo input y lo mapeo
    
    elf64_header_map    *header = (elf64_header_map *)map;
    elfhFormatChecks(header, size);
    // extraigo el header de ELF y le hago un chikiparse
    
    elf64_program_header_map    *programHeaders = (elf64_program_header_map *)((__uint8_t *)map + header->elf_phoff);
    elf64_program_header_map    *executable = findLoadExec(programHeaders, header->elf_phnum);
    elf64_program_header_map    *lastLoad = findLastLoad(programHeaders, header->elf_phnum);
    if (!executable || !lastLoad){
        munmap(map, size);
        ft_error(3, NULL);
    }
    // aislo los PH y el segmento LOAD que tenga permisos de ejecucion y el ultimo LOAD (despues ira mi injeccion)
    
    __uint64_t og_entrypoint = header->elf_entrypoint;
    __uint8_t   *initExecPtr = (__uint8_t *)map + executable->ph_offset;
    size_t      iepSize = executable->ph_filesz;
    // busco el primer byte ejecutable y el tamanho del segmento
    
    const __uint8_t *key = (const __uint8_t *)"patata";
    rc4cript(initExecPtr, iepSize, key, 6);
    // cifro el segmento
    
    elf64_program_header_map *stubSegment = &programHeaders[header->elf_phnum];
    stubSegmentInit(stubSegment, lastLoad);
    header->elf_phnum += 1;
    // genero un nuevo segmento al final de los programHeaders
    // de tipo LOAD con permisos y redirigo el entrypoint a este (stub)

    __uint8_t   *stubDist = (__uint8_t *)map + stubSegment->ph_offset;
    size_t  stubSize = loadStub(stubDist, "src/stub.bin", map, size);
    (void)stubSize;
    // cargo el stub RAW
    stubInternalMod(stubDist, executable, stubSegment, og_entrypoint, key, 6);
    // reemplazo variables del STUB con mi SKey y con el entrypoint correcto

    exportWoody(map, size);
    return (0);
}

/* Funcionamiento de "woody" (mi export)

    - entrypoint apunta al STUB
    - el STUB imprime ....WOODY....
    - el STUB descifra el contenido cifrado (antiguo codigo ejec)
    - el STUB redirige el entrypoint al entrypoint original (example)
    
    Dando como resultado un archivo cifrado hasta el momento
    de su ejecucion con un mensaje
*/
