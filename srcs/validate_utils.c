/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 12:49:38 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/05 11:07:31 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

int	validate_coders_data(t_parse_data *data)
{
	int	coders_min;

	coders_min = 1;
	if (data->number_of_coders < coders_min)
	{
		printf("Not enough coders (must be at least %d)\n", coders_min);
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
		printf("Not enough time to burnout (must be at least %d)\n", time_min);
		return (0);
	}
	if (data->time_to_compile < time_min)
	{
		printf("Not enough time to compile (must be at least %d)\n", time_min);
		return (0);
	}
	if (data->time_to_debug < time_min)
	{
		printf("Not enough time to debug (must be at least %d)\n", time_min);
		return (0);
	}
	if (data->time_to_refactor < time_min)
	{
		printf("Not enough time to refactor (must be at least %d)\n", time_min);
		return (0);
	}
	return (1);
}

int	validate_scheduler(t_parse_data *data)
{
	if (ft_strcmp(data->scheduler, "fifo") != 0
		&& ft_strcmp(data->scheduler, "edf") != 0)
	{
		printf("Scheduler must be 'fifo' or 'edf'\n");
		return (0);
	}
	return (1);
}

int	validate_number_compiles(t_parse_data *data)
{
	int	loop_min;

	loop_min = 1;
	if (data->number_of_compiles_required < loop_min)
	{
		printf("Not enough number of compiles required ");
		printf("(must be at least %d)", loop_min);
		return (0);
	}
	return (1);
}

int	validate_dongle_cooldown(t_parse_data *data)
{
	int	min_cooldown;

	min_cooldown = 0;
	if (data->dongle_cooldown < min_cooldown)
	{
		printf("Not enough dongle cooldown ");
		printf("(must be at least %d)", min_cooldown);
		return (0);
	}
	return (1);
}
