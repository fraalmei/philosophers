/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:05:25 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/12 16:52:58 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	dead_p(t_philin *philo)
{
	if (get_time() - philo->lst_meal >= philo->table->t_die)
	{
		print("died", philo);
		philo->table->dead = 1;
		return (1);
	}
	return (0);
}

static t_forkin	*new_fork(int n)
{
	t_forkin		*fork;

	fork = calloc(sizeof(t_forkin), 1);
	if (!fork)
		return (NULL);
	fork->n = n;
	fork->mutex = 0;
	pthread_mutex_init(&(fork->use), NULL);
	return (fork);
}

t_philin	*new_phil(int n)
{
	t_philin			*filo;

	filo = (t_philin *)calloc(sizeof(t_philin) + 1, 1);
	if (!filo)
		return (NULL);
	filo->n = n;
	filo->r_frk = 0;
	filo->l_frk = 0;
	filo->color = (n % 7) + 31;
	filo->lst_meal = 0;
	filo->meals = 0;
	return (filo);
}

int	create_philos(t_table *table)
{
	int		i;

	i = -1;
	table->philo = ft_calloc(sizeof(t_philin *), table->n_philos + 1);
	table->fork = ft_calloc(sizeof(t_forkin *), table->n_philos + 1);
	while (++i < table->n_philos)
	{
		table->philo[i] = new_phil(i);
		table->fork[i] = new_fork(i);
	}
	return (0);
}
