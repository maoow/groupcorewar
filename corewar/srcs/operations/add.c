/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:24:58 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/29 11:52:42 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

/*
** ADD
**
** store in the third reg the sum of the other two,
** carry go true if the result is equal to zero
*/

bool		cw_add(t_cor *core, t_process *proc)
{
	size_t			r1;
	size_t			r2;
	size_t			r3;
	long			value;

	r1 = core->arena[(proc->pc + proc->startpos + 2) % MEM_SIZE] - 1;
	r2 = core->arena[(proc->pc + proc->startpos + 3) % MEM_SIZE] - 1;
	r3 = core->arena[(proc->pc + proc->startpos + 4) % MEM_SIZE] - 1;
	if (r3 < REG_NUMBER && r1 < REG_NUMBER && r2 < REG_NUMBER)
	{
		value = ((long)proc->registres[r1] + (long)proc->registres[r2]);
		if (value > 4294967296 / 2)
		{
			value -= 4294967296;
		}
		proc->registres[r3] = value;
		if (core->options->v4)
		{
			ft_printf("P %4d | add r%d", proc->id, r1 + 1);
			ft_printf(" r%d r%d\n", r2 + 1, r3 + 1);
		}
		return (proc->registres[r3] == 0);
	}
	return (proc->carry);
}
