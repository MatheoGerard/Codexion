/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 13:22:38 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/22 15:50:19 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

t_wait_queue	*create_coder_node(void *content)
{
	t_wait_queue	*new;

	new = malloc(sizeof(t_wait_queue));
	if (new == NULL)
		return (NULL);
	new->coder = content;
	new->next = NULL;
	return (new);
}

t_wait_queue	*find_last_coder(t_wait_queue *queue)
{
	if (!queue)
		return (NULL);
	while (queue->next != NULL)
		queue = queue->next;
	return (queue);
}

void	add_coder_to_queue(t_wait_queue **queue, t_wait_queue *coder)
{
	t_wait_queue	*last;

	if (!queue || !coder)
		return (NULL);
	if (!*queue)
	{
		*queue = coder;
		return ;
	}
	last = find_last_coder(*queue);
	last->next = new;
}
