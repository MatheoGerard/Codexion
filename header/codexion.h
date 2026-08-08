/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 09:05:29 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/08 10:25:21 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

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

t_parse_data	*data_init(char **av);
int				check_args_nb(int nb_args);
int				validate_coders_data(t_parse_data *data);
int				validate_timers_data(t_parse_data *data);
int				ft_atoi(char *str);

#endif
