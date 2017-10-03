/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:25:05 by cbinet            #+#    #+#             */
/*   Updated: 2017/10/03 21:32:58 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

bool	cw_ldi(t_cor *core, t_process *proc)
{
	int adress;
	int adress2;

	adress = getparam(core, proc, 1, 2);
	adress2 = getparam(core, proc, 2, 2);
	proc->registres[core->arena[getparamplace(core, proc, 3, 2) % MEM_SIZE]] =
	getram(core, idx(proc, adress));
	if (core->options->v4)
		ft_printf("P%5d | ldi %d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %d)\n",
			  	proc->ID, adress - 201363497, adress2, core->arena[getparamplace(core, proc, 3, 2) % MEM_SIZE],
				adress - 201363497, adress2, (adress + adress2) - 201363497,(adress + adress2 + proc->PC + proc->startpos) % MEM_SIZE);
//		exit(0);

	return (proc->registres[core->arena[(getparamplace(core, proc, 3, 2)) % MEM_SIZE]] != 0);
}
