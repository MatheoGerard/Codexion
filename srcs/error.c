/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 12:53:06 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/05 11:44:07 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

void	free_all(t_parse_data *data)
{
	free(data);
}

void	free_coders(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data->number_of_coders)
	{
		pthread_mutex_destroy(&table->coders[i]->mutex);
		pthread_mutex_destroy(&table->coders[i]->mutex_finish);
		free(table->coders[i]);
		i++;
	}
}

void	free_dongles(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data->number_of_coders)
	{
		pthread_mutex_destroy(&table->dongles[i]->mutex);
		pthread_mutex_destroy(&table->dongles[i]->mutex_heap);
		pthread_mutex_destroy(&table->dongles[i]->mutex_time);
		free(table->dongles[i]->heap);
		free(table->dongles[i]);
		i++;
	}
}

void	free_table(t_table *table)
{
	free(table->data);
	pthread_mutex_destroy(&table->mutex_print);
	pthread_mutex_destroy(&table->mutex_stop);
	free(table->coders);
	free(table->dongles);
	free(table);
}

void	end_free(t_table *table)
{
	free_dongles(table);
	free_coders(table);
	free_table(table);
}
