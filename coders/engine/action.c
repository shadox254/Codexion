/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:37:15 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/13 14:12:49 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_action(t_coder *coder, char *action)
{
	pthread_mutex_lock(&coder->data->print_lock);
	if (coder->data->dead == 0)
		printf(action, (get_time() - coder->data->start_time) / 1000, coder->id);
	pthread_mutex_unlock(&coder->data->print_lock);
}