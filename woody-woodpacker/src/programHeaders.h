/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programHeaders.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:30:31 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/30 16:07:40 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "binaryTreatment.h"
# include <string.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

# define PT_NULL            0
# define PT_LOAD            1
# define PT_DYNAMIC         2
# define PT_INTERP          3
# define PT_NOTE            4
# define PT_PHDR            6

# define PF_X               0x1
# define PF_W               0x2
# define PF_R               0x4

# define PT_GNU_STACK       0x6474e551
# define PT_GNU_RELRO       0x6474e552
# define PT_GNU_EH_FRAME    0x6474e550
# define STUB_MAX_SIZE      0x1000

typedef struct {
    __uint32_t    ph_type; // tipo de segmento [LOAD, INTERP, DYNAMIC...]
    __uint32_t    ph_flags; // permisos del segmento [R, W, X]
    __uint64_t    ph_offset; // es la diferencia positiva a la direccion que tendre que cifrar
    __uint64_t    ph_vaddr; // direccion virtual donde el segmento se cargara en runtime
    __uint64_t    ph_paddr; // direccion fisica (no se usa)
    __uint64_t    ph_filesz; // tamanho del segmento en el archivo (para iterar al cifrar)
    __uint64_t    ph_memsz; // creo que el final de filesz pero es igual porque tengo el offsett
    __uint64_t    ph_align; // no lo termino de entender pero innecesario por ahora
}   elf64_program_header_map;
/* estructura que contiene cada uno de los program headers */

bool                        isLoadable(elf64_program_header_map *ph);
bool                        isReadable(elf64_program_header_map *ph);
bool                        isExecutable(elf64_program_header_map *ph);
bool                        isWritable(elf64_program_header_map *ph);
void                        stubSegmentInit(elf64_program_header_map *ptr, elf64_program_header_map *last);