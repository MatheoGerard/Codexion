/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 19:24:16 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/04 19:25:49 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

int	is_terminated(t_coders *coder)
{
	int	is_stoped;

	pthread_mutex_lock(&coder->table_link->mutex_stop);
	is_stoped = coder->table_link->stop;
	pthread_mutex_unlock(&coder->table_link->mutex_stop);
	return (is_stoped);
}
