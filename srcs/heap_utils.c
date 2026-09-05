/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 15:10:06 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/05 16:25:02 by mgerard          ###   ########.fr       */
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

void	sift_down(t_heap *heap, int i)
{
	int		smallest;
	int		left;
	int		right;
	t_node	tmp;

	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		smallest = i;
		if (left < heap->size && heap->nodes[left].key
			< heap->nodes[smallest].key)
			smallest = left;
		if (right < heap->size && heap->nodes[right].key
			< heap->nodes[smallest].key)
			smallest = right;
		if (smallest == i)
			break ;
		tmp = heap->nodes[i];
		heap->nodes[i] = heap->nodes[smallest];
		heap->nodes[smallest] = tmp;
		i = smallest;
	}
}

struct s_coders	*heap_extract_min(t_heap *heap)
{
	struct s_coders	*min_coder;

	if (heap->size == 0)
		return (NULL);
	min_coder = heap->nodes[0].content;
	heap->size--;
	heap->nodes[0] = heap->nodes[heap->size];
	sift_down(heap, 0);
	return (min_coder);
}

void	heap_insert(t_heap *heap, struct s_coders *coder, time_t key)
{
	int		i;
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

struct s_coders	*heap_peek(t_heap *heap)
{
	if (heap->size == 0)
		return (NULL);
	return (heap->nodes[0].content);
}
