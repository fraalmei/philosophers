/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:34:20 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/14 19:00:07 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	init_thread(t_philin *philo)
{
	wait_to(philo->table->t_start, 1000);
	philo->lst_meal = get_time();
	if (philo->n % 2 == 0 && philo->table->n_philos > 1)
		slp(philo->table->t_eat / 2);
}

int	create_process(t_table *table)
{
	int			i;

	i = 0;
	while (i < table->n_philos)
	{
		table->philo[i]->pid = fork();
		if (table->philo[i]->pid == 0)
			return (philo(&(table->philo[i])));
		i++;
	}
	return (0);
}

int	join_process(t_table *table)
{
	int			i;
	int			ret;

	i = 0;
	ret = 1;
	while (i < table->n_philos)
	{
		if (waitid(table->philo[i]->pid, NULL, 0) == -1)
			ret = 0;
		i++;
	}
	return (ret);
}
