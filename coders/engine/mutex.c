/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:34:05 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/16 08:58:06 by rruiz            ###   ########.fr       */
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
		count++;
	}
}