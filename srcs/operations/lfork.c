/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:25:06 by cbinet            #+#    #+#             */
/*   Updated: 2017/10/18 18:04:15 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

static void			fulfill_tmp(t_cor *core, t_process *tmp, t_process *proc)
{
	tmp->next_jump = 0;
	tmp->next_op = NULL;
	ft_getop(core, tmp);
	tmp->cycles_before_execute--;
	tmp->carry = proc->carry;
	tmp->live = proc->live;
	tmp->color = proc->color;
	tmp->ID = core->process->ID + 1;
	tmp->next = core->process;
	core->process = tmp;
}

bool				cw_lfork(t_cor *core, t_process *proc)
{
	t_process	*tmp;
	size_t		i;
	int			indt;

	i = 0;
	if (!(tmp = (t_process *)malloc(sizeof(t_process))))
		write_error(2);
	while (i < REG_NUMBER)
	{
		tmp->registres[i] = proc->registres[i];
		i++;
	}
	tmp->PC = 0;
	tmp->startpos = ind(core, proc, proc->PC + 1) % MEM_SIZE;
	fulfill_tmp(core, tmp, proc);
	if (core->options->v4)
	{
		indt = ind(core, proc, proc->PC + 1) % MEM_SIZE;
		if (indt > MEM_SIZE / 2)
			indt -= MEM_SIZE;
		ft_printf("P%5d | fork %d (%d)\n", proc->ID, indt,
				idx(proc, ind(core, proc, proc->PC + 1)));
	}
	return (true);
}
