/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:37:15 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/16 16:37:46 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_action(t_coder *coder, char *action)
{
	pthread_mutex_lock(&coder->data->print_lock);
	if (is_simu(coder->data) == 1 || strcmp(action, BURNOUT) == 0)
		printf(action, (get_time() - coder->data->start_time), coder->id);
	pthread_mutex_unlock(&coder->data->print_lock);
}
