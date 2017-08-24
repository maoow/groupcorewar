/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 12:07:38 by cbinet            #+#    #+#             */
/*   Updated: 2017/08/24 15:00:32 by starrit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_init(t_cor *core)
{
	size_t		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		core->arena[i] = 0;
		core->arena_color[i] = 3;
		i++;
	}
	core->cycle_to_die = CYCLE_TO_DIE;
	core->tmp_cycle_to_die = 0;
	core->checks = 0;
	core->total_cycle = 0;
	core->verbose = true;
	core->champs = NULL;
	core->process = NULL;
	core->last_champ_alive = NULL;
}

/*
**	parse() : recupere le code hexa du champion
**	nb_champ + 3 pour la couleur car les COLOR_PAIR de champ commencent a 4
**	champ[0][0] = size du champion,	champ[1] = int* du code du champion
**
**	while : attribution de la couleur dans l'arene.
**		moove_champ = espacement entre chaque champion
**		decal = decalage de chaque champion, commence a zero puis augmente de
**			moove_champ pour chaque incrementation
*/
void			launch_parse(t_cor *cor, int ac, char **av)
{
	size_t		nb_champ;
	int			**champ;
	size_t		moove_champ;
	size_t		i;
	size_t		decal = 0;

	nb_champ = 1;//nb_champ = 1 + nb_option
	if (ac > 1)
	moove_champ = MEM_SIZE / (ac - 1);
	i = 0;
	while (nb_champ < (size_t)ac)
	{
		champ = parse(cor, av[nb_champ]);
		add_process(cor, decal, ac - nb_champ);
		while (i + decal < champ[0][0] + decal)
		{
			cor->arena[i + decal] = champ[1][i];
			cor->arena_color[i + decal] = nb_champ + 3;
			if (i == 0)//a virer
				cor->arena_color[i + decal] = 10 + nb_champ + 3;
			i++;
		}
		i = 0;
		decal = decal + moove_champ;
		nb_champ++;
	}
	cor->nb_champs = nb_champ;
}

static void		ft_clean(t_cor *core)
{
	(void)core;
	// TO DO
}

//check error : no champ : actuellement : floating point exception
int				main(int ac, char **av)
{
	t_cor	core;

	ft_init(&core);
	launch_parse(&core, ac, av);
	ft_warcycle(&core);
	ft_clean(&core);
}
