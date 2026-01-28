/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:37:49 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/28 14:28:37 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/mman.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include "fileTreatment.h"

void    ft_error(int id, void *allocated) {
    if (id == 0) {
        printf("runtime error: invalid input.\n");
        exit(1);
    }
    if (id == 1) {
        perror("mmap failed");
        exit(1);
    }
}

int main(int argc, char **argv) {
    if (argc != 2 || !formatCheck(argv[1]))
        ft_error(0, NULL);
    
    void    *map = readFile(argv[1]);
    if (map == NULL)
        ft_error(1, NULL);
    
    // comprobar formato ELF64
    // comprobar clase 64 bits
    // leer el entrypoint
    return (0);
}