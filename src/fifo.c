/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:07:27 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/09 17:53:25 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static void	set_order(t_coder *coder, t_dongle *first, t_dongle *second);

void	fifo(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	set_order(coder, &first, &second);
	while (coder->nbr_of_compilations < coder->data->rules.number_of_compiles_required && coder->data->dead == 0)
	{
		pthread_mutex_lock(coder->left_dongle);
		pthread_mutex_lock(coder->right_dongle);
	}
}

static void	set_order(t_coder *coder, t_dongle *first, t_dongle *second)
{
	if (coder->left_dongle < coder->right_dongle)
	{
		first = coder->left_dongle;
		second = coder->right_dongle;
	}
	else
	{
		first = coder->right_dongle;
		second = coder->left_dongle;
	}
}
