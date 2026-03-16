/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:07:27 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/16 17:33:33 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	set_order(t_coder *coder, t_dongle **first, t_dongle **second);
static void	get_tickets(t_coder *coder, t_dongle *first, t_dongle *second,
				unsigned int *tickets);
static void	do_compile(t_coder *coder, t_dongle *first, t_dongle *second);
static void	wait_for_dongle(t_coder *coder, t_dongle *dongle,
				unsigned int ticket);

void	compiling(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	set_order(coder, &first, &second);
	do_compile(coder, first, second);
	pthread_mutex_lock(&first->lock);
	first->last_release = get_time();
	first->serving_ticket++;
	pthread_cond_broadcast(&first->cond);
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_lock(&second->lock);
	second->last_release = get_time();
	second->serving_ticket++;
	pthread_cond_broadcast(&second->cond);
	pthread_mutex_unlock(&second->lock);
}

static void	set_order(t_coder *coder, t_dongle **first, t_dongle **second)
{
	if (coder->left_dongle < coder->right_dongle)
	{
		*first = coder->left_dongle;
		*second = coder->right_dongle;
	}
	else
	{
		*first = coder->right_dongle;
		*second = coder->left_dongle;
	}
}

static void	get_tickets(t_coder *coder, t_dongle *first, t_dongle *second,
	unsigned int *tickets)
{
	pthread_mutex_lock(&coder->data->lock);
	pthread_mutex_lock(&first->lock);
	tickets[0] = first->ticket_counter;
	first->ticket_counter += 1;
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_lock(&second->lock);
	tickets[1] = second->ticket_counter;
	second->ticket_counter += 1;
	pthread_mutex_unlock(&second->lock);
	pthread_mutex_unlock(&coder->data->lock);
}

static void	do_compile(t_coder *coder, t_dongle *first, t_dongle *second)
{
	unsigned int	tickets[2];

	get_tickets(coder, first, second, tickets);
	wait_for_dongle(coder, first, tickets[0]);
	wait_for_dongle(coder, second, tickets[1]);
	print_action(coder, COMPILING);
	custom_sleep(coder->data->rules.time_to_compile, coder->data);
	coder->nbr_of_compilations++;
}

static void	wait_for_dongle(t_coder *coder, t_dongle *dongle,
		unsigned int ticket)
{
	long long	wait_time;

	pthread_mutex_lock(&dongle->lock);
	while (ticket != dongle->serving_ticket && is_simu(coder->data) == 1)
		pthread_cond_wait(&dongle->cond, &dongle->lock);
	wait_time = (dongle->last_release + coder->data->rules.dongle_cooldown)
		- get_time();
	pthread_mutex_unlock(&dongle->lock);
	if (wait_time > 0)
		custom_sleep(wait_time, coder->data);
	print_action(coder, TAKE_DONGLE);
}
