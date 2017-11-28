/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ramfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:10:18 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/28 12:53:55 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

long int			getram(t_cor *core, size_t address)
{
	long int	value;

	address %= MEM_SIZE;
	value = core->arena[(address) % MEM_SIZE];
	value *= 256;
	value += core->arena[(address + 1) % MEM_SIZE];
	value *= 256;
	value += core->arena[(address + 2) % MEM_SIZE];
	value *= 256;
	value += core->arena[(address + 3) % MEM_SIZE];
	if (value > 4294967296 / 2)
		value -= 4294967296;
	return (value);
}

void				setram(t_cor *core, size_t address, int val, int color)
{
	long int value;

	value = val % 4294967296;
	if (value < 0)
		value += 4294967296;
	core->arena[(address + 3) % MEM_SIZE] = value % 256;
	core->arena_color[(address + 3) % MEM_SIZE] = color;
	core->arena_update[(address + 3) % MEM_SIZE] = UPDATE;
	value /= 256;
	core->arena[(address + 2) % MEM_SIZE] = value % 256;
	core->arena_color[(address + 2) % MEM_SIZE] = color;
	core->arena_update[(address + 2) % MEM_SIZE] = UPDATE;
	value /= 256;
	core->arena[(address + 1) % MEM_SIZE] = value % 256;
	core->arena_color[(address + 1) % MEM_SIZE] = color;
	core->arena_update[(address + 1) % MEM_SIZE] = UPDATE;
	value /= 256;
	core->arena[address % MEM_SIZE] = value;
	core->arena_update[address % MEM_SIZE] = UPDATE;
	core->arena_color[address % MEM_SIZE] = color;
}
