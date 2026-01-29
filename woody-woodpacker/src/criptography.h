/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   criptography.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:37:19 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/29 16:37:21 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <sys/mman.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <stdlib.h>

void    rc4cript(__uint8_t *initialPtr, size_t size, const __uint8_t secretKey[], size_t keylen);