/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaryTreatment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:57:19 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/30 16:22:51 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binaryTreatment.h"

void    *readFile(char *path) {
    int     fd = open(path, O_RDONLY);

    off_t   size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    void    *map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    /* las flags hacen referencia a la capacidad de leer/escribir sobre el archivo
    y el private marca que no se modificara el archivo original */
    if (map == MAP_FAILED) {
        close(fd);
        return NULL;
    }
    close(fd);

    return (map);
}

/* lo primero que he de hacer es cargar el archivo
para lo cual usare mmap, un mapa simple el cual necesita
de un fileDescriptor con el archivo abierto y su tamanho */

bool    binaryFormatChecks(char *path) {
    int fd = open(path, O_RDWR);
    if (fd < 0) {
        return false;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    if (size <= 0) {
        close(fd);
        return false;
    }

    close(fd);
    return true;
}
/* para separar errores mas que nada entre invalid input
y fallo de la funcion mmap, primero compruebo que el archivo
sea legible y medible */

off_t   fileSize(char *path) {
    int fd = open(path, O_RDONLY);
    off_t   size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    return (size);
}
/* no hay otra que extraer el size del file descriptor, necesario
para liberar memoria del mapa */

void    ft_error(int id, void *allocated) {
    if (id == 0)
        printf("error: invalid file input.\n");
    if (id == 1)
        perror("mmap failed");
    if (id == 2)
        printf("error: invalid ELF64 format file.\n");
    if (id == 3)
        printf("error: no executable LOAD segment found.\n");
    if (id == 4)
        printf("error: unable to open stub.bin.\n");
    if (id == 5)
        printf("error: void stub.bin.\n");
    if (id == 6)
        printf("error: unable to read stub.bin.\n");
    if (id == 7)
        printf("error: can't create 'woody' file.\n");
    if (id == 8)
        printf("error: can't write on 'woody' file.\n");
    exit(1);
    (void)allocated;
}
// error handler