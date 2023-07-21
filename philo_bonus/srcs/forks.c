/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:13:40 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/12 16:56:59 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	take_f(t_philin *philo)
{
	if (philo->r_frk == 0 && philo->l_frk == 0)
	{
		pthread_mutex_lock(&philo->l_fork->use);
		pthread_mutex_lock(&philo->r_fork->use);
		print("has taken a fork", philo);
		philo->r_fork->mutex = 1;
		philo->l_fork->mutex = 1;
		philo->r_frk = 1;
		philo->l_frk = 1;
		return (1);
	}
	return (0);
}

void	drop_f(t_philin *philo)
{
	pthread_mutex_unlock(&philo->l_fork->use);
	pthread_mutex_unlock(&philo->r_fork->use);
	philo->r_fork->mutex = 0;
	philo->l_fork->mutex = 0;
	philo->r_frk = 0;
	philo->l_frk = 0;
	philo->lst_meal = get_time();
}
