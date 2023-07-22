/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:35:18 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/22 15:21:32 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief function to retard the start of the philo function
/// @param start_time is the initial time of the table
/// @param time is the time we want the threads to wait
void	wait_to(long start_time, long time)
{
	while (1)
	{
		if (get_time() - start_time >= time)
			break ;
		usleep(10);
	}
}

/// @brief custom sleep function
/// @param tm time to wait
void	slp(long tm)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < tm)
		usleep(100);
}

/// @brief get the actual time of the clock
/// @return the time in miliseconds
long	get_time(void)
{
	long						i;
	struct timeval				tv;

	gettimeofday(&tv, NULL);
	i = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (i);
}

/// @brief function to print a message with the time ffrom the start
/// the number of philosopher an the message
/// @param str the message
/// @param phil the philosopher
void	print(char *str, t_philin *phil)
{
	pthread_mutex_lock(&phil->table->print);
	if (!phil->table->dead)
	{
		printf("%li \033[0;%im%i \033[0;37m%s\n", (get_time() - \
			phil->table->t_start - 1000), phil->color, phil->n + 1, str);
		pthread_mutex_unlock(&phil->table->print);
	}
	else
		exit (0);
}

/// @brief function to free and destroy the mutexes and the allocatedd structs
/// @param table 
/// @return 
int	free_all(t_table *table)
{
	while (table->n_philos--)
	{
		if (table->philo[table->n_philos])
		{
			pthread_mutex_destroy \
				(&table->philo[table->n_philos]->fork_plus.use);
			pthread_mutex_destroy \
				(&table->philo[table->n_philos]->philo);
			free(table->philo[table->n_philos]);
		}
	}
	free(table->philo);
	pthread_mutex_destroy(&table->print);
	free (table);
	return (0);
}
