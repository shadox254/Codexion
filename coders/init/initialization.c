/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 09:47:15 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/20 09:36:29 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	assign_dongles(t_data *data, unsigned int i);
static int	init_dongle(t_dongle *dongle, t_data *data);
static void	init_coder(t_data *data, t_coder *coder, int count);

int	init_all(t_data *data)
{
	unsigned int	count;

	count = 0;
	data->coders = malloc(sizeof(t_coder) * data->rules.number_of_coders);
	if (!data->coders)
	{
		print_error(C_MALLOC_ERROR);
		return (0);
	}
	while (count < data->rules.number_of_coders)
	{
		init_coder(data, &data->coders[count], count);
		pthread_mutex_init(&data->coders[count].data_lock, NULL);
		if (init_dongle(&data->dongles[count], data) == 0)
			return (0);
		assign_dongles(data, count);
		count++;
	}
	return (1);
}

static void	init_coder(t_data *data, t_coder *coder, int count)
{
	coder->id = count + 1;
	coder->data = data;
	coder->nbr_of_compilations = 0;
	coder->finished = 0;
	coder->last_compile = data->start_time;
	coder->last_compile_start = data->start_time;
	(void) coder;
}

static int	init_dongle(t_dongle *dongle, t_data *data)
{
	dongle->data = data;
	dongle->serving_ticket = 0;
	dongle->ticket_counter = 0;
	dongle->last_release = 0;
	dongle->heap.nodes = malloc(sizeof(t_node)
			* dongle->data->rules.number_of_coders);
	if (!dongle->heap.nodes)
	{
		print_error(N_MALLOC_ERROR);
		return (0);
	}
	dongle->heap.size = 0;
	return (1);
}

static void	assign_dongles(t_data *data, unsigned int i)
{
	data->coders[i].left_dongle = &data->dongles[i];
	data->coders[i].right_dongle = &data->dongles[(i + 1)
		% data->rules.number_of_coders];
}
