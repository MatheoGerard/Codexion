/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 09:05:29 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/07 21:04:54 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>

typedef struct	s_parse_data
{
	int	number_of_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	number_of_compiles_required;
	int	dongle_cooldown;
	char	*scheduler;
}	t_parse_data;

int	check_args_nb(int nb_args);
t_parse_data	*data_init(char **av);
int	validate_coders_data(t_parse_data *data);
int	validate_timers_data(t_parse_data *data);

#endif
