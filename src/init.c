/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:13:10 by dabae             #+#    #+#             */
/*   Updated: 2024/04/25 07:23:18 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_param(t_param *param, char **av)
{
	if (is_positive(av) && is_digit(av))
	{
		param->num_philo = (int)ft_atoi(av[0]);
		param->time_to_die = (uint64_t)ft_atoi(av[1]);
		param->time_to_eat = (uint64_t)ft_atoi(av[2]);
		param->time_to_sleep = (uint64_t)ft_atoi(av[3]);
		if (av[4])
			param->max_num_eat = (int)ft_atoi(av[4]);
		else
			param->max_num_eat = -1;
		param->stop = false;
		param->num_full = 0;
		param->philo = malloc(sizeof(t_philo) * param->num_philo);
		param->forks = malloc(sizeof(pthread_mutex_t) * param->num_philo);
		param->tids = malloc(sizeof(pthread_t) * param->num_philo);
		pthread_mutex_init(&param->print, NULL);
		pthread_mutex_init(&param->stop_lock, NULL);
	}
	else
		ft_err_msg("Invalid arguments", param);
}

void	init_philo(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->num_philo)
	{
		param->philo[i].id = i + 1;
		param->philo[i].countdown_to_death = get_time() + param->time_to_die;
		param->philo[i].num_eat = 0;
		param->philo[i].is_dead = false;
		param->philo[i].is_eating = false;
		param->philo[i].param = param;
		pthread_mutex_init(&param->philo[i].lock, NULL);
		pthread_mutex_init(&param->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < param->num_philo)
	{
		param->philo[i].l_fork = &param->forks[i];
		if (i == 0)
			param->philo[i].r_fork = &param->forks[param->num_philo - 1];
		else
			param->philo[i].r_fork = &param->forks[i - 1];
		i++;
	}
}