/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:20:01 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/20 16:28:36 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/// @brief funtion to reserv memory to the table and the philosophers
/// @param count numbers of philosophers
/// @param size size of the table / philosophers struct
/// @return the reserved struct
void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	s = (void *)malloc(count * size);
	if (!s)
		return (NULL);
	memset(s, '\0', count * size);
	return (s);
}

/// @brief check if the string is a positive number
/// @param c a string
/// @return -1 if it's  not a positive number, 0 if it is
int	ft_ispos_num(char *c)
{
	int		i;

	i = 0;
	while (c[i])
	{
		if (c[i] <= 57 && c[i] >= 48)
			i++;
		else
			return (-1);
	}
	return (0);
}

/// @brief turn a string into a positive ints
/// @param str  a string
/// @return -1 if it's not a positive number, or the number if it is
int	ft_atoi(char *str)
{
	int	i;
	int	k;
	int	l;

	i = 0;
	l = 1;
	k = 0;
	if (ft_ispos_num(str) == -1)
		return (-1);
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			l = -1;
	while (str[i] >= '0' && str[i] <= '9')
		k = (str[i++] - '0') + (k * 10);
	return (k * l);
}

/// @brief function to create the table and controll dthe data
/// @return return the table if the creation is correct or NULL if it isn't
t_table	*parse(int argc, char **argv)
{
	t_table		*table;

	if (argc < 5 || argc > 6)
		(printf("Wrong number of arguments.\n"), exit (0));
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 \
		|| ft_atoi(argv[4]) <= 0)
		(printf("Wrong arguments.\n"), exit (0));
	if (argc == 6)
		if (ft_atoi(argv[5]) <= 0)
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
	return (table);
}
