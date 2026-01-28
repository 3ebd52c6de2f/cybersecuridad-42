/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:37:49 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/28 18:00:07 by adlopez-         ###   ########.fr       */
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

void printAll(elf64_header_map *header, elf64_program_header_map *phs)
{
    int i;
    printf("========== ELF64 HEADER ==========\n");
    printf("Magic: %02x %02x %02x %02x\n",
           header->elf_id[0],
           header->elf_id[1],
           header->elf_id[2],
           header->elf_id[3]);

    printf("Class:            %s\n",
           header->elf_id[4] == 2 ? "ELF64" : "Not ELF64");

    printf("Endian:           %s\n",
           header->elf_id[5] == 1 ? "Little Endian" : "Big Endian");

    printf("Type:             0x%x\n", header->elf_type);
    printf("Machine:          0x%x\n", header->elf_machine);
    printf("Version:          0x%x\n", header->elf_ver);
    printf("Entry point:      0x%lx\n", header->elf_entrypoint);
    printf("PH offset:        %lu\n", header->elf_phoff);
    printf("PH entry size:    %u\n", header->elf_phentsize);
    printf("PH number:        %u\n", header->elf_phnum);
    printf("\n========== PROGRAM HEADERS ==========\n");

    for (i = 0; i < header->elf_phnum; i++)
    {
        printf("\n-- Program Header %d --\n", i);

        printf("Type:    0x%x", phs[i].ph_type);
        if (phs[i].ph_type == 1)
            printf(" (PT_LOAD)");
        else if (phs[i].ph_type == 2)
            printf(" (PT_DYNAMIC)");
        else if (phs[i].ph_type == 3)
            printf(" (PT_INTERP)");
        else
            printf(" (OTHER)");
        printf("\n");

        printf("Offset:  0x%lx\n", phs[i].ph_offset);
        printf("Vaddr:   0x%lx\n", phs[i].ph_vaddr);
        printf("Filesz:  0x%lx\n", phs[i].ph_filesz);
        printf("Memsz:   0x%lx\n", phs[i].ph_memsz);
        printf("Align:   0x%lx\n", phs[i].ph_align);

        printf("Flags:   ");
        if (phs[i].ph_flags & 0x4) printf("R ");
        if (phs[i].ph_flags & 0x2) printf("W ");
        if (phs[i].ph_flags & 0x1) printf("X ");
        printf("\n");
    }
}
// # chat # gpt

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
    (void)allocated;
}

int main(int argc, char **argv) {
    if (argc != 2 || !binaryFormatChecks(argv[1]))
        ft_error(0, NULL);
    
    void    *map = readFile(argv[1]); //mmap
    off_t   size = fileSize(argv[1]); // tamanho de mmap
    if (map == NULL)
        ft_error(1, NULL);
    if (!elfhBasicChecks(map, size) || (long)size < (long)sizeof(elf64_header_map)) // formato de elfh
        ft_error(2, NULL);
    
    elf64_header_map    *header = (elf64_header_map *)map;
    elfhFormatChecks(header, size);

    __uint64_t    entrypoint = header->elf_entrypoint;
    printf("entrypoint: %lu\n", entrypoint);
    elf64_program_header_map *programHeaders = (elf64_program_header_map *)(map + header->elf_phoff);
    
    printAll(header, programHeaders);

    return (0);
}