/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:53:03 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/16 16:49:55 by rruiz            ###   ########.fr       */
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
