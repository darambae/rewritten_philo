/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:02:52 by dabae             #+#    #+#             */
/*   Updated: 2024/04/23 16:35:25 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	u_int64_t		countdown_to_death;
	int				num_eat;

	bool			is_dead;
	bool			is_eating;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	lock;
	struct s_param	*param;
}					t_philo;

typedef struct s_param
{
	int					num_philo;
	u_int64_t			time_to_die;
	u_int64_t			time_to_eat;
	u_int64_t			time_to_sleep;
	int					max_num_eat;
	bool				stop;
	int					num_full;
	pthread_t			*tids;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		stop_lock;
}				t_param;

int			ft_err_msg(char *msg, t_param *param);
void		ft_exit(t_param *param);
int			is_digit(char **av);
long		ft_atoi(char *str);
int			is_positive(char **str);
void		ft_usleep(uint64_t elapsed);
u_int64_t	get_time(void);
void		init_param(t_param *param, char **av);
void		init_philo(t_param *param);
void		eat(t_philo *philo);
void		print(t_philo *philo, char *msg);
void		*routine(void *philo);
void		life_cycle(t_param *param);
#endif