/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:34:20 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/22 11:48:07 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/// @brief function to check the meals made by all the philosophers
/// @param table 
/// @return 1 if all philosophers made the meals limit
static int	check_meals(t_table *table)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < table->n_philos)
	{
		if (table->philo[i]->meals == table->n_eats)
			j++;
		i++;
	}
	if (j == table->n_philos)
		return (1);
	return (0);
}

/// @brief function of the thread to check if any philosopher is dead
/// the functionwait to start with all the philosophers
/// and go into the loop checking all the philosophers if anyone
/// reach the limit time of dead, changing the state dead in the table
/// once all the philosophers are checked
/// checking the meals and restart the philosophers count
/// if one philosophers is dead or all are end theirs meals end the thread
/// @param arg 
/// @return 
void	*check_dead(void *arg)
{
	t_table			*table;
	int				i;

	table = ((t_table *) arg);
	i = 0;
	wait_to(table->t_start, 1000 + (table->t_eat / 2));
	while (!table->dead)
	{
		if ((get_time() - table->philo[i]->lst_meal) > table->t_die)
		{
			print("died", table->philo[i]);
			table->dead = 1;
		}
		i++;
		if (i == table->n_philos)
		{
			if (check_meals(table))
				break ;
			i = 0;
		}
	}
	return (NULL);
}

/// @brief function to start the philosophers thread
/// retard the start of the loop to all the philosophers start at the same time
/// and if the philosopher are odd start a little later and print think message
/// @param philo 
void	init_thread(t_philin *philo)
{
	wait_to(philo->table->t_start, 1000);
	philo->lst_meal = get_time();
	if (philo->n % 2 != 0)
	{
		print("is thinking", philo);
		philo->think++;
		slp(philo->t_eat / 2);
	}
}

/// @brief function to create all the threads, the philosophers and the dead
/// start the print mutex and loop the creations of the philosophers threads
/// and end with the creation of the dead checker thread
/// @param table 
/// @return 
int	create_threads(t_table *table)
{
	int			i;

	i = 0;
	pthread_mutex_init(&(table->print), NULL);
	while (i < table->n_philos)
	{
		if (pthread_create(&table->philo[i]->thread, NULL, \
				philo, (void *)table->philo[i]))
			return (1);
		i++;
	}
	pthread_create(&table->c_dead, NULL, check_dead, (void *)table);
	return (0);
}

/// @brief function to wait all the threadds to end
/// @param table 
/// @return 
int	join_threads(t_table *table)
{
	int			i;

	i = 0;
	pthread_join(table->c_dead, NULL);
	while (i < table->n_philos)
	{
		pthread_join(table->philo[i]->thread, NULL);
		i++;
	}
	return (0);
}
