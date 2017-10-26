/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:06:40 by cbinet            #+#    #+#             */
/*   Updated: 2017/10/26 15:46:48 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
size_t					g_oplabel[OPC_NBR] = {
	4,
	4,
	0,
	0,
	0,
	4,
	4,
	4,
	2,
	2,
	2,
	2,
	4,
	2,
	2,
	0
};

long int	idx(t_process *proc, long int jump)
{
	long int	tmp;

	//ft_printf(" %d %d  ", jump, IDX_MOD);
	if (jump > MEM_SIZE / 2 && jump % IDX_MOD != 0)
		tmp = (jump % IDX_MOD) + proc->PC - IDX_MOD;
	else
		tmp = (jump % IDX_MOD) + proc->PC;
	//ft_printf(" %d %d  ", tmp, IDX_MOD);
	return (((tmp + proc->startpos) % MEM_SIZE));
}

void	dispjump(t_cor *core, t_process *proc)
{
	size_t		i;
	size_t		start;

	if (proc->next_jump > 0)
	{
	start = mod(proc->startpos + proc->PC, MEM_SIZE);
	i = 0;
	//ft_printf("%d  ", proc->ID);
	if (start > 0)
		ft_printf("ADV %d (%06#x -> %#06x)", proc->next_jump, start, start + proc->next_jump);
	else
		ft_printf("ADV %d (0x0000 -> %#06x)", proc->next_jump, proc->startpos + proc->PC + proc->next_jump);
	if (proc->next_jump < 1000)
		while (i < proc->next_jump)
		{
			ft_printf(" %02x", core->arena[mod(proc->startpos + proc->PC + i, MEM_SIZE)]);
			i++;
		}
	ft_printf(" \n");
	}
}

void	ft_determinejmpdist(t_cor *core, t_process *proc)
{
	unsigned char	tmp;
	unsigned char	op;

	op = core->arena[(proc->startpos + proc->PC) % MEM_SIZE];
	op = revgetop(proc->next_op);
	tmp = core->arena[(proc->startpos + proc->PC + 1) % MEM_SIZE];
	if (op != 9 && op < 17 && op > 0)
	{
		if (hasopcode(op))
		{
			proc->next_jump = 2;
			while (tmp)
			{
				tmp /= 4;
				if (tmp % 4 == 1)
					proc->next_jump += 1;
				else if (tmp % 4 == 3)
					proc->next_jump += 2;
				else if (tmp % 4 == 2)
					proc->next_jump += g_oplabel[op - 1];
			}
		}
		else
			proc->next_jump = 1 + g_oplabel[op - 1];
		//if (core->arena[(proc->startpos + proc->PC) % MEM_SIZE] == 2 && proc->next_jump >= 8)
			//proc->next_jump = 6;
	}
	else
		proc->next_jump = 0; // aqui
}
