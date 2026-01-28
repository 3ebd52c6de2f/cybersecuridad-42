/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elfHeaderTreatment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:09:17 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/28 18:04:29 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elfHeaderTreatment.h"

bool    elfhBasicChecks(void *map, off_t size) {
    unsigned char *chamanism = (unsigned char *)map;

    if (chamanism[0] != 0x7f || chamanism[1] != 'E' || \
            chamanism[2] != 'L' || chamanism[3] != 'F' || chamanism[4] != 2) {
        munmap(map, size);
        return false;
    }
    return true;
}
/*  antes de asignar el mmap a la estructura ordenada voy a comprobar
que el formato de ELF sea correcto para evitar segfault */

bool    elfhFormatChecks(elf64_header_map *header, off_t size) {
    if (header->elf_machine != 0x3E) {
        printf("error: only x86_64 architecture supported\n");
        munmap(header, size);
        exit(1);
    }
    if (header->elf_type != 2 && header->elf_type != 3) {
        printf("error: only executable files supported\n");
        munmap(header, size);
        exit(1);
    }
    if ((long)(header->elf_phoff + (header->elf_phnum * sizeof(elf64_program_header_map))) > (long)size) {
        printf("error: program headers out of range\n");
        munmap(header, size);
        exit(1);
    }
    return true;
}