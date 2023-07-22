/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:58:58 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/22 11:15:06 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/* void	leaks(void)
{
	system("leaks -q philo");
} */
	/* atexit(leaks); */

/// @brief main function to start the program
/// @param argc the number of datawe must in
/// @param argv the infomation above the philosophers
/// number of philosophers, time to eat, sleep, die, and number of times to eat
/// @return 1 if fails the creation of the table or 0 if the program runs
int	main(int argc, char	**argv)
{
	t_table					*table;

	table = parse(argc, argv);
	if (!table)
		return (1);
	if (create_philos(table))
		return (free_all(table));
	if (create_threads(table))
		return (free_all(table));
	join_threads(table);
	return (free_all(table));
}
