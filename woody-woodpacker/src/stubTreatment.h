/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stubTreatment.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:37:24 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/30 16:14:41 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "elfHeaderTreatment.h"
# include "programHeaders.h"
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define STUB_ENTRYPOINT_OFFSET  0x148
# define STUB_TEXT_ADDR_OFFSET 0x128
# define STUB_TEXT_SIZE_OFFSET 0x130
# define STUB_KEY_ADDR_OFFSET 0x138
# define STUB_KEY_LEN_OFFSET 0x140

// hardcode inspeccionando el stub.bin
// he buscado el lugar donde declaro el entrypoint
// para reemplazarlo desde dentro del programa

size_t                      loadStub(__uint8_t *dist, char *path, void *map, off_t maplen);
void                        stubInternalMod(__uint8_t *stubPtr, elf64_program_header_map *exec, elf64_program_header_map *stubSeg, __uint64_t og_entrypoint, const __uint8_t *key, size_t keylen);