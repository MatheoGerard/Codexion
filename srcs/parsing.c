/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 09:34:00 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/07 21:12:50 by mgerard          ###   ########.fr       */
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

t_parse_data	*data_init(char **av)
{
	t_parse_data	*data;

	data = malloc(1 * sizeof(t_parse_data));
	data->number_of_coders = atoi(av[1]);
	data->time_to_burnout = atoi(av[2]);
	data->time_to_compile = atoi(av[3]);
	data->time_to_debug = atoi(av[4]);
	data->time_to_refactor = atoi(av[5]);
	data->number_of_compiles_required = atoi(av[6]);
	data->dongle_cooldown = atoi(av[7]);
	data->scheduler = av[8];
	return (data);
}

int	validate_coders_data(t_parse_data *data)
{
	int	coders_min;

	coders_min = 1;
	if (data->number_of_coders < coders_min)
	{
		printf("Not enough coders (must be a least %d)\n", coders_min);
		return (0);
	}
	return (1);
}

int	validate_timers_data(t_parse_data *data)
{
	int	time_min;

	time_min = 0;
	if (data->time_to_burnout < time_min)
	{
		printf("Not enough time to burnout (must be a least %d)\n", time_min);
		return (0);
	}
	if (data->time_to_compile < time_min)
	{
		printf("Not enough time to compile (must be a least %d)\n", time_min);
		return (0);
	}
	if (data->time_to_debug < time_min)
	{
		printf("Not enough time to debug (must be a least %d)\n", time_min);
		return (0);
	}
	if (data->time_to_refactor < time_min)
	{
		printf("Not enough time to refactor (must be a least %d)\n", time_min);
		return (0);
	}
	return (1);
}
