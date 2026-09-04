/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:39:51 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/04 21:59:07 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

long long	get_available_time(t_dongle *dongle)
{
	long long	dongle_time;

	pthread_mutex_lock(&dongle->mutex_time);
	dongle_time = dongle->available;
	pthread_mutex_unlock(&dongle->mutex_time);
	return dongle_time;
}

static long long compute_key(t_coders *coder, t_dongle *dongle)
{
	t_parse_data *data;

	data = coder->table_link->data;
	if (ft_strcmp(dongle->scheduler, "edf") == 0)
		return (coder->last_compile_time + data->time_to_burnout);
	return (get_time(data));
}

static void take_dongle_one(t_coders *coder, t_dongle *dongle)
{
	long long now;

	pthread_mutex_lock(&dongle->mutex_heap);
	heap_insert(dongle->heap, coder, compute_key(coder, dongle));
	pthread_mutex_unlock(&dongle->mutex_heap);
	while (1)
	{
		pthread_mutex_lock(&dongle->mutex_heap);
		if (dongle->heap->size > 0 && heap_peek(dongle->heap) == coder)
		{
			pthread_mutex_unlock(&dongle->mutex_heap);
			break ;
		}
		pthread_mutex_unlock(&dongle->mutex_heap);
		usleep(200);
	}

	pthread_mutex_lock(&dongle->mutex);
	while (1)
	{
		now = get_time(coder->table_link->data);
		if (now >= get_available_time(dongle))
			break;
		pthread_mutex_unlock(&dongle->mutex);
		usleep(500);
		pthread_mutex_lock(&dongle->mutex);
	}

	pthread_mutex_lock(&dongle->mutex_heap);
	heap_extract_min(dongle->heap);
	pthread_mutex_unlock(&dongle->mutex_heap);
}

void take_dongle(t_coders *coder)
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
	coder->left->available = get_time(coder->table_link->data) + coder->table_link->data->dongle_cooldown;
	pthread_mutex_unlock(&coder->left->mutex_time);
	pthread_mutex_unlock(&coder->left->mutex);
	pthread_mutex_lock(&coder->right->mutex_time);
	coder->right->available = get_time(coder->table_link->data) + coder->table_link->data->dongle_cooldown;
	pthread_mutex_unlock(&coder->right->mutex_time);
	pthread_mutex_unlock(&coder->right->mutex);
}
