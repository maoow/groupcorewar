/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkim <vkim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 11:42:42 by vkim              #+#    #+#             */
/*   Updated: 2017/11/29 16:53:36 by starrit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				ft_del_com(t_asm *as)
{
	int			i;
	int			j;
	int			count;
	char		*save;

	count = 0;
	i = -1;
	while (as->lines[++i])
	{
		j = -1;
		while (as->lines[i][++j])
		{
			if (as->lines[i][j] == '"')
				count++;
			if (as->lines[i][j] == '#' && (count % 2) == 0)
			{
				save = as->lines[i];
				if (!(as->lines[i] = ft_strsub(as->lines[i], 0, j)))
					return (0);
				free(save);
				j--;
			}
		}
	}
	return (1);
}

int				ft_del_space(t_asm *as)
{
	int			i;
	int			j;
	char		*save;

	i = -1;
	while (as->lines[++i])
	{
		j = -1;
		while (as->lines[i][++j] == ' ' || as->lines[i][j] == '\t')
			;
		save = as->lines[i];
		if (!(as->lines[i] = ft_strsub(as->lines[i], j,
			ft_strlen(as->lines[i]) - j)))
			return (0);
		free(save);
		j = ft_strlen(as->lines[i]);
		while (--j > -1 && (as->lines[i][j] == ' ' || as->lines[i][j] == '\t'))
			;
		as->lines[i][j + 1] = '\0';
	}
	return (1);
}
