/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:25:05 by cbinet            #+#    #+#             */
/*   Updated: 2017/10/30 13:57:50 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

static bool		regcheck(t_cor *core, t_process *proc)
{
	size_t op;
	size_t reg;

	op = core->arena[(proc->PC + proc->startpos + 1) % MEM_SIZE];
	if ((op / 4) % 4 == 1) // oui
	{
		if ((op / 16) % 4 == 1) // non
			reg = core->arena[(proc->PC + proc->startpos + 4) % MEM_SIZE] - 1;
		else
			reg = core->arena[(proc->PC + proc->startpos + 5) % MEM_SIZE] - 1;
		if (reg >= REG_NUMBER)
			return (false);
	}
	return (true);
}

bool	cw_ldi(t_cor *core, t_process *proc)
{
	int		adress;
	int		adress2;
	int		adress3;
	size_t		reg;

	reg = core->arena[(getparamplace(core, proc, 3, 2) - 1) % MEM_SIZE];
	//if (((core->arena[mod(proc->PC + proc->startpos + 1, MEM_SIZE)]) / 16) % 4 == 1)
		if (reg - 1 >= REG_NUMBER || !regcheck(core, proc))
			return (proc->carry);
	adress = getparam(core, proc, 1, 2);
	if (adress > 65536 / 2)
		adress -= 65536;
	adress2 = getparam(core, proc, 2, 2);
	if (adress2 > 65536 / 2)
		adress2 -= 65536;
adress3 = (adress + adress2) % IDX_MOD;
	proc->registres[reg - 1] = getram(core, (adress3 + proc->startpos + proc->PC) % MEM_SIZE);
	if (core->options->v4)
	{
		ft_printf("P%5d | ldi %d %d r%d\n", proc->ID, adress, adress2,
				reg);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
				adress, adress2, (adress + adress2),
				(adress3 + proc->PC + proc->startpos));
	}
	return (proc->registres[reg - 1] != 0);
}
