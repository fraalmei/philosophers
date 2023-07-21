/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:48:57 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/21 18:23:09 by fraalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philin				t_philin;
typedef struct s_table				t_table;
typedef struct s_forkin				t_forkin;

typedef struct s_forkin
{
	int					n;
	pthread_mutex_t		use;
	int					mutex;
}						t_forkin;

/// @brief estructura filosofo
/// todos los datos les contiene el propio filosofo
/// ademas con punteros a los tenedores
typedef struct s_philin
{
	int							n;
	int							color;
	long						lst_meal;
	int							meals;
	int							t_eat;
	int							t_sleep;
	int							think;
	t_forkin					*fork_minus;
	t_forkin					fork_plus;
	pthread_t					thread;
	struct s_table				*table;
}				t_philin;

typedef struct s_table
{
	int					n_philos;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eats;
	long				t_start;
	int					dead;
	t_philin			**philo;
	pthread_mutex_t		print;
	pthread_t			c_dead;
}				t_table;

	// main.c

	//parse.c
void		*ft_calloc(size_t count, size_t size);
int			ft_ispos_num(char *c);
int			ft_atoi(char *str);
t_table		*parse(int argc, char **argv);

	// philosophers.c
void		*philo(void *arg);
int			create_philos(t_table *table);

	// utils.c
void		wait_to(long start_time, long time);
void		slp(long tm);
long		get_time(void);
void		print(char *str, t_philin *phil);
int			free_all(t_table *table);

	// threads.c
void		*check_dead(void *arg);
void		init_thread(t_philin *philo);
int			create_threads(t_table *table);
int			join_threads(t_table *table);

#endif
