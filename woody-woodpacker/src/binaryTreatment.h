/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaryTreatment.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:57:41 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/29 12:12:11 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <sys/mman.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <stdbool.h>

void    *readFile(char *argv);
bool    binaryFormatChecks(char *argv);
off_t   fileSize(char *path);
bool    basicChecks(void *map, off_t size);
