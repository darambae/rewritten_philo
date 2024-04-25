/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:33:36 by dabae             #+#    #+#             */
/*   Updated: 2024/04/24 11:11:46 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->param->print);
	printf("%lu %d %s\n", get_time(), philo->id, msg);
	pthread_mutex_unlock(&philo->param->print);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	print(philo, "has taken both forks");
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = true;
	philo->num_eat++;
	print(philo, "is eating");
	philo->countdown_to_death = get_time() + philo->param->time_to_die;
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->param->time_to_eat);
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->l_fork);	
	pthread_mutex_unlock(philo->r_fork);
}
