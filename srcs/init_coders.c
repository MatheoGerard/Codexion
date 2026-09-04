/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 16:20:45 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/04 19:38:08 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

void	give_dongles_to_coder(int i, t_coders *coder, t_table *table)
{
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
}

int	init_all_mutex(t_coders *coder)
{
	if (pthread_mutex_init(&coder->mutex, NULL) != 0)
	{
		printf("Error in mutex create of %d coder", coder->n);
		return (0);
	}
	if (pthread_mutex_init(&coder->mutex_finish, NULL) != 0)
	{
		printf("Error in mutex finish create of %d coder", coder->n);
		return (0);
	}
	return (1);
}

t_coders	*init_coders(int i, t_table *table)
{
	t_coders	*coder;

	coder = malloc(sizeof(t_coders));
	if (coder == NULL)
		return (NULL);
	coder->data = table->data;
	give_dongles_to_coder(i, coder, table);
	if (!init_all_mutex(coder))
		return (NULL);
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
