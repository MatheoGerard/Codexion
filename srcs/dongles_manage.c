/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:39:51 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/05 16:10:46 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

void	wait_for_heap_turn(t_coders *coder, t_dongle *dongle)
{
	while (1)
	{
		pthread_mutex_lock(&dongle->mutex_heap);
		if (dongle->heap->size > 0
			&& heap_peek(dongle->heap) == coder)
		{
			pthread_mutex_unlock(&dongle->mutex_heap);
			break ;
		}
		pthread_mutex_unlock(&dongle->mutex_heap);
		usleep(200);
	}
}

void	wait_for_dongle_available(t_coders *coder, t_dongle *dongle)
{
	time_t	now;

	pthread_mutex_lock(&dongle->mutex);
	while (1)
	{
		now = get_time(coder->table_link->data);
		if (now >= get_available_time(dongle))
			break ;
		pthread_mutex_unlock(&dongle->mutex);
		usleep(500);
		pthread_mutex_lock(&dongle->mutex);
	}
}

void	take_dongle_one(t_coders *coder, t_dongle *dongle)
{
	protected_heap_insert(dongle, coder, compute_key(coder, dongle));
	wait_for_heap_turn(coder, dongle);
	wait_for_dongle_available(coder, dongle);
	protected_extract_heap(dongle);
}

void	take_dongle(t_coders *coder)
{
	if (coder->n % 2 == 0)
	{
		take_dongle_one(coder, coder->left);
		print_status(coder, "has taken a dongle", 0);
		take_dongle_one(coder, coder->right);
		print_status(coder, "has taken a dongle", 0);
	}
	else
	{
		take_dongle_one(coder, coder->right);
		print_status(coder, "has taken a dongle", 0);
		take_dongle_one(coder, coder->left);
		print_status(coder, "has taken a dongle", 0);
	}
}

void	release_dongles(t_coders *coder)
{
	pthread_mutex_lock(&coder->left->mutex_time);
	coder->left->available = get_time(coder->table_link->data)
		+ coder->table_link->data->dongle_cooldown;
	pthread_mutex_unlock(&coder->left->mutex_time);
	pthread_mutex_unlock(&coder->left->mutex);
	pthread_mutex_lock(&coder->right->mutex_time);
	coder->right->available = get_time(coder->table_link->data)
		+ coder->table_link->data->dongle_cooldown;
	pthread_mutex_unlock(&coder->right->mutex_time);
	pthread_mutex_unlock(&coder->right->mutex);
}
