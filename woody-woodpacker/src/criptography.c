/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   criptography.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:37:30 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/29 16:38:41 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "criptography.h"

void    rc4cript(__uint8_t *initialPtr, size_t size, const __uint8_t secretKey[], size_t keylen) {
    __uint8_t   S[256];
    __uint8_t   idx;
    __uint8_t   idy;
    __uint8_t   temp;

    for (size_t id = 0; id != 256; id++)
        S[id] = id;
    // inicio S con [1, 2, 3, 4... a 256]
    
    for (size_t id = 0; id != 256; id++) {
        idx = idx + S[id] + secretKey[id %  keylen];

        temp = S[id];
        S[id] = S[idx];
        S[idx] = temp;
    }
    // lo mezclo con "patata"

    idx = 0;
    for (size_t id = 0; id < size; id++) {
        idx++;
        idy = idy + S[idx];

        temp = S[idx];
        S[idx] = S[idy];
        S[idy] = temp;

        __uint8_t   random = S[(S[idx] + S[idy]) % 0xff];
        initialPtr[id] ^= random;
    }

}