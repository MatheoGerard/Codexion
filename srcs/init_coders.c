/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 16:20:45 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/02 20:48:40 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

t_coders	*init_coders(int i, t_table *table)
{
	t_coders	*coder;

	coder = malloc(sizeof(t_coders));
	if (coder == NULL)
		return (NULL);
	coder->data = table->data;
	if (i == 1)
	{
		coder->right = table->dongles[table->data->number_of_coders - 1];
		coder->left = table->dongles[0];
	}
	else
	{
		coder->right = table->dongles[i - 2];
		coder->left = table->dongles[i - 1];
	}
	pthread_mutex_init(&coder->mutex, NULL);
	pthread_mutex_init(&coder->mutex_finish, NULL);
	coder->n = i;
	coder->is_finish = 0;
	coder->compile_nb = 0;
	coder->last_compile_time = 0;
	coder->table_link = table;
	if (pthread_create(&coder->id, NULL, coders_routine, coder) != 0)
	{
		printf("Error in thread create of %d coder", coder->n);
		return (NULL);
	}
	return (coder);
}
