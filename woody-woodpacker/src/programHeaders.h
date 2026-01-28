/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programHeaders.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:30:31 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/28 17:54:24 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct {
    __uint32_t    ph_type; // tipo de segmento [LOAD, INTERP, DYNAMIC...]
    __uint32_t    ph_flags; // permisos del segmento [R, W, X]
    __uint64_t    ph_offset; // es la diferencia positiva a la direccion que tendre que cifrar
    __uint64_t    ph_vaddr; // direccion virtual donde el segmento se cargara en runtime
    __uint64_t    ph_paddr; // direccion fisica (no se usa)
    __uint64_t    ph_filesz; // tamanho del segmento en el archivo (para iterar al cifrar)
    __uint64_t    ph_memsz; // limite para cifrar
    __uint64_t    ph_align; // no lo termino de entender pero innecesario por ahora
}   elf64_program_header_map;
/* estructura que contiene cada uno de los program headers */
