/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:45:28 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/12 16:47:30 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief obtiene el tiemo actua del reloj
/// le añades un tiempo la diferencia entre ellos
/// @param tm 
/// @return 
long	get_time(void)
{
	long						i;
	struct timeval				tv;

	gettimeofday(&tv, NULL);
	i = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (i);
}

void	print(char *str, t_philin *phil)
{
	long	init;

	init = get_time() - phil->table->t_start;
	pthread_mutex_lock(&phil->table->print);
	if (!phil->table->dead)
		printf("%li \033[0;%im%i\033[0;37m %s\n", \
			init - 1000, phil->color, phil->n, str);
	pthread_mutex_unlock(&phil->table->print);
}

void	free_all(t_table *table)
{
	while (table->n_philos--)
	{
		free(table->philo[table->n_philos]);
		free(table->fork[table->n_philos]);
	}
	free(table->philo);
	free (table->threads);
	free (table);
}
