/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:07:27 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/19 10:50:34 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	get_tickets(t_dongle *first, t_dongle *second,
				unsigned int *tickets);
static void	do_compile(t_coder *coder, t_dongle *first, t_dongle *second);
static void	wait_for_dongle(t_coder *coder, t_dongle *dongle1, t_dongle *dongle2,
				unsigned int *tickets);

void	fifo_compiling(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	set_order(coder, &first, &second);
	do_compile(coder, first, second);
	pthread_mutex_lock(&coder->data_lock);
	coder->last_compile = get_time();
	pthread_mutex_unlock(&coder->data_lock);
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

static void	get_tickets(t_dongle *first, t_dongle *second, unsigned int *tickets)
{
	pthread_mutex_lock(&first->lock);
	tickets[0] = first->ticket_counter;
	first->ticket_counter += 1;
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_lock(&second->lock);
	tickets[1] = second->ticket_counter;
	second->ticket_counter += 1;
	pthread_mutex_unlock(&second->lock);
}

static void	do_compile(t_coder *coder, t_dongle *first, t_dongle *second)
{
	unsigned int	tickets[2];

	get_tickets(first, second, tickets);
	wait_for_dongle(coder, first, second, tickets);
	print_action(coder, COMPILING);
	custom_sleep(coder->data->rules.time_to_compile, coder->data);
	coder->nbr_of_compilations++;
}

static void	wait_for_dongle(t_coder *coder, t_dongle *dongle1,
		t_dongle *dongle2, unsigned int *tickets)
{
	long long	wait_time;
	long long	d1_cooldown;
	long long	d2_cooldown;

	pthread_mutex_lock(&dongle1->lock);
	while (tickets[0] != dongle1->serving_ticket && is_simu(coder->data) == 1)
		pthread_cond_wait(&dongle1->cond, &dongle1->lock);
	d1_cooldown = (dongle1->last_release);
	pthread_mutex_unlock(&dongle1->lock);
	pthread_mutex_lock(&dongle2->lock);
	while (tickets[1] != dongle2->serving_ticket && is_simu(coder->data) == 1)
		pthread_cond_wait(&dongle2->cond, &dongle2->lock);
	d2_cooldown = (dongle2->last_release);
	pthread_mutex_unlock(&dongle2->lock);
	if (d1_cooldown > d2_cooldown)
		wait_time = d1_cooldown + coder->data->rules.dongle_cooldown - get_time();
	else
		wait_time = d2_cooldown + coder->data->rules.dongle_cooldown - get_time();
	if (wait_time > 0)
		custom_sleep(wait_time, coder->data);
	print_action(coder, TAKE_DONGLE);
	print_action(coder, TAKE_DONGLE);
}
