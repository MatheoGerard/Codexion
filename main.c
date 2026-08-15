/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 11:15:51 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/15 15:07:17 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/codexion.h"

int	main(int ac, char **av)
{
	t_parse_data	*data;
	int				check_max;
	t_table	*table;
	int				i;

	check_max = 0;
	if (!check_args_nb(ac))
		return (0);
	data = data_init(av, &check_max);
	if (check_max == 1)
	{
		free_all(data);
		return (0);
	}
	if (!validate_all(data))
		return (0);
	table = init_table(data);
	i = 0;
	while (i < data->number_of_coders)
	{
		pthread_join(table->coders[i]->id, NULL);
		printf("%d\n", table->coders[i]->n);
		i++;
	}
}
