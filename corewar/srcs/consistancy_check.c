/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consistancy_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 12:55:45 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/28 12:53:55 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

size_t			g_opparams[OPC_NUMBER][3] =
{
	{T_DIR},
	{0, T_DIR | T_IND, T_REG},
	{0, T_REG, T_IND | T_REG},
	{T_REG, T_REG, T_REG},
	{T_REG, T_REG, T_REG},
	{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
	{T_DIR},
	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
	{T_DIR | T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
	{T_DIR},
	{0, T_DIR | T_IND, T_REG},
	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
	{T_DIR},
	{T_REG}
};

size_t			g_opparamnb[OPC_NUMBER] = {
	1,
	2,
	2,
	3,
	3,
	3,
	3,
	3,
	1,
	3,
	3,
	1,
	2,
	3,
	1,
	1
};

bool			g_ocp[OPC_NUMBER] = {
	false,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	false,
	true,
	true,
	false,
	true,
	true,
	false,
	true
};

/*
** check if operation has opcode
*/

bool			hasopcode(size_t op)
{
	return (g_ocp[op - 1]);
}

/*
** check if operation is executable
*/

bool			checkopn(t_cor *core, t_process *proc)
{
	size_t op;

	op = core->arena[(proc->pc + proc->startpos) % MEM_SIZE];
	if (op == 0 || op > OPC_NUMBER)
		return (false);
	return (true);
}

/*
** ft_checexecutable() :
**
** check if the param given proc is on a logically executable operation
**
** (check if operation number is correct and in case of the operation
** have opcode count the number of parameters)
** if opc unconsistant jump it (jump = 2)
*/

static int		get_paramsize(size_t opc, size_t op)
{
	int		ret;
	size_t	i;
	size_t	tmp;

	ret = 0;
	i = 0;
	while (opc / 4)
	{
		opc /= 4;
		tmp = opc % 4;
		if (tmp == 3)
			tmp++;
		if (i < 3 - g_opparamnb[op - 1])
			i++;
		else if (opc % 4 == 3)
			ret += 2;
		else if (opc % 4 == 2 && getlabel(op - 1) == 0)
			ret += 4;
		else if (opc % 4 == 2)
			ret += getlabel(op - 1);
		else if (opc % 4 == 1)
			ret += 1;
	}
	return (ret);
}

bool			ft_checkexecutable(t_cor *core, t_process *proc)
{
	size_t op;
	size_t opc;

	op = revgetop(proc->next_op);
	if (op >= 1 && op <= OPC_NUMBER && g_ocp[op - 1])
	{
		opc = core->arena[(proc->startpos + proc->pc + 1) % MEM_SIZE];
		if (get_paramnb(opc) != g_opparamnb[op - 1] || (g_opparamnb[op - 1] == 2
					&& (opc / 64 == 0 || (opc / 16) % 4 == 0)))
		{
			proc->next_jump = get_paramsize(opc, op) + 2;
			if (core->options->v16)
				dispjump(core, proc);
			return (false);
		}
		opc = core->arena[(proc->startpos + proc->pc + 1) % MEM_SIZE];
		if (g_opparamnb[op - 1] > 1 && proc->next_jump <= 3)
		{
			proc->next_jump = get_paramsize(opc, op) + 2;
			if (core->options->v16)
				dispjump(core, proc);
			return (false);
		}
	}
	return (true);
}

/*
** ft_checkloadable() :
**
** check if the param given proc is on a logically executable operation
*/

bool			ft_checkloadable(t_cor *core, t_process *proc)
{
	if (!checkopn(core, proc))
		return (false);
	return (true);
}
