/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jz_salloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzoltan <jzoltan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 00:11:26 by jzoltan           #+#    #+#             */
/*   Updated: 2022/01/23 02:53:52 by jzoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jz_salloc.h"

char	*jz_salloc_raw_memory(void)
{
	static char	memory[JZ_SALLOC_SIZE] = {0};

	return (memory);
}

static int	jz_salloc_try(char *block, char *next, size_t size)
{
	if (!next)
	{
		*block = 1;
		++block;
		next = block + size + sizeof(char *);
		*(char **)(block) = next;
		*next = 0;
		*(char **)(next + 1) = 0;
		return (1);
	}
	else if ((size_t)next - (size_t)block > size + sizeof(size_t) * 2 + 1)
	{
		*block = 1;
		++block;
		*(char **)(block) = block + size + sizeof(char *);
		if (*(size_t *)block < (size_t)next)
		{
			block = *(char **)(block);
			*block = 0;
			*(char **)(block + 1) = next;
		}
		return (1);
	}
	return (0);
}

void	*jz_salloc(size_t size)
{
	char *const	block_end = jz_salloc_raw_memory() + JZ_SALLOC_SIZE;
	char		*block;
	char		*next;

	block = jz_salloc_raw_memory();
	while (block && block < block_end)
	{
		while (block < block_end && *block)
			block = *((char **)(&(block[1])));
		if (block + (size + sizeof(char *) + sizeof(char)) >= block_end)
			return (0);
		jz_salloc_free(block + sizeof(size_t) + 1);
		next = (*(char **)(block + 1));
		if (jz_salloc_try(block, next, size))
			return ((size_t *)(block + 1) + 1);
		else
			block = *((char **)(&(block[1])));
	}
	return (0);
}

void	jz_salloc_free(void *block_)
{
	char *const	block_end = jz_salloc_raw_memory() + JZ_SALLOC_SIZE;
	char		*block;
	char		**next_block;

	block = block_;
	if (!block)
		return ;
	block -= 9;
	*block = 0;
	next_block = (char **)(block + 1);
	while (block && block < block_end && !*block)
		block = *((char **)(&(block[1])));
	*next_block = block;
}
