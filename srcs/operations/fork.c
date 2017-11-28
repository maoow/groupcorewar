/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:25:02 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/28 12:53:54 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

/*
** FORK
**
** make a perfect copy of the proc and place it on the given adress (%idx)
*/

static void			fulfill_tmp(t_cor *core, t_process *tmp, t_process *proc)
{
	tmp->next_jump = 0;
	tmp->next_op = NULL;
	tmp->just_played = false;
	tmp->searching = false;
	tmp->buffc = 0;
	tmp->carry = proc->carry;
	tmp->live = proc->live;
	tmp->color = proc->color;
	tmp->id = core->procnb + 1;
	core->procnb++;
	tmp->next = core->process;
	core->process = tmp;
}

bool				cw_fork(t_cor *core, t_process *proc)
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
	tmp->pc = 0;
	tmp->startpos = (idx(proc, ind(core, proc, proc->pc + 1))) % MEM_SIZE;
	fulfill_tmp(core, tmp, proc);
	if (core->options->v4)
	{
		indt = ind(core, proc, proc->pc + 1);
		ft_printf("P %4d | fork %d (%d)\n", proc->id, indt,
				idx(proc, ind(core, proc, proc->pc + 1)));
	}
	return (true);
}
