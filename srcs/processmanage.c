/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processmanage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 13:30:25 by cbinet            #+#    #+#             */
/*   Updated: 2017/10/10 13:06:07 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
# include "opg.c"

size_t			*ft_getparamstype(t_cor *core, t_process *proc)
{
	size_t		*params;
	size_t		i;
	size_t		tmp;

	if (!(params = (size_t *)malloc(g_oplabel[core->arena[(proc->startpos + proc->PC) % MEM_SIZE] - 1] * sizeof(size_t))))
		exit(1);
	tmp = core->arena[(proc->startpos + proc->PC + 1) % MEM_SIZE];
	i = 0;
	while (tmp)
	{
		tmp /= 4;
		if (tmp % 4 == 1)
			params[i] = 1;
		else if (tmp % 4 == 3)
			params[i] = 2;
		else if (tmp % 4 == 2)
			params[i] = g_oplabel[core->arena[(proc->startpos + proc->PC) % MEM_SIZE] - 1];
		i++;
	}
	return (params);
}

static void		ft_executeprocess(t_cor *core, t_process *proc)
{
	bool	carry;

	ft_determinejmpdist(core, proc);
//	dispreg(proc);
	carry = proc->next_op(core, proc);
	dispreg(proc);
	if (g_opcarry[core->arena[(proc->startpos + proc->PC) % MEM_SIZE] - 1])
		proc->carry = carry;
//COMMENT SOPHIE ICI	core->arena_color[(proc->PC + proc->startpos) % MEM_SIZE] = 0; // need extracolor for pc
	core->arena_update[(proc->PC + proc->startpos) % MEM_SIZE] = UPDATE;
	proc->PC += proc->next_jump;
//COMMENT SOPHIE ICI	core->arena_color[(proc->PC + proc->startpos) % MEM_SIZE] = proc->color + 3; // need extracolor for pc
	core->arena_update[(proc->PC + proc->startpos) % MEM_SIZE] = UPDATE;
	proc->next_op = NULL;
}

// compare core->arena[proc->PC] with opc_table
void		ft_getop(t_cor *core, t_process *proc)
{

	if (core->arena[(proc->startpos + proc->PC) % MEM_SIZE] - 1 >= 0 && core->arena[(proc->startpos + proc->PC) % MEM_SIZE] - 1 < OPC_NBR)
	{
		proc->next_op = g_opctable[core->arena[(proc->startpos + proc->PC) % MEM_SIZE] - 1];
		proc->cycles_before_execute = g_optime[core->arena[(proc->startpos + proc->PC) % MEM_SIZE] - 1];
	}
	else
		proc->PC++;
}

void			ft_browseprocess(t_cor *core)
{
	t_process	*proc;

	proc = core->process;
	while (proc)
	{
		if (proc->cycles_before_execute == 0 && proc->next_op)
			ft_executeprocess(core, proc);
		if (!proc->next_op)
			ft_getop(core, proc);
		if (proc->cycles_before_execute > 0)
		proc->cycles_before_execute--;
		proc = proc->next;
	}
}


void	ft_delprocess(t_cor *core, t_process **del)
{
	t_process *tmp;
	if (core->process == (*del))
	{
		core->process = (*del)->next;
	}
	else
	{
		tmp = core->process;
		while (tmp->next != (*del))
			tmp = tmp->next;
		tmp->next = (*del)->next;
	}
	free((*del));
	*del = NULL;
}

