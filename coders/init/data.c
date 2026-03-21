/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 09:44:24 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/21 11:11:16 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_data(t_data *data, char **av)
{
	if (args_verif(av) == 0)
		return (0);
	if (fill_rules(&data->rules, av) == 0)
		return (0);
	if (av[8][0] == 'f' || av[8][0] == 'F')
		data->is_fifo = 1;
	else
		data->is_fifo = 0;
	data->start_time = get_time();
	data->is_simu = 1;
	data->dongles = malloc(sizeof(t_dongle) * data->rules.number_of_coders);
	if (!data->dongles)
	{
		print_error(D_MALLOC_ERROR);
		free_data(data);
		return (0);
	}
	if (init_all(data) == 0)
		return (0);
	return (1);
}
