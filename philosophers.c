/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:59:59 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/03/28 20:45:29 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eatnumcheck(int i, int *flag, t_phils *phils, t_common *common)
{
	if (i == 0 && phils[i].timesate >= common->info->eatnum \
	&& common->info->eatnum != MAX_INT)
	{
		while (i <= common->info->phils)
		{
			if (phils[i].timesate >= common->info->eatnum)
				i++;
			else
			{
				i = 0;
				break ;
			}
			if (i == common->info->phils)
			{
				i = 0;
				while (i <= common->info->phils)
				{
					phils[i].status = 3;
					i++;
				}
				*flag = 1;
				break ;
			}
		}
	}
}

void	announcedeath(int i, t_phils *phils, t_common *common)
{
	mutexprint(phils[i].id, "died", gettime(&phils[i]), common);
	i = 0;
	while (i < common->info->phils)
	{
		phils[i].status = 3;
		i++;
	}
}

void	monitoring(t_phils *phils, t_common *common, int i)
{
	int				flag;
	struct timeval	time;

	i = 0;
	flag = 0;
	while (1 && flag != 1)
	{
		if (phils[i].status == 3)
		{
			flag = 1;
			announcedeath(i, phils, common);
			break ;
		}
		gettimeofday(&time, NULL);
		if (converttime(time) - converttime(phils[i].lastmeal) \
		> common->info->die)
		{
			phils[i].status = 3;
			continue ;
		}
		eatnumcheck(i, &flag, phils, common);
		i++;
		if (i == common->info->phils)
			i = 0;
	}
}

int	createthreads(t_phils *phils, t_common *common, int i)
{
	gettimeofday(&common->starttime, NULL);
	common->startms = converttime(common->starttime);
	while (i < common->info->phils)
	{
		phils[i].lastmeal = common->starttime;
		i++;
	}
	i = 0;
	while (i < common->info->phils)
	{
		if (pthread_create(&common->threads[i], NULL, &routine, \
		(void *)&phils[i]) != 0)
			return (1);
		i++;
	}
	monitoring(phils, common, i);
	i = 0;
	while (i < common->info->phils)
	{
		if (pthread_join(common->threads[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_info		info;
	t_common	common;
	t_phils		*phils;
	int			i;

	i = 0;
	if (inputhandling(ac, av) == 1)
		return (0);
	fillinfo(&info, av, ac, &common);
	if (philinit(&info, &common, &phils) == 1)
		return (1);
	if (createthreads(phils, &common, i) == 1)
	{
		freestruct(phils);
		return (1);
	}
	if (destroylocks(&common) == 1)
	{
		freestruct(phils);
		return (1);
	}
	if (freestruct(phils) == 1)
		return (1);
	return (0);
}
