/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:48:57 by fraalmei          #+#    #+#             */
/*   Updated: 2023/07/14 18:27:10 by fraalmei         ###   ########.fr       */
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
	pid_t						pid;
	int							n;
	t_forkin					*r_fork;
	int							r_frk;
	t_forkin					*l_fork;
	int							l_frk;
	int							color;
	long						lst_meal;
	int							meals;
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
	t_forkin			**fork;
	t_philin			**philo;
}				t_table;

	// main.c
void		*philo(void *arg);
void		exe_threads(t_table *table);
t_table		*parse(int argc, char **argv);

	//parse.c
void		parse_philos(t_table *table);
t_table		*parse(int argc, char **argv);

	// philosophers.c
int			dead_p(t_philin *philo);
t_philin	*new_phil(int n);
int			create_philos(t_table *table);

	// utils.c
int			ft_ispos_num(char *c);
void		wait_to(long start_time, long time);
void		slp(long tm);
long		get_time(void);
void		print(char *str, t_philin *phil);
void		free_all(t_table *table);
void		*ft_calloc(size_t count, size_t size);
int			ft_atoi(char *str);

	// threads.c
void		init_thread(t_philin *philo);
int			create_process(t_table *table);
int			join_process(t_table *table);

	// forks.c
int			take_f(t_philin *philo);
void		drop_f(t_philin *philo);

#endif
