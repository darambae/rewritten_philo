/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:33:36 by dabae             #+#    #+#             */
/*   Updated: 2024/04/23 16:20:55 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->param->print);
	printf("%llu %d %s\n", get_time(), philo->id, msg);
	pthread_mutex_unlock(&philo->param->print);
}


void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock); // Lock the philosopher's lock to ensure atomic access to num_eat
	if (philo->num_eat < philo->param->max_num_eat)
	{
		pthread_mutex_lock(philo->l_fork);
		print(philo, "has taken left fork");
		pthread_mutex_lock(philo->r_fork);
		print(philo, "has taken right fork");
		philo->is_eating = true;
		print(philo, "is eating");
		philo->countdown_to_death = get_time() + philo->param->time_to_die;
		ft_usleep(philo->param->time_to_eat);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		philo->is_eating = false;
		philo->num_eat++; // Increment the eat counter
		if (philo->num_eat >= philo->param->max_num_eat) 
		{
			pthread_mutex_lock(&philo->param->stop_lock); // Lock the stop lock to ensure atomic access to stop
			philo->param->num_full++; // Increment the number of philosophers that have eaten enough
			pthread_mutex_unlock(&philo->param->stop_lock); // Unlock the stop lock
			pthread_mutex_unlock(&philo->lock); // Unlock the philosopher's lock if they've finished eating
			return ;
		}
	}
	else
	{
		pthread_mutex_lock(&philo->param->stop_lock); // Lock the stop lock to ensure atomic access to stop
		philo->param->num_full++; // Increment the number of philosophers that have eaten enough
		pthread_mutex_unlock(&philo->param->stop_lock); // Lock the stop lock to ensure atomic access to stop		
		pthread_mutex_unlock(&philo->lock); // Unlock the philosopher's lock
		return;
	}
	pthread_mutex_unlock(&philo->lock); // Unlock the philosopher's lock
}
