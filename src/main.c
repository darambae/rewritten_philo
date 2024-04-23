/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:02:42 by dabae             #+#    #+#             */
/*   Updated: 2024/04/23 16:27:36 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleanup_memory(t_param *param)
{
	if (param->philo)
		free(param->philo);
	if (param->forks)
		free(param->forks);
	if (param->tids)
		free(param->tids);
	free(param);
}

void	ft_exit(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->num_philo)
	{
		pthread_mutex_destroy(&param->philo[i].lock);
		pthread_mutex_destroy(&param->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&param->print);
	pthread_mutex_destroy(&param->stop_lock);
	cleanup_memory(param);
}

int	ft_err_msg(char *msg, t_param *param)
{
	if (param)
		ft_exit(param);
	if (msg)
	{
		printf("Error: %s\n", msg);
		exit(1);
	}
	else
		exit(0);
}

void	only_one_philo(t_param *param)
{
	pthread_create(&param->tids[0], NULL, &routine, &param->philo[0]);
	pthread_join(param->tids[0], NULL);
	while (param->stop == 0)
		ft_usleep(0);
	ft_exit(param);
}

int	main(int ac, char **av)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	if (!param)
		return (ft_err_msg("Malloc failed", NULL));
	if (ac == 5 || ac == 6)
	{
		init_param(param, av + 1);
		init_philo(param);
		if (param->num_philo == 1)
			only_one_philo(param);
		else
			life_cycle(param);
	}
	else
		return (ft_err_msg("Invalid number of arguments", param));
	return (0);
}
