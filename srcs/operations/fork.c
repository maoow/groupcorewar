/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:25:02 by cbinet            #+#    #+#             */
/*   Updated: 2017/08/10 15:00:09 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

bool	fork(t_cor *core, t_process *proc)
{
	t_process 	*tmp;
	size_t		i;

	i = 0;
	tmp = (t_process *)malloc(sizeof(t_process)); //
	while (i < REG_NUMBER)
	{
		tmp->registres[i] = proc->registres[i];
		i++;
	}
	tmp->PC = (proc->PC - proc->startpos + idx(core, ind(proc, proc->PC + 1))) % MEM_SIZE;
	tmp->startpos = proc->startpos;
	tmp->next_jump = 0;
	tmp->cycles_before_execute = 0;
	tmp->next_jump = NULL;
	tmp->carry = proc->carry;
	tmp->live = proc->live;
	tmp->next = NULL; // todo (voir comment on gere la pile)
	return (true);
}
