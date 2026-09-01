/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 14:33:54 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/01 16:23:01 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

t_dongle	*init_dongle(int n)
{
	t_dongle	*dongle;

	dongle = malloc(sizeof(t_dongle));
	if (dongle == NULL)
		return (NULL);
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
	{
		printf("Error in mutex create of %d dongle", dongle->n);
		return (NULL);
	}
	dongle->n = n;
	return (dongle);
}
