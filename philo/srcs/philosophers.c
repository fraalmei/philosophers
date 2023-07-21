/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:05:25 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/21 14:45:08 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/// @brief function to take the forks
/// check the forks arent the same fork
/// lock the forks if it can
/// print the fork message and sleep the thread
/// renew the last meal time, print the eat message and sleep the thread
/// unlock the forks
/// @param philo the philo of the thread
/// @return 1 if it works correctly
static int	take_f(t_philin *philo)
{
	if (philo->fork_minus->n == philo->fork_plus.n && \
			!(philo->fork_minus->mutex == 0 && philo->fork_plus.mutex == 0))
		return (0);
	usleep (5);
	pthread_mutex_lock(&philo->fork_minus->use);
	pthread_mutex_lock(&philo->fork_plus.use);
	philo->fork_minus->mutex = 1;
	philo->fork_plus.mutex = 1;
	print("has taken a fork", philo);
	philo->lst_meal = get_time();
	print("is eating", philo);
	slp(philo->t_eat);
	philo->fork_minus->mutex = 0;
	philo->fork_plus.mutex = 0;
	pthread_mutex_unlock(&philo->fork_minus->use);
	pthread_mutex_unlock(&philo->fork_plus.use);
	return (1);
}

/// @brief function of the thread
/// take the philo struct of the args
/// start the thread calling a functin to retard the start
/// start a loop to work while no one philosophers die
/// check the fork function if its works reset the think variable
/// increase the meals made and check if it the limit
/// print the sleep message and sleep the thread
/// if the fork function didn't work
/// print the think message if its the first time
/// @param arg philo struct passed when create the thread
/// @return NULL when end the loop, only when the meals limit is reached
void	*philo(void *arg)
{
	t_philin					*philo;

	philo = ((t_philin *) arg);
	init_thread(philo);
	pthread_mutex_lock(&philo->mutex);
	while (philo->table->dead == 0)
	{
		if (take_f(philo))
		{
			philo->think = 0;
			if (++philo->meals == philo->table->n_eats)
				break ;
			print("is sleeping", philo);
			slp(philo->t_sleep);
		}
		if (philo->think++ == 0)
			print("is thinking", philo);
	}
	pthread_mutex_unlock(&philo->mutex);
	pthread_exit (NULL);
}

/// @brief create a new philosopher struct
/// allocate the philo struct and check the correct allocation
/// asign the philosopher data needed
/// create the mutex for the philosopher's fork
/// @param n identification number of the philosopher
/// @param table
/// @param otr_f the fork of the left (or right) philosopher
/// @return the philosopher struct or NULL if the allocation didn't work
static t_philin	*new_phil(int n, t_table *table, t_forkin *otr_f)
{
	t_philin			*philo;

	philo = (t_philin *)calloc(sizeof(t_philin) + 1, 1);
	if (!philo)
		return (NULL);
	philo->n = n;
	philo->color = (n % 7) + 31;
	philo->lst_meal = 0;
	philo->meals = 0;
	philo->think = 0;
	philo->fork_minus = otr_f;
	philo->fork_plus.n = n;
	philo->fork_plus.mutex = 0;
	philo->table = table;
	philo->t_eat = table->t_eat;
	philo->t_sleep = table->t_sleep;
	pthread_mutex_init(&philo->mutex, NULL);
	pthread_mutex_init(&philo->fork_plus.use, NULL);
	return (philo);
}

/// @brief function to create all the philosophers struct
/// allocate the pointer to each philosopher struct
/// and loop to create all philosophers
/// and assign thefork of the next philosopher's
/// @param table
/// @return
int	create_philos(t_table *table)
{
	int			i;

	i = 0;
	table->philo = ft_calloc(sizeof(t_philin *), table->n_philos + 1);
	if (!table->philo)
		return (1);
	table->philo[i] = new_phil(i, table, NULL);
	while (++i < table->n_philos)
	{
		table->philo[i] = new_phil(i, table, &table->philo[i - 1]->fork_plus);
		if (!table->philo[i])
			return (1);
	}
	table->philo[0]->fork_minus = &table->philo[i - 1]->fork_plus;
	return (0);
}
