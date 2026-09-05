/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 11:12:54 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/05 11:12:57 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_parse_data
{
	struct timeval	tv;
	char			*scheduler;
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
}	t_parse_data;

typedef struct s_dongles
{
	int				state;
	int				n;
	time_t			available;
	struct s_heap	*heap;
	char			*scheduler;
	pthread_mutex_t	mutex_heap;
	pthread_mutex_t	mutex_time;
	pthread_mutex_t	mutex;
}	t_dongle;

typedef struct s_coders
{
	t_parse_data	*data;
	pthread_t		id;
	int				n;
	t_dongle		*left;
	t_dongle		*right;
	int				compile_nb;
	pthread_mutex_t	mutex;
	time_t			last_compile_time;
	struct s_table	*table_link;
	pthread_mutex_t	mutex_finish;
	int				is_finish;
}	t_coders;

typedef struct s_node
{
	t_coders	*content;
	long long	key;
}	t_node;

typedef struct s_heap
{
	t_node	nodes[2];
	int		size;
}	t_heap;

typedef struct s_table
{
	pthread_t		monitor;
	t_parse_data	*data;
	t_coders		**coders;
	t_dongle		**dongles;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_stop;
	int				stop;
}	t_table;

t_parse_data	*data_init(char **av, int ac, int *check_max);
int				check_args_nb(int nb_args);
int				ft_atoi(char *str, int *check_max);
int				ft_strcmp(char *s1, char *s2);
int				validate_all(t_parse_data *data);
int				validate_coders_data(t_parse_data *data);
int				validate_timers_data(t_parse_data *data);
int				validate_scheduler(t_parse_data *data);
int				validate_number_compiles(t_parse_data *data);
int				validate_dongle_cooldown(t_parse_data *data);
void			free_all(t_parse_data *data);

t_coders		*init_coders(int index, t_table *table);
t_dongle		*init_dongle(int n, t_parse_data *data);
t_table			*init_table(t_parse_data *data);

void			*coders_routine(void *args);
int				set_start_time(t_parse_data *data);
time_t			get_time(t_parse_data *data);
void			print_status(t_coders *coder, char *status, int force);
void			take_dongle(t_coders *coder);
void			release_dongles(t_coders *coder);
void			*death_check(void *args);
void			ft_usleep(long time_to_wait, t_coders *coder);
void			end_free(t_table *table);
int				is_terminated(t_coders *coder);

t_heap			*init_heap(void);
void			heap_insert(t_heap *heap, struct s_coders *coder, time_t key);
struct s_coders	*heap_extract_min(t_heap *heap);
struct s_coders	*heap_peek(t_heap *heap);

#endif
