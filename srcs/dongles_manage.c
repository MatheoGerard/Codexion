/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:39:51 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/31 16:12:19 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	take_dongle(t_coders *coder)
{
	pthread_mutex_lock(&coder->left);
	print_status(coder->n, "has taken a dongle");
	pthread_mutex_lock(&coder->right);
	print_status(coder->n, "has taken a dongle");
}

void	release_dongles(t_coders *coder)
{
	pthread_mutex_unlock(&coder->left);
	pthread_mutex_unlock(&coder->right);
}
