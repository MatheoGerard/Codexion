/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 11:17:06 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/21 10:18:57 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

void	print_status(t_coders *coder, char *status)
{
	printf("timestamp_in_ms %d %s\n", coder->n, status);
}

void	coders_debug(t_parse_data *data, t_coders *coder)
{
	print_status(coder, "is debugging");
	coder->compile_nb++;
	usleep(data->time_to_debug * 1000);
}

void	*coders_routine(void *args)
{
	t_coders	*coder;

	coder = (t_coders *)args;
	while (coder->compile_nb < coder->data->number_of_compiles_required)
		coders_debug(coder->data, coder);
	return (NULL);
}
