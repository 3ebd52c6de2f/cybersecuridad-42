/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stubTreatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:37:10 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/30 16:08:22 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stubTreatment.h"

void    stubInternalMod(__uint8_t *stubPtr, elf64_program_header_map *exec, elf64_program_header_map *stubSeg, __uint64_t og_entrypoint, const __uint8_t *key, size_t keylen) {
    // dir del texto cifrado y tamanho
    *(__uint64_t *)(stubPtr + STUB_TEXT_ADDR_OFFSET) = exec->ph_vaddr;
    *(__uint64_t *)(stubPtr + STUB_TEXT_SIZE_OFFSET) = exec->ph_filesz;
    
    // introducir mi SecretKey, su direccion virtual y size
    __uint8_t   *keyDist = stubPtr + stubSeg->ph_filesz;
    memcpy(keyDist, key, keylen);
    *(__uint64_t *)(stubPtr + STUB_KEY_ADDR_OFFSET) = stubSeg->ph_vaddr + stubSeg->ph_filesz;
    *(__uint64_t *)(stubPtr + STUB_KEY_LEN_OFFSET) = keylen;

    // introducir entrypoint original
    *(__uint64_t *)(stubPtr + STUB_ENTRYPOINT_OFFSET) = og_entrypoint;

    // actualizar variables de program headers
    stubSeg->ph_filesz += keylen;
    stubSeg->ph_memsz += keylen;
}

size_t    loadStub(__uint8_t *dist, char *path, void *map, off_t maplen) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        munmap(map, maplen);
        ft_error(4, NULL);
    }

    off_t   size = lseek(fd, 0, SEEK_END);
    if (size <= 0) {
        munmap(map, maplen);
        ft_error(5, NULL);
    }
    lseek(fd, 0, SEEK_SET);

    __uint8_t *buffer = malloc(size);
    if (!buffer || read(fd, buffer, size) != size) {
        munmap(map, maplen);
        ft_error(6, NULL);
    }
    memcpy(dist, buffer, size);
    // compruebo que la carga del archivo no falle y la copio
    // sobre la dir apuntada por el nuevo segmento

    close(fd);
    free(buffer);
    return (size);
}
