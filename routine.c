/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:15:13 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/03/28 20:45:33 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	gettime(t_phils *phils)
{
	struct timeval	time;
	long long		diff;

	gettimeofday(&time, NULL);
	diff = (time.tv_sec * 1000 + time.tv_usec / 1000) \
	- (phils->common->startms);
	return (diff);
}

long long	converttime(struct timeval time)
{
	long long	t1;

	t1 = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (t1);
}

void	ft_eat(t_phils *phils)
{
	gettimeofday(&phils->time, NULL);
	phils->endtime = converttime(phils->time) + phils->common->info->eat;
	mutexprint(phils->id, "is eating", gettime(phils), phils->common);
	while (phils->status != 3 && converttime(phils->time) < phils->endtime)
	{
		usleep(500);
		gettimeofday(&phils->time, NULL);
	}
	gettimeofday(&phils->lastmeal, NULL);
	phils->timesate++;
}

void	ft_sleep(t_phils *phils)
{
	gettimeofday(&phils->time, NULL);
	phils->endtime = converttime(phils->time) + phils->common->info->sleep;
	mutexprint(phils->id, "is sleeping", gettime(phils), phils->common);
	while (phils->status != 3 && converttime(phils->time) < phils->endtime)
	{
		usleep(500);
		gettimeofday(&phils->time, NULL);
	}
}

void	*routine(void *arg)
{
	t_phils	*phils;

	phils = (t_phils *)arg;
	if (phils->id % 2 == 0)
	{
		mutexprint(phils->id, "is thinking", gettime(phils), phils->common);
		usleep(phils->common->info->eat / 2 * 1000);
	}
	while (phils->status != 3)
	{
		if (phils->status != 3)
			mutexprint(phils->id, "is thinking", gettime(phils), phils->common);
		pickupforks(phils);
		if (phils->status != 3)
			ft_eat(phils);
		pthread_mutex_unlock(phils->forks.left);
		pthread_mutex_unlock(phils->forks.right);
		if (phils->status != 3)
			ft_sleep(phils);
	}
	return (0);
}
