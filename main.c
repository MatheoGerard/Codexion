/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 11:15:51 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/08 12:47:19 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/codexion.h"

int	main(int ac, char **av)
{
	t_parse_data	*data;
	int	check_max;

	check_max = 0;
	if (!check_args_nb(ac))
		return (0);
	data = data_init(av, &check_max);
	if (check_max == 1)
		return (0);
	if (!validate_coders_data(data) || !validate_timers_data(data))
		return (0);
	printf("%d\n", data->number_of_coders);
}
