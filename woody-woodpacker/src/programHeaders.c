/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programHeaders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlopez- <adloprub004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:30:03 by adlopez-          #+#    #+#             */
/*   Updated: 2026/01/29 12:12:03 by adlopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "programHeaders.h"

bool    isLoadable(elf64_program_header_map *ph) {
    return (ph->ph_type == PT_LOAD);
}

bool    isExecutable(elf64_program_header_map *ph) {
    return (ph->ph_flags & PF_X);
}

bool    isWritable(elf64_program_header_map *ph) {
    return (ph->ph_flags & PF_W);
}

bool    isReadable(elf64_program_header_map *ph) {
    return (ph->ph_flags & PF_R);
}