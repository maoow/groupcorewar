/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:25:13 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/28 12:53:54 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

/*
** XOR
**
** store in the third reg the result of a logical xor of the other two,
** carry go true if the result is equal to zero
*/

static size_t	xor(size_t a, size_t b)
{
	size_t		out;
	uintmax_t	place;

	place = 1;
	out = 0;
	while (place <= 4294967295)
	{
		if (((a / place) % 2 || (b / place) % 2) &&
				!((a / place) % 2 && (b / place) % 2))
			out += place;
		place *= 2;
	}
	return (out);
}

bool			cw_xor(t_cor *core, t_process *proc)
{
	size_t	a;
	size_t	b;
	size_t	c;

	a = getparam(core, proc, 1, 4);
	b = getparam(core, proc, 2, 4);
	c = core->arena[(proc->pc + proc->startpos + proc->next_jump - 1)
		% MEM_SIZE] - 1;
	if (c >= REG_NUMBER || core->error)
	{
		core->error = false;
		return (proc->carry);
	}
	proc->registres[c] = xor(a, b);
	if (core->options->v4)
		ft_printf("P %4d | xor %d %d r%d\n", proc->id, a, b, c + 1);
	return (proc->registres[c] == 0);
}
