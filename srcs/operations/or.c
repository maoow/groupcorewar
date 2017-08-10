/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:25:10 by cbinet            #+#    #+#             */
/*   Updated: 2017/08/10 13:46:50 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

bool	or(t_cor *core, t_process *proc)
{
	size_t	a;
	size_t	b;

	a = getparam(core, proc, 1, 4);
	b = getparam(core, proc, 2, 4);
	proc->registres[core->arena[getparamplace(core, proc, 3, 4)]] = a || b;
	return (true);
}
