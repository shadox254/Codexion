/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:07:27 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/12 16:13:27 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static void	set_order(t_coder *coder, t_dongle **first, t_dongle **second);
static void	get_tickets(t_dongle *first, t_dongle *second, unsigned int *f_ticket, unsigned int *s_ticket);
static void	do_compile(t_coder *coder, t_dongle *first, t_dongle *second);

void	compile(t_coder *coder)
{
	compiling(coder);
	pthread_mutex_lock(&coder->data_lock);
	coder->last_compile = get_time();
	coder->nbr_of_compilations += 1;
	pthread_mutex_unlock(&coder->data_lock);
	debugging_and_refactoring(coder);
}

void	compiling(t_coder *coder)
{
	t_dongle		*first;
	t_dongle		*second;

	set_order(coder, &first, &second);
	do_compile(coder, first, second);
	first->serving_ticket++;
	pthread_cond_broadcast(&first->cond);
	pthread_mutex_unlock(&first->lock);
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

static void	get_tickets(t_dongle *first, t_dongle *second, unsigned int *f_ticket, unsigned int *s_ticket)
{
	pthread_mutex_lock(&first->lock);
	*f_ticket = first->ticket_counter;
	first->ticket_counter += 1;
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_lock(&second->lock);
	*s_ticket = second->ticket_counter;
	second->ticket_counter += 1;
	pthread_mutex_unlock(&second->lock);
}

static void	do_compile(t_coder *coder, t_dongle *first, t_dongle *second)
{
	unsigned int	first_ticket;
	unsigned int	second_ticket;

	get_tickets(first, second, &first_ticket, &second_ticket);
	pthread_mutex_lock(&first->lock);
	while (first_ticket != first->serving_ticket)
		pthread_cond_wait(&first->cond, &first->lock);
	print_action(coder, TAKE_DONGLE);
	pthread_mutex_lock(&second->lock);
	while (second_ticket != second->serving_ticket)
		pthread_cond_wait(&second->cond, &second->lock);
	print_action(coder, TAKE_DONGLE);
	print_action(coder, COMPILING);
	usleep(coder->data->rules.time_to_compile * 1000);
}

void	debugging_and_refactoring(t_coder *coder)
{
	print_action(coder, DEBUGGING);
	usleep(coder->data->rules.time_to_debug * 1000);
	print_action(coder, REFACTORING);
	usleep(coder->data->rules.time_to_refactor * 1000);
}