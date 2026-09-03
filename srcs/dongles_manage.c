/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:39:51 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/03 22:43:06 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

void	swap_coders(t_dongle *dongle)
{
	struct s_coders	*tmp;

	tmp = dongle->workers[0];
	dongle->workers[0] = dongle->workers[1];
	dongle->workers[1] = tmp;
}

long long	get_available_time(t_dongle *dongle)
{
	long long	dongle_time;

	pthread_mutex_lock(&dongle->mutex_time);
	dongle_time = dongle->available;
	pthread_mutex_unlock(&dongle->mutex_time);
	return dongle_time;
}

static void take_dongle_one(t_coders *coder, t_dongle *dongle)
{
	long long now;

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
}

void take_dongle(t_coders *coder)
{
	take_dongle_one(coder, coder->left);
	print_status(coder, "has taken a dongle", 0);
	take_dongle_one(coder, coder->right);
	print_status(coder, "has taken a dongle", 0);
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
