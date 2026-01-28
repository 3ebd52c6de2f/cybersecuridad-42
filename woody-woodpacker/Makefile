# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/28 13:35:18 by adlopez-          #+#    #+#              #
#    Updated: 2026/01/28 18:01:31 by adlopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	src/main.c src/programHeaders.c src/elfHeaderTreatment.c src/binaryTreatment.c
NAME	=	woody_woodpacker

sample:
	gcc src/sample.c -o example
# sin flags genera el formato deseado
# (ELF64 dinamico por defecto x84_64 Linux)

packer:
	gcc -Wall -Werror -Wextra -std=gnu99 -g ${SRCS} -o ${NAME}

clean:
	rm -rf example