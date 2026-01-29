/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:37:49 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/29 16:38:17 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

    __uint64_t    og_entrypoint = header->elf_entrypoint;
    elf64_program_header_map    *programHeaders = (elf64_program_header_map *)((__uint8_t *)map + header->elf_phoff);
    elf64_program_header_map    *executable = findLoadExec(programHeaders, header->elf_phnum);
    elf64_program_header_map    *lastLoad = findLastLoad(programHeaders, header->elf_phnum);
    if (!executable || !lastLoad){
        munmap(map, size);
        ft_error(3, NULL);
    }
    // aislo el entrypoint, los PH y el segmento LOAD que tenga permisos de ejecucion y el ultimo LOAD (despues ira mi injeccion)

    __uint8_t   *initExecPtr = (__uint8_t *)map + executable->ph_offset;
    size_t      iepSize = executable->ph_filesz;
    // busco el primer byte ejecutable y el tamanho del segmento
    
    printSegment("SEGMENTO ANTES", initExecPtr, iepSize);

    const __uint8_t *key = (const __uint8_t *)"patata";
    rc4cript(initExecPtr, iepSize, key, 6);
    // cifro el segmento

    printSegment("SEGMENTO DESPUES", initExecPtr, iepSize);

    // stub cosas


    (void)og_entrypoint;

    return (0);
}

/* FLUJO FUTURO 

+ parseao elf 
+ encontrar un LOAD con permisos de ejecucion
- encryptar .text RC4
- inyectar el stub
- arreglar el entrypoint


RC4 es un algoritmo simetrico (misma funcion para ambos sentidos)
utiliza un array de 256 bytes y 2 index
*/