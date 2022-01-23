/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jz_salloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzoltan <jzoltan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 02:04:18 by jzoltan           #+#    #+#             */
/*   Updated: 2022/01/23 03:11:47 by jzoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JZ_SALLOC_H
# define JZ_SALLOC_H

# ifndef JZ_SALLOC_SIZE
#  define JZ_SALLOC_SIZE 409600
# endif
# include <unistd.h>

void			*jz_salloc(size_t size);
void			jz_salloc_free(void *block);

#endif
