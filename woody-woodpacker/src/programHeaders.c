/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programHeaders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:30:03 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/30 16:15:59 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "elfHeaderTreatment.h"
#include "programHeaders.h"

static inline off_t align(off_t v, off_t a) {
    return (v + a - 1) & ~(a - 1);
}

void    stubSegmentInit(elf64_program_header_map *ptr, elf64_program_header_map *last) {
    ptr->ph_type = PT_LOAD; // tipo load
    ptr->ph_flags = PF_R | PF_X; // permisos a full
    ptr->ph_align = 0x1000;
    
    off_t firstFreeValue = last->ph_offset + last->ph_filesz;
    
    ptr->ph_offset = align(firstFreeValue, 0x1000);
    ptr->ph_vaddr = align(last->ph_vaddr + last->ph_memsz, 0x1000);
    // el offset indica distancia al segmento y vaddr es la direccion virtual del nuevo

    ptr->ph_paddr = ptr->ph_vaddr; // dir fisica (irrelevante)
    ptr->ph_filesz = STUB_MAX_SIZE;
    ptr->ph_memsz = STUB_MAX_SIZE;
}

bool    isLoadable(elf64_program_header_map *ph) {
    return (ph->ph_type == PT_LOAD);
}

bool    isExecutable(elf64_program_header_map *ph) {
    return (ph->ph_flags & PF_X);
}

bool    isWritable(elf64_program_header_map *ph) {
    return (ph->ph_flags & PF_W);
}

bool    isReadable(elf64_program_header_map *ph) {
    return (ph->ph_flags & PF_R);
}
