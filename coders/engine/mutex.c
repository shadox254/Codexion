/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:34:05 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/17 17:34:11 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	init_mutex(t_data *data)
{
	unsigned int	count;

	count = 0;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->lock, NULL);
	while (count < data->rules.number_of_coders)
	{
		pthread_mutex_init(&data->dongles[count].lock, NULL);
		pthread_cond_init(&data->dongles[count].cond, NULL);
		count++;
	}
}

void	destroy_mutex(t_data *data)
{
	unsigned int	count;

	count = 0;
	while (count < data->rules.number_of_coders)
	{
		pthread_mutex_destroy(&data->coders[count].data_lock);
		pthread_mutex_destroy(&data->dongles[count].lock);
		pthread_cond_destroy(&data->dongles[count].cond);
		if (data->dongles[count].heap.nodes)
			free(data->dongles[count].heap.nodes);
		count++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->lock);
}
