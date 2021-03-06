/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:25:01 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/29 11:53:19 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

/*
** AND
**
** store in the third reg the result of a logical and of the other two,
** carry go true if the result is equal to zero
*/

static size_t	and(size_t a, size_t b)
{
	size_t	out;
	size_t	place;

	place = 1;
	out = 0;
	while (place <= 4294967295)
	{
		if ((a / place) % 2 && (b / place) % 2)
			out += place;
		place *= 2;
	}
	return (out);
}

bool			cw_and(t_cor *core, t_process *proc)
{
	size_t	a;
	size_t	b;
	size_t	c;
	int		pos;

	a = getparam(core, proc, 1, 2);
	b = getparam(core, proc, 2, 2);
	pos = (proc->pc + proc->startpos + proc->next_jump - 1) % MEM_SIZE;
	c = core->arena[pos] - 1;
	if (c >= REG_NUMBER)
		return (proc->carry);
	proc->registres[c] = and(a, b);
	if (core->options->v4)
		ft_printf("P %4d | and %d %d r%d\n", proc->id, a, b, c + 1);
	return (proc->registres[c] == 0);
}
