/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_heap_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 16:15:24 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/05 16:19:41 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

void	protected_extract_heap(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex_heap);
	heap_extract_min(dongle->heap);
	pthread_mutex_unlock(&dongle->mutex_heap);
}

void	protected_heap_insert(t_dongle *dongle, struct s_coders *coder,
				time_t key)
{
	pthread_mutex_lock(&dongle->mutex_heap);
	heap_insert(dongle->heap, coder, key);
	pthread_mutex_unlock(&dongle->mutex_heap);
}
