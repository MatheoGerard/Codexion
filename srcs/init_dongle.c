/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 14:33:54 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/04 15:45:46 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

t_dongle	*init_dongle(int n, t_parse_data *data)
{
	t_dongle	*dongle;

	dongle = malloc(sizeof(t_dongle));
	if (dongle == NULL)
		return (NULL);
	dongle->n = n;
	dongle->available = 0;
	dongle->scheduler = data->scheduler;
	dongle->heap = init_heap();
	dongle->heap->size = 0;
	if (pthread_mutex_init(&dongle->mutex_time, NULL) != 0)
	{
		printf("Error in mutex time create of %d dongle", dongle->n);
		return (NULL);
	}
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
	{
		printf("Error in mutex create of %d dongle", dongle->n);
		return (NULL);
	}
	if (pthread_mutex_init(&dongle->mutex_heap, NULL) != 0)
	{
		printf("Error in mutex heap create of %d dongle", dongle->n);
		return (NULL);
	}
	return (dongle);
}
