/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 11:15:51 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/07 21:06:01 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/codexion.h"

int	main(int ac, char **av)
{
	t_parse_data	*data;

	if (!check_args_nb(ac))
		return (0);
	data = data_init(av);
	if (!validate_coders_data(data) || !validate_timers_data(data))
		return (0);
}
