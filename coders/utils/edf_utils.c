/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:32:05 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/20 15:46:36 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	wait_for_dongles(t_coder *coder, t_dongle *dongle1,
				t_dongle *dongle2);
static void	check_prio(t_coder *coder, t_dongle *dongle1, t_dongle *dongle2);
static int	is_cooldown_ok(t_coder *coder, t_dongle *d1, t_dongle *d2);

int	do_compile_edf(t_coder *coder, t_dongle *dongle1, t_dongle *dongle2)
{
	if (wait_for_dongles(coder, dongle1, dongle2) == 0)
		return (0);
	pthread_mutex_lock(&coder->data_lock);
	coder->last_compile_start = get_time();
	pthread_mutex_unlock(&coder->data_lock);
	print_action(coder, COMPILING);
	custom_sleep(coder->data->rules.time_to_compile, coder->data);
	coder->nbr_of_compilations++;
	return (1);
}

void	put_heap(t_coder *coder, t_dongle *dongle)
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

static int	wait_for_dongles(t_coder *coder, t_dongle *dongle1,
		t_dongle *dongle2)
{
	while (is_simu(coder->data))
	{
		pthread_mutex_lock(&dongle1->lock);
		pthread_mutex_lock(&dongle2->lock);
		if (dongle1->heap.nodes[0].coder_id == coder->id
			&& dongle2->heap.nodes[0].coder_id == coder->id)
		{
			if (is_cooldown_ok(coder, dongle1, dongle2))
				break ;
			pthread_mutex_unlock(&dongle1->lock);
			pthread_mutex_unlock(&dongle2->lock);
			custom_sleep(1, coder->data);
			continue ;
		}
		check_prio(coder, dongle1, dongle2);
	}
	if (is_simu(coder->data) == 0)
		return (0);
	heap_extract_min(&dongle1->heap);
	heap_extract_min(&dongle2->heap);
	print_action(coder, TAKE_DONGLE);
	print_action(coder, TAKE_DONGLE);
	return (1);
}

static int	is_cooldown_ok(t_coder *coder, t_dongle *d1, t_dongle *d2)
{
	long long	now;
	long long	cooldown;

	now = get_time();
	cooldown = coder->data->rules.dongle_cooldown;
	if (now >= d1->last_release + cooldown
		&& now >= d2->last_release + cooldown)
		return (1);
	return (0);
}

static void	check_prio(t_coder *coder, t_dongle *dongle1, t_dongle *dongle2)
{
	if (dongle1->heap.nodes[0].coder_id != coder->id)
	{
		pthread_mutex_unlock(&dongle2->lock);
		pthread_cond_wait(&dongle1->cond, &dongle1->lock);
		pthread_mutex_unlock(&dongle1->lock);
	}
	else if (dongle1->heap.nodes[0].coder_id == coder->id
		&& dongle2->heap.nodes[0].coder_id != coder->id)
	{
		pthread_mutex_unlock(&dongle1->lock);
		pthread_cond_wait(&dongle2->cond, &dongle2->lock);
		pthread_mutex_unlock(&dongle2->lock);
	}
}
