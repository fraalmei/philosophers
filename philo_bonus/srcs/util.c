/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:35:18 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/12 11:45:48 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief comprobante de si el string es un numero positivo
/// @param c string
/// @return -1 si no es numero, 0 si lo es
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

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	s = (void *)malloc(count * size);
	if (!s)
		return (NULL);
	memset(s, '\0', count * size);
	return (s);
}

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

void	wait_to(long start_time, long time)
{
	while (1)
	{
		if (get_time() - start_time >= time)
			break ;
	}
}

void	slp(long tm)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < tm)
		usleep(10);
}
