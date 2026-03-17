/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:03:01 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/17 11:55:37 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	fifo(t_coder *coder)
{
	while (is_simu(coder->data) == 1 && have_finish(coder) == 0)
	{
		compiling(coder);
		debugging_and_refactoring(coder);
	}
}

void	debugging_and_refactoring(t_coder *coder)
{
	print_action(coder, DEBUGGING);
	custom_sleep(coder->data->rules.time_to_debug, coder->data);
	print_action(coder, REFACTORING);
	custom_sleep(coder->data->rules.time_to_refactor, coder->data);
}
