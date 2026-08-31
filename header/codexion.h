/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 09:05:29 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/31 16:12:34 by mgerard          ###   ########.fr       */
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
	char	*scheduler;
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
}	t_parse_data;

typedef struct s_dongles
{
	int	state;
	int	n;
	pthread_mutex_t	mutex;
}	t_dongle;

typedef struct s_coders
{
	t_parse_data	*data;
	pthread_t	id;
	int			n;
	t_dongle	*left;
	t_dongle	*right;
	int			compile_nb;
}	t_coders;

typedef struct s_node
{
	t_coders	*content;
	struct s_node	*next;
}	t_node;

typedef struct s_wait_queue
{
	void	*first;
	void	*last;
}	t_wait_queue;

typedef struct s_table
{
	t_parse_data	*data;
	t_coders	**coders;
	t_dongle	**dongles;
	t_wait_queue	*queue;
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

t_coders	*init_coders(int index, t_table *table);
t_dongle	*init_dongle(int n);
t_table	*init_table(t_parse_data *data);
void	*coders_routine(void *args);
int	set_start_time(t_parse_data *data);
time_t	get_time(t_parse_data *data);
t_wait_queue	*create_coder_node(void *content);
t_wait_queue	*find_last_coder(t_wait_queue *queue);
void	add_coder_to_queue(t_wait_queue **queue, t_wait_queue *coder);
void	print_status(t_coders *coder, char *status);
void	take_dongle(t_coders *coder);
void	release_dongles(t_coders *coder);

#endif
