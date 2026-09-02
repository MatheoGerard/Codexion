/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:39:51 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/02 23:30:59 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

void	take_dongle(t_coders *coder)
{
	pthread_mutex_lock(&coder->left->mutex);
	print_status(coder, "has taken a dongle", 0);
	pthread_mutex_lock(&coder->right->mutex);
	print_status(coder, "has taken a dongle", 0);
}

void	release_dongles(t_coders *coder)
{
	pthread_mutex_unlock(&coder->left->mutex);
	pthread_mutex_unlock(&coder->right->mutex);
}
