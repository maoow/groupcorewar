/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:25:09 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/29 16:05:48 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

static void		print_v4(t_process *proc, int adress, int adress2, size_t reg)
{
	int		adress3;

	adress3 = adress + adress2;
	ft_printf("P %4d | lldi %d %d r%d\n", proc->id, adress, adress2, reg);
	ft_printf("       | -> load from %d + %d = %d (",
			adress, adress2, adress3);
	ft_printf("with pc and mod %d)\n", adress3 + proc->pc + proc->startpos);
}

/*
** LLDI
**
** add first and second param and load it in the first param reg
*/

bool			cw_lldi(t_cor *core, t_process *proc)
{
	int			adress;
	int			adress2;
	int			adress3;
	size_t		reg;
	int			pos;

	pos = proc->pc + proc->startpos;
	reg = core->arena[(proc->pc + proc->startpos + proc->next_jump - 1)
		% MEM_SIZE];
	if (((core->arena[mod(pos + 1, MEM_SIZE)]) / 16) % 4 == 1 &&
			reg - 1 >= REG_NUMBER)
		return (proc->carry);
	adress = getparam(core, proc, 1, 2);
	adress2 = getparam(core, proc, 2, 2);
	adress3 = (adress + adress2);
	proc->registres[reg - 1] = getram(core, (adress3 + pos) % MEM_SIZE);
	if (core->options->v4)
		print_v4(proc, adress, adress2, reg);
	return (proc->registres[reg - 1] != 0);
}
