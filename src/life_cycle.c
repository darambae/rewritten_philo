/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:33:12 by dabae             #+#    #+#             */
/*   Updated: 2024/04/24 12:29:00 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	stop_lock(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->stop_lock);
	philo->param->stop = true;
	pthread_mutex_unlock(&philo->param->stop_lock);
}

void	*set_stop(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	pthread_mutex_lock(&phi->param->stop_lock);
	while (phi->param->stop == false && phi->param->num_full < phi->param->num_philo)
	{
		pthread_mutex_unlock(&phi->param->stop_lock);
		ft_usleep(1000);
		pthread_mutex_lock(&phi->param->stop_lock);
	}
	if (phi->param->max_num_eat != -1 && phi->param->stop == false && phi->param->num_full >= phi->param->num_philo)
	{
		pthread_mutex_lock(&phi->param->print);
		printf("Everyone has eaten as many times as %d\n", phi->param->max_num_eat);
		pthread_mutex_unlock(&phi->param->print);
		phi->param->stop = true;
		pthread_mutex_unlock(&phi->param->stop_lock);
	}
	pthread_mutex_lock(&phi->lock);
	if (phi->countdown_to_death <= get_time() && phi->is_eating == false)
	{
		stop_lock(phi);
		phi->is_dead = true;
		print(phi, "died");
		pthread_mutex_unlock(&phi->lock);
	}
	pthread_mutex_unlock(&phi->param->stop_lock);
	return (NULL);
}
	// while (1)
	// {
	// 	pthread_mutex_lock(&phi->lock);
	// 	if (phi->param->max_num_eat != -1 && \
	// 		phi->param->num_full >= phi->param->num_philo)
	// 	{
	// 		pthread_mutex_lock(&phi->param->print);
	// 		printf("All philosophers have eaten %d times\n", phi->param->max_num_eat);
	// 		pthread_mutex_unlock(&phi->param->print);
	// 		pthread_mutex_unlock(&phi->lock);
	// 		stop_lock(phi);
	// 		break ;
	// 	}
	// 	if (phi->countdown_to_death <= get_time() && phi->is_eating == false)
	// 	{
	// 		phi->is_dead = true;
	// 		print(phi, "died");
	// 		pthread_mutex_unlock(&phi->lock);
	// 		stop_lock(phi);
	// 		break ;
	// 	}
	// 	pthread_mutex_unlock(&phi->lock);
	// 	//ft_usleep(1000);
	// }
// 	return (NULL);
// }

void	*routine(void *philo)
{
	t_philo		*phi;
	pthread_t	stop;

	phi = (t_philo *)philo;
	pthread_create(&stop, NULL, &set_stop, phi);
	if (phi->param->num_philo == 1)
	{
		phi->is_dead = true;
		pthread_join(stop, NULL);
		return (NULL);
	}
	while (phi->is_dead == false && phi->param->stop == false && phi->param->num_full < phi->param->num_philo)
	{
		eat(phi);
		print(phi, "is sleeping");
		ft_usleep(phi->param->time_to_sleep);
		print(phi, "is thinking");
	}
	pthread_join(stop, NULL);
	return (NULL);
}

void	*monitor_stop(void *arg)
{
	t_param	*param;

	param = (t_param *)arg;
	while (1)
	{
		pthread_mutex_lock(&param->stop_lock);
		if (param->stop == true)
		{
			pthread_mutex_unlock(&param->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&param->stop_lock);
		ft_usleep(1000);
	}
	return (NULL);
}

void	life_cycle(t_param *param)
{
	pthread_t	monitor;
	int			i;

	i = -1;
	pthread_create(&monitor, NULL, &monitor_stop, param);
	while (++i < param->num_philo)
		pthread_create(&param->tids[i], NULL, &routine, &param->philo[i]);
	i = -1;
	while (++i < param->num_philo)
	{
		pthread_join(param->tids[i], NULL);
		ft_usleep(1);
	}
	pthread_join(monitor, NULL);
	ft_exit(param);
}