/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:15:21 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/03/28 20:45:34 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pickupforks(t_phils *phils)
{
	pthread_mutex_lock(phils->forks.right);
	if (phils->status != 3)
		mutexprint(phils->id, "has taken a fork", \
		gettime(phils), phils->common);
	pthread_mutex_lock(phils->forks.left);
	if (phils->status != 3)
		mutexprint(phils->id, "has taken a fork", \
		gettime(phils), phils->common);
}

void	fillphil(t_phils *phils, t_common *common)
{
	int	i;

	i = 0;
	while (i < common->info->phils)
	{
		phils[i].id = i + 1;
		phils[i].timesate = 0;
		phils[i].status = 0;
		phils[i].common = common;
		phils[i].forks.right = &common->forks[i];
		if (i == common->info->phils - 1)
			phils[i].forks.left = &common->forks[0];
		else
			phils[i].forks.left = &common->forks[i + 1];
		i++;
	}
}

int	freestruct(t_phils *phils)
{
	free(phils->common->forks);
	free(phils->common->threads);
	free(phils);
	return (0);
}

int	inputhandling(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Give 4 or 5 args.\n");
		return (1);
	}
	if (ac == 6 && ft_atoi(av[5]) == 0)
		return (1);
	if (ft_atoi(av[1]) == 1)
	{
		printf("0 1 is thinking\n0 1 has taken a fork\n%d 1 has died\n"\
		, ft_atoi(av[2]));
		return (1);
	}
	if (inputhandling2(ac, av) == 1)
		return (1);
	return (0);
}

int	inputhandling2(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Positive integers only please.\n");
				return (1);
			}
			j++;
		}
		if (j == 0)
			return (1);
		j = 0;
		i++;
	}
	return (0);
}
