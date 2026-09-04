/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 09:34:00 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/04 14:56:04 by mgerard          ###   ########.fr       */
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

int	is_digit(char c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

int	is_numbers(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac - 1)
	{
		j = 0;
		if (av[i][j] == '-' || av[i][j] == '+')
			j++;
		while (av[i][j] != '\0')
		{
			if (!is_digit(av[i][j]))
			{
				printf("Arg %d must be a number!\n", i);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

t_parse_data	*data_init(char **av, int ac, int *check_max)
{
	t_parse_data	*data;

	if (!is_numbers(av, ac))
		return (NULL);
	data = malloc(1 * sizeof(t_parse_data));
	if (data == NULL)
		return (NULL);
	if (!set_start_time(data))
		return (NULL);
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
