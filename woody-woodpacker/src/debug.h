/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:15:53 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/29 16:17:32 by adlopez-         ###   ########.fr       */
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

void printProgramHeaders(elf64_program_header_map *ph, size_t count);
void printSegment(const char *title, __uint8_t *ptr, size_t size);