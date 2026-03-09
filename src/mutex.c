/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:54:33 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/09 15:17:55 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static void	init_dongles(t_data *data);

void init_mutex(t_data *data)
{
	pthread_mutex_init(&data->print_lock, NULL);
	init_dongles(data);
}

static void	init_dongles(t_data *data)
{
	unsigned int	count;

	count = 0;
	data->dongles = malloc(sizeof(t_dongle) * data->rules.number_of_coders);
	while (count < data->rules.number_of_coders)
	{
		pthread_mutex_init(&data->dongles[count].lock, NULL);
		count++;
	}
}
