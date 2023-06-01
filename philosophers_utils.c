/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:14:46 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/03/28 20:45:40 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fillinfo(t_info *info, char **av, int ac, t_common *common)
{
	info->phils = ft_atoi(av[1]);
	info->die = ft_atoi(av[2]);
	info->eat = ft_atoi(av[3]);
	info->sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->eatnum = ft_atoi(av[5]);
	else
		info->eatnum = MAX_INT;
	common->info = info;
}

int	initlocks(t_common *common, t_phils *phils, int i)
{
	if (pthread_mutex_init(&common->printlock, NULL) != 0)
	{
		freestruct(phils);
		return (1);
	}
	while (i < common->info->phils)
	{
		if (pthread_mutex_init(&common->forks[i], NULL) != 0)
		{
			freestruct(phils);
			pthread_mutex_destroy(&common->printlock);
			return (1);
		}
		i++;
	}
	fillphil(phils, common);
	return (0);
}

int	destroylocks(t_common *common)
{
	int	i;

	i = 0;
	while (i < common->info->phils)
	{
		if (pthread_mutex_destroy(&common->forks[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(&common->printlock) != 0)
		return (1);
	return (0);
}

int	philinit(t_info *info, t_common *common, t_phils **phils)
{
	int	i;

	i = 0;
	*phils = malloc(sizeof(t_phils) * common->info->phils);
	if (*phils == NULL)
		return (1);
	common->threads = malloc(sizeof(pthread_t) * common->info->phils);
	if (common->threads == NULL)
	{
		free(phils);
		return (1);
	}
	common->forks = malloc(sizeof(pthread_mutex_t) * common->info->phils);
	if (common->forks == NULL)
	{
		free(phils);
		free(common->threads);
		return (1);
	}
	if (initlocks(common, *phils, i) == 1)
		return (1);
	return (0);
}

void	mutexprint(int id, char *msg, int time, t_common *common)
{
	pthread_mutex_lock(&common->printlock);
	printf("%d %d %s\n", time, id, msg);
	pthread_mutex_unlock(&common->printlock);
}
