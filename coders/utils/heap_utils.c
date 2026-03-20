/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:19:35 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/20 09:50:15 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	set_variables(t_heap *heap, t_node *tmp, int *index, int *left);
static void	swap(t_node *parent, t_node *new_node);

void	heap_insert(t_heap *heap, t_node new_node)
{
	int	parent_index;
	int	curr_index;

	curr_index = heap->size;
	heap->nodes[curr_index] = new_node;
	parent_index = (curr_index - 1) / 2;
	while (curr_index > 0 && heap->nodes[curr_index].deadline
		< heap->nodes[parent_index].deadline)
	{
		swap(&heap->nodes[parent_index], &heap->nodes[curr_index]);
		curr_index = parent_index;
		parent_index = (curr_index - 1) / 2;
	}
	heap->size++;
}

t_node	heap_extract_min(t_heap *heap)
{
	t_node	tmp;
	int		index;
	int		left;
	int		right;
	int		smallest_child_index;

	set_variables(heap, &tmp, &index, &left);
	heap->nodes[0] = heap->nodes[heap->size - 1];
	heap->size--;
	while (left < heap->size)
	{
		right = (index * 2) + 2;
		smallest_child_index = left;
		if (right < heap->size && heap->nodes[right].deadline
			< heap->nodes[left].deadline)
			smallest_child_index = right;
		if (heap->nodes[index].deadline
			<= heap->nodes[smallest_child_index].deadline)
			break ;
		swap(&heap->nodes[index], &heap->nodes[smallest_child_index]);
		index = smallest_child_index;
		left = (index * 2) + 1;
	}
	return (tmp);
}

static void	set_variables(t_heap *heap, t_node *tmp, int *index, int *left)
{
	*tmp = heap->nodes[0];
	*index = 0;
	*left = 1;
}

static void	swap(t_node *parent, t_node *node)
{
	t_node	tmp;

	tmp = *parent;
	*parent = *node;
	*node = tmp;
}
