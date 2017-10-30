/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:25:13 by cbinet            #+#    #+#             */
/*   Updated: 2017/10/30 14:33:43 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

bool	cw_sub(t_cor *core, t_process *proc)
{
	size_t			r1;
	size_t			r2;
	size_t			r3;
	r1 = core->arena[(proc->PC + proc->startpos + 2) % MEM_SIZE] - 1;
	r2 = core->arena[(proc->PC + proc->startpos + 3) % MEM_SIZE] - 1;
	r3 = core->arena[(proc->PC + proc->startpos + 4) % MEM_SIZE] - 1;
	if (r3 < REG_NUMBER && r1 < REG_NUMBER && r2 < REG_NUMBER)
	{
		proc->registres[r3] = proc->registres[r1] - proc->registres[r2];
		if (core->options->v4)
			ft_printf("P%5d | add r%d r%d r%d\n", proc->ID, r3 + 1, r2 + 1, r1 + 1);
		return (proc->registres[r3] == 0);
	}
	return (proc->carry);
}
