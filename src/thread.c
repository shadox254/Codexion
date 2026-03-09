/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:21:49 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/09 16:07:36 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	init_thread(t_data *data)
{
	unsigned int	count;
	
	count = 0;
	while (count)
	{
		pthread_create(&data->coders[count].id, NULL, coder_start, NULL);
		count++;
	}
}

static void	coder_start(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->data->is_fifo == 1)
		fifo(coder);
	else
		return;
}