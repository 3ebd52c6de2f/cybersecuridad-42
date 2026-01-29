/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:37:49 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/29 12:12:02 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "binaryTreatment.h"
# include "elfHeaderTreatment.h"
# include "programHeaders.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>

void    ft_error(int id, void *allocated) {
    if (id == 0) {
        printf("error: invalid file input.\n");
        exit(1);
    }
    if (id == 1) {
        perror("mmap failed");
        exit(1);
    }
    if (id == 2) {
        printf("error: invalid ELF64 format file.\n");
        exit(1);
    }
    if (id == 3) {
        printf("error: no executable LOAD segment found.\n");
        exit(1);
    }
    (void)allocated;
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

    __uint64_t    entrypoint = header->elf_entrypoint;
    elf64_program_header_map    *programHeaders = (__uint8_t *)map + header->elf_phoff;
    elf64_program_header_map    *executable = findLoadExec(programHeaders, header->elf_phnum);
    elf64_program_header_map    *lastLoad = findLastLoad(programHeaders, header->elf_phnum);
    if (!executable || !lastLoad){
        munmap(map, size);
        ft_error(3, NULL);
    }
    // aislo el entrypoint, los PH y el segmento LOAD que tenga permisos de ejecucion y el ultimo LOAD (despues ira mi injeccion)

    
    
    return (0);
}

/* FLUJO FUTURO 

+ parseao elf 
+ encontrar un LOAD con permisos de ejecucion
- encryptar .text
- inyectar el stub
- arreglar el entrypoint

*/