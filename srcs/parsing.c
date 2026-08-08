/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 09:34:00 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/08 14:27:50 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

int	check_args_nb(int nb_args)
{
	if (nb_args < 9)
	{
		printf("Not enough arguments!\n");
		return (0);
	}
	else if (nb_args > 9)
	{
		printf("To much arguments!\n");
		return (0);
	}
	else
		return (1);
}

t_parse_data	*data_init(char **av, int *check_max)
{
	t_parse_data	*data;

	data = malloc(1 * sizeof(t_parse_data));
	data->number_of_coders = ft_atoi(av[1], check_max);
	data->time_to_burnout = ft_atoi(av[2], check_max);
	data->time_to_compile = ft_atoi(av[3], check_max);
	data->time_to_debug = ft_atoi(av[4], check_max);
	data->time_to_refactor = ft_atoi(av[5], check_max);
	data->number_of_compiles_required = ft_atoi(av[6], check_max);
	data->dongle_cooldown = ft_atoi(av[7], check_max);
	data->scheduler = av[8];
	return (data);
}
