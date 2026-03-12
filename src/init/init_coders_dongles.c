/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 09:47:15 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/12 16:12:35 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	assign_dongles(t_data *data, unsigned int i);

int	init_coders_dongles(t_data *data)
{	
	unsigned int	i;

	i = 0;
	data->coders = malloc(sizeof(t_coder) * data->rules.number_of_coders);
	if (!data->coders)
	{
		print_error(C_MALLOC_ERROR);
		return (0);
	}
	while (i < data->rules.number_of_coders)
	{
		data->coders[i].id = i + 1;
		data->coders[i].data = data;
		data->coders[i].nbr_of_compilations = 0;
		data->coders[i].finished = 0;
		data->coders[i].last_compile = get_time();
		pthread_mutex_init(&data->coders[i].data_lock, NULL);
		pthread_mutex_init(&data->dongles[i].lock, NULL);
		data->dongles[i].serving_ticket = 0;
		data->dongles[i].ticket_counter = 0;
		assign_dongles(data, i);
		i++;
	}
	return (1);
}

static void	assign_dongles(t_data *data, unsigned int i)
{
	data->coders[i].left_dongle = &data->dongles[i];
	data->coders[i].right_dongle = &data->dongles[(i + 1) % data->rules.number_of_coders];
}
