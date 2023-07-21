/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:58:58 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/21 18:49:05 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/* void	leaks(void)
{
	system("leaks -q philo");
}

	atexit(leaks); */

void	*philo(void *arg)
{
	t_philin					*philo;
	int							i;

	philo = ((t_philin *) arg);
	init_thread(philo);
	i = 0;
	while (philo->table->dead == 0)
	{
		if (take_f(philo))
		{
			print("is eating", philo);
			slp(philo->table->t_eat);
			drop_f(philo);
			if (++philo->meals == philo->table->n_eats)
				break ;
			print("is sleeping", philo);
			slp(philo->table->t_sleep);
			i = 0;
		}
		if (dead_p(philo))
			continue ;
		if (i++ == 0)
			print("is thinking", philo);
	}
	pthread_exit (NULL);
}

void	exe_threads(t_table *table)
{
	create_philos(table);
	parse_philos(table);
}

/// @brief función main para iniciar el programa
/// @param argc la cantidad de datos que se deben introducir 4 o 5
/// @param argv la información de los filosofos (cantidad, 
/// tiemmpo hasta la muerte, tiempo para comer, tiempo para dormir y 
/// numero de veces que come)
/// @return 
int	main(int argc, char	**argv)
{
	t_table					*table;

	table = parse(argc, argv);
	if (!table)
		return (0);
	exe_threads(table);
	free_all(table);
	return (0);
}
