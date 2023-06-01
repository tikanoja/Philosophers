/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:00:12 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/03/28 20:45:43 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_*
# define MAX_INT 2147483647

typedef struct s_info
{
	int			phils;
	int			die;
	int			eat;
	int			sleep;
	int			eatnum;
}				t_info;

typedef struct s_forks
{
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
}				t_forks;

typedef struct s_common
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	printlock;
	pthread_t		*threads;
	t_info			*info;
	struct timeval	starttime;
	long long		startms;
}				t_common;

typedef struct s_phils
{
	t_forks			forks;
	int				id;
	int				timesate;
	int				status;
	struct timeval	lastmeal;
	struct timeval	time;
	long long		endtime;
	t_common		*common;
}				t_phils;

//philosophers.c
void		eatnumcheck(int i, int *flag, t_phils *phils, t_common *common);
void		announcedeath(int i, t_phils *phils, t_common *common);
void		monitoring(t_phils *phils, t_common *common, int i);
int			createthreads(t_phils *phils, t_common *common, int i);
int			main(int ac, char **av);

//philosophers_utils.c
void		fillinfo(t_info *info, char **av, int ac, t_common *common);
int			initlocks(t_common *common, t_phils *phils, int i);
int			destroylocks(t_common *common);
int			philinit(t_info *info, t_common *common, t_phils **phils);
void		mutexprint(int id, char *msg, int time, t_common *common);

//routine.c
int			gettime(t_phils *phils);
long long	converttime(struct timeval time);
void		ft_eat(t_phils *phils);
void		ft_sleep(t_phils *phils);
void		*routine(void *arg);

//routine_utils.c
void		pickupforks(t_phils *phils);
void		fillphil(t_phils *phils, t_common *common);
int			freestruct(t_phils *phils);
int			inputhandling(int ac, char **av);
int			inputhandling2(int ac, char **av);

//ft_atoi.c
int			toolong(int sign);
int			ft_atoi(const char *str);

#endif