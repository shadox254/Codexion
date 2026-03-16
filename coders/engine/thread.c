/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:21:49 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/16 10:57:05 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	*coder_start(void *arg);
static void	join_thread(t_data *data);

void	init_thread(t_data *data)
{
	unsigned int	count;
	
	count = 0;
	pthread_create(&data->monitor, NULL, monitoring, &data);
	while (count < data->rules.number_of_coders)
	{
		pthread_create(&data->coders[count].thread_id, NULL, coder_start, &data->coders[count]);
		count++;
	}
	join_thread(data);
}

static void	*coder_start(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->data->is_fifo == 1)
		fifo(coder);
	else
		return (NULL);
	return (NULL);
}

static void	join_thread(t_data *data)
{
	unsigned int	count;
	
	count = 0;
	// pthread_create(&data->monitor, NULL, monitoring, &data->coders[count]);
	while (count < data->rules.number_of_coders)
	{
		pthread_join(data->coders[count].thread_id, NULL);
		count++;
	}
}