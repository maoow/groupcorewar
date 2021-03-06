/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starrit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:08:00 by starrit           #+#    #+#             */
/*   Updated: 2017/11/29 11:15:37 by starrit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		exitfree_champ(t_cor *cor)
{
	t_champ		*tmp;
	t_champ		*tmp2;

	tmp = cor->champs;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_strdel(&tmp->name);
		ft_strdel(&tmp->comment);
		free(tmp);
		tmp = NULL;
		tmp = tmp2;
	}
}

static void		exitfree_process(t_cor *cor)
{
	t_process	*tmp;
	t_process	*tmp2;

	tmp = cor->process;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = tmp2;
	}
}

static void		exitfree_idlist(t_opt_number *tmp)
{
	t_opt_number	*tmp2;

	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = tmp2;
	}
}

static void		exitfree_options(t_cor *cor)
{
	t_options	*tmp;

	tmp = cor->options;
	free(tmp);
	tmp = NULL;
}

void			ft_clean(t_cor *cor)
{
	if (cor)
	{
		if (cor->champs)
			exitfree_champ(cor);
		if (cor->process)
			exitfree_process(cor);
		if (cor->options)
			exitfree_options(cor);
		if (cor->id_list)
			exitfree_idlist(cor->id_list);
		cor = NULL;
	}
}
