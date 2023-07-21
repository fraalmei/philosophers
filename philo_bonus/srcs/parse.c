/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:20:01 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/12 16:49:03 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	parse_philos(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->n_philos)
	{
		table->philo[i]->table = table;
		i++;
	}
}

/// @brief funcion para crear la mesa y controlar los datos
/// @return devuelve la mesa o sale si los datos no son correctos
t_table	*parse(int argc, char **argv)
{
	t_table		*table;

	if (argc < 5 || argc > 6)
		(printf("Wrong number of arguments.\n"), exit (0));
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 \
		|| ft_atoi(argv[4]) <= 0)
		(printf("Wrong arguments.\n"), exit (0));
	if (argc == 6)
		if (ft_atoi(argv[5]) < 0)
			(printf("Wrong arguments.\n"), exit (0));
	table = (t_table *)ft_calloc(sizeof(t_table), 1);
	if (!table)
		return (NULL);
	table->n_philos = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->n_eats = -1;
	if (argc == 6)
		table->n_eats = ft_atoi(argv[5]);
	table->t_start = get_time();
	table->dead = 0;
	table->threads = NULL;
	return (table);
}
