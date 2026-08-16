/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 09:05:29 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/16 16:17:35 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_parse_data
{
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
	pthread_t	id;
	int			n;
	t_dongle	*left;
	t_dongle	*right;
}	t_coders;

typedef struct s_table
{
	t_coders	**coders;
	t_dongle	**dongles;
}	t_table;

t_parse_data	*data_init(char **av, int *check_max);
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

t_coders	*init_coders(int index);
t_dongle	*init_dongle(int n);
t_table	*init_table(t_parse_data *data);

#endif
