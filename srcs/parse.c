/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starrit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 12:35:07 by starrit           #+#    #+#             */
/*   Updated: 2017/08/09 15:19:52 by starrit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_CHAMP_SIZE 1000

static int		*get_hexa(unsigned char *champion, size_t size_champ)
{
	int	*new;
	int	i;
	int j;

//	i = 3 + 37;
//	i = 28;
	i = 0;
	j = 0;
	new = (int*)malloc(sizeof(*new) * (size_champ + 1));//
	while (i < size_champ)
	{
		new[j] = champion[i];
		j++;
		i++;
	}
	return (new);
}

/*
**	parse un champion en hexa et rempli sa struct champ
**	rempli sa struct process
*/


// a faire : 	remplir les 2 struct
// 				changer 138 par la formule exacte (voir asm)

#include <stdlib.h>
int				*parse(char *av, int fd, int ret, bool start)
{
	unsigned char	buf[2];
	unsigned char	*champion;
	size_t			size_champ = 0;
	int				*new;

	champion = NULL;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		exit(printf("crash open"));//ft_printf
	champion = malloc(sizeof(*champion) * (MAX_CHAMP_SIZE + 1));//
	int s = 0;
	while ((ret = read(fd, buf, 1)) > 0)
	{
		if (s > 138 && buf[0] && buf[0] > 0 && buf[0] < 17)
			start = true;
		if (start == true)
		{
			champion[size_champ] = buf[0];
			size_champ++;
		}
		s++;
	}
	champion[size_champ] = '\0';
	new = get_hexa(champion, size_champ);
	return (new);
}
