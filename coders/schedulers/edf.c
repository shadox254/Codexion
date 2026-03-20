/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:07:36 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/20 16:07:27 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	edf(t_coder *coder)
{
	while (is_simu(coder->data) == 1 && have_finish(coder) == 0)
	{
		edf_compiling(coder);
		debugging_and_refactoring(coder);
	}
}

void	edf_compiling(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	set_order(coder, &first, &second);
	put_heap(coder, first);
	put_heap(coder, second);
	if (do_compile_edf(coder, first, second) == 0)
		return ;
	pthread_mutex_lock(&coder->data_lock);
	coder->last_compile = get_time();
	pthread_mutex_unlock(&coder->data_lock);
	first->last_release = get_time();
	pthread_cond_broadcast(&first->cond);
	pthread_mutex_unlock(&first->lock);
	second->last_release = get_time();
	pthread_cond_broadcast(&second->cond);
	pthread_mutex_unlock(&second->lock);
}
