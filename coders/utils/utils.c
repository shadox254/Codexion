/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:53:03 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/19 10:35:55 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	have_finish(t_coder *coder)
{
	unsigned int	nbr_of_comp;

	pthread_mutex_lock(&coder->data_lock);
	nbr_of_comp = coder->nbr_of_compilations;
	if (nbr_of_comp == coder->data->rules.number_of_compiles_required)
	{
		coder->finished = 1;
		pthread_mutex_unlock(&coder->data_lock);
		return (1);
	}
	pthread_mutex_unlock(&coder->data_lock);
	return (0);
}

void	set_order(t_coder *coder, t_dongle **first, t_dongle **second)
{
	if (coder->left_dongle < coder->right_dongle)
	{
		*first = coder->left_dongle;
		*second = coder->right_dongle;
	}
	else
	{
		*first = coder->right_dongle;
		*second = coder->left_dongle;
	}
}

t_node	*create_node(t_node *node, int coder_id, long long deadline)
{
	node->coder_id = coder_id;
	node->deadline = deadline;
	return (node);
}