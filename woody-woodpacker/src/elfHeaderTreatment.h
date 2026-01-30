/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elfHeaderTreatment.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:09:40 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/30 12:01:30 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "programHeaders.h"
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct {
    unsigned char   elf_id[16]; // informacion basica en array de 16 (para parsear)
    __uint16_t      elf_type; // tipo de archivo ELF (ejecutable, shared, coredump)
    __uint16_t      elf_machine; // arquitectura (en mi caso solo 0x3E que referencia x86_64)
    __uint32_t      elf_ver; // version de ELF
    __uint64_t      elf_entrypoint; // direccion del punto de entrada del programa
    __uint64_t      elf_phoff; // diferencia positiva de bytes hasta la direccion de los headers del programa
    __uint64_t      elf_shoff; // diferencia positiva de bytes hasta la direccion de 
    __uint32_t      elf_flags; // flags especificos de arquitectura
    __uint16_t      elf_size; // tamanho del header (este)
    __uint16_t      elf_phentsize; // tamanho de cada program header
    __uint16_t      elf_phnum; // numero de program headers
    __uint16_t      elf_shentsize; // tamanho de cada section header
    __uint16_t      elf_shnum; //  numero de section headers
    __uint16_t      elf_shstrndx; // idx de la seccion de nombres de sh
}   elf64_header_map;
// structura para mapear el header de ELF

bool    elfhBasicChecks(void *map, off_t size);
bool    elfhFormatChecks(elf64_header_map *header, off_t size);
elf64_program_header_map    *findLoadExec(elf64_program_header_map *ph, size_t size);
elf64_program_header_map    *findLastLoad(elf64_program_header_map *ph, size_t size);
