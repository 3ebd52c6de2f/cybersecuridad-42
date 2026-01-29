/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:15:41 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/29 16:17:36 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void printProgramHeaders(elf64_program_header_map *ph, size_t count) {
    size_t i;

    printf("\n================ PROGRAM HEADERS ================\n");
    printf("Idx  Type      Flags  Offset     Vaddr      Paddr      Filesz    Memsz     Align\n");
    printf("---- --------  -----  ---------  ---------  ---------  ---------  --------- --------\n");

    for (i = 0; i < count; i++)
    {
        printf("%-4zu ", i);

        /* -------- TYPE -------- */
        if (ph[i].ph_type == PT_LOAD)
            printf("%-8s ", "LOAD");
        else if (ph[i].ph_type == PT_DYNAMIC)
            printf("%-8s ", "DYNAMIC");
        else if (ph[i].ph_type == PT_INTERP)
            printf("%-8s ", "INTERP");
        else if (ph[i].ph_type == PT_PHDR)
            printf("%-8s ", "PHDR");
        else if (ph[i].ph_type == PT_NOTE)
            printf("%-8s ", "NOTE");
        else
            printf("%-8s ", "OTHER");

        /* -------- FLAGS -------- */
        printf("%c", (ph[i].ph_flags & PF_R) ? 'R' : '-');
        printf("%c", (ph[i].ph_flags & PF_W) ? 'W' : '-');
        printf("%c", (ph[i].ph_flags & PF_X) ? 'X' : '-');
        printf("  ");

        /* -------- ADDRESSES & SIZES -------- */
        printf("0x%07lx  ", ph[i].ph_offset);
        printf("0x%07lx  ", ph[i].ph_vaddr);
        printf("0x%07lx  ", ph[i].ph_paddr);
        printf("0x%07lx  ", ph[i].ph_filesz);
        printf("0x%07lx  ", ph[i].ph_memsz);
        printf("0x%lx\n",    ph[i].ph_align);
    }

    printf("=================================================\n\n");
}

void printSegment(const char *title, __uint8_t *ptr, size_t size) {
    size_t i;

    printf("\n=== %s ===\n", title);
    printf("Address: %p\n", ptr);
    printf("Size:    %zu bytes\n\n", size);

    for (i = 0; i < size && i < 128; i++) { // limitamos a 128 bytes
        if (i % 16 == 0)
            printf("%08zx  ", i);
        printf("%02x ", ptr[i]);
        if (i % 16 == 15)
            printf("\n");
    }

    if (i % 16 != 0)
        printf("\n");

    if (size > 128)
        printf("... (%zu bytes more)\n", size - 128);
}