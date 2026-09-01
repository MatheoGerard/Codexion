/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 16:21:03 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/01 19:39:17 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

t_coders	**create_coders(t_parse_data *data, t_table *table)
{
	t_coders	**coders;
	int			i;

	coders = malloc(data->number_of_coders * sizeof(t_coders));
	if (coders == NULL)
		return (NULL);
	i = 0;
	while (i < data->number_of_coders)
	{
		coders[i] = init_coders(i + 1, table);
		i++;
	}
	return (coders);
}

t_dongle	**create_dongles(t_parse_data *data)
{
	t_dongle	**dongles;
	int			i;

	dongles = malloc(data->number_of_coders * sizeof(t_dongle));
	if (dongles == NULL)
		return (NULL);
	i = 0;
	while (i < data->number_of_coders)
	{
		dongles[i] = init_dongle(i + 1);
		i++;
	}
	return (dongles);
}

t_table	*init_table(t_parse_data *data)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	if (pthread_mutex_init(&table->mutex_print, NULL) != 0)
	{
		printf("Error in mutex create of table");
		return (NULL);
	}
	table->data = data;
	table->dongles = create_dongles(data);
	if (table->dongles == NULL)
		return (NULL);
	table->coders = create_coders(data, table);
	if (table->coders == NULL)
		return (NULL);
	return (table);
}
