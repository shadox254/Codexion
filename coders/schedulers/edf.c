/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:07:36 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/19 15:42:02 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	edf_compiling(t_coder *coder);
static void	do_compile(t_coder *coder, t_dongle *dongle1, t_dongle *dongle2);
static void	put_heap(t_coder *coder, t_dongle *dongle);
static void	wait_for_dongles(t_coder *coder, t_dongle *dongle1, t_dongle *dongle2);

void	edf(t_coder *coder)
{
	while (is_simu(coder->data) == 1 && have_finish(coder) == 0)
	{
		edf_compiling(coder);
		debugging_and_refactoring(coder);
	}
}

static void	edf_compiling(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	set_order(coder, &first, &second);
	put_heap(coder, first);
	put_heap(coder, second);
	do_compile(coder, first, second);
	first->last_release = get_time();
	pthread_cond_broadcast(&first->cond);
	pthread_mutex_unlock(&first->lock);
	second->last_release = get_time();
	pthread_cond_broadcast(&second->cond);
	pthread_mutex_unlock(&second->lock);
}

static void	do_compile(t_coder *coder, t_dongle *dongle1, t_dongle *dongle2)
{
	wait_for_dongles(coder, dongle1, dongle2);
	pthread_mutex_lock(&coder->data_lock);
	coder->last_compile_start = get_time();
	pthread_mutex_unlock(&coder->data_lock); 
	print_action(coder, COMPILING);
	custom_sleep(coder->data->rules.time_to_compile, coder->data);
	coder->nbr_of_compilations++;
}


static void	put_heap(t_coder *coder, t_dongle *dongle)
{
	long long	deadline;
	int			coder_id;
	t_node		node;

	pthread_mutex_lock(&coder->data_lock);
	deadline = coder->last_compile_start + coder->data->rules.time_to_burnout;
	coder_id = coder->id;
	pthread_mutex_unlock(&coder->data_lock);
	create_node(&node, coder_id, deadline);
	pthread_mutex_lock(&dongle->lock);
	heap_insert(&dongle->heap, node);
	pthread_mutex_unlock(&dongle->lock);
}

static void	wait_for_dongles(t_coder *coder, t_dongle *dongle1, t_dongle *dongle2)
{
	long long	now;

	pthread_mutex_lock(&dongle1->lock);
	pthread_mutex_lock(&dongle2->lock);
	while (is_simu(coder->data))
	{
		if (dongle1->heap.nodes[0].coder_id == coder->id && dongle2->heap.nodes[0].coder_id == coder->id)
		{
			now = get_time();
			if (now >= dongle1->last_release + coder->data->rules.dongle_cooldown && now >= dongle2->last_release + coder->data->rules.dongle_cooldown)
				break ;
			pthread_mutex_unlock(&dongle1->lock);
			pthread_mutex_unlock(&dongle2->lock);
			custom_sleep(5, coder->data);
			pthread_mutex_lock(&dongle1->lock);
			pthread_mutex_lock(&dongle2->lock);
			continue ;
		}
		pthread_mutex_unlock(&dongle2->lock);
		pthread_cond_wait(&dongle1->cond, &dongle1->lock);
		pthread_mutex_lock(&dongle2->lock);
	}
	heap_extract_min(&dongle1->heap);
	heap_extract_min(&dongle2->heap);
	print_action(coder, TAKE_DONGLE);
	print_action(coder, TAKE_DONGLE);
}
