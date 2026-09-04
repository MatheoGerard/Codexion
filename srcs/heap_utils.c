/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 15:10:06 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/04 17:26:41 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

t_heap	*init_heap(void)
{
	t_heap	*heap;

	heap = malloc(sizeof(t_heap));
	if (heap == NULL)
		return (NULL);
	heap->size = 0;
	return (heap);
}

void	heap_insert(t_heap *heap, struct s_coders *coder, time_t key)
{
	int			i;
	t_node	tmp;

	i = heap->size;
	heap->nodes[i].content = coder;
	heap->nodes[i].key = key;
	heap->size++;
	while (i > 0 && heap->nodes[i].key < heap->nodes[(i - 1) / 2].key)
	{
		tmp = heap->nodes[i];
		heap->nodes[i] = heap->nodes[(i - 1) / 2];
		heap->nodes[(i - 1) / 2] = tmp;
		i = (i - 1) / 2;
	}
}

struct s_coders	*heap_extract_min(t_heap *heap)
{
	struct s_coders	*min_coder;
	int					i;
	int					smallest;
	int					left;
	int					right;
	t_node			tmp;

	if (heap->size == 0)
		return (NULL);
	min_coder = heap->nodes[0].content;
	heap->size--;
	heap->nodes[0] = heap->nodes[heap->size];
	i = 0;
	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		smallest = i;
		if (left < heap->size && heap->nodes[left].key < heap->nodes[smallest].key)
			smallest = left;
		if (right < heap->size && heap->nodes[right].key < heap->nodes[smallest].key)
			smallest = right;
		if (smallest == i)
			break ;
		tmp = heap->nodes[i];
		heap->nodes[i] = heap->nodes[smallest];
		heap->nodes[smallest] = tmp;
		i = smallest;
	}
	return (min_coder);
}

//static int	is_my_turn(t_dongle *dongle, t_coders *coder)
//{
//	int	ret;
//
//	ret = 0;
//	pthread_mutex_lock(&dongle->mutex_heap);
//	if (dongle->heap->size > 0 && dongle->heap->nodes[0].content == coder)
//	{
//		heap_extract_min(dongle->heap);
//		ret = 1;
//	}
//	pthread_mutex_unlock(&dongle->mutex_heap);
//	return (ret);
//}

void wait_and_extract_from_heaps(t_coders *coder)
{
	while (1)
	{
		lock_both_heaps(coder);
		if (coder->left->heap->size > 0 && coder->left->heap->nodes[0].content == coder &&
			coder->right->heap->size > 0 && coder->right->heap->nodes[0].content == coder)
		{
			heap_extract_min(coder->left->heap);
			heap_extract_min(coder->right->heap);
			unlock_both_heaps(coder);
			break ;
		}
		unlock_both_heaps(coder);
		usleep(200);
	}
}

struct s_coders	*heap_peek(t_heap *heap)
{
	if (heap->size == 0)
		return (NULL);
	return (heap->nodes[0].content);
}
