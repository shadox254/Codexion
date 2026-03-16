/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:16:28 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/16 09:06:34 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	codexion(char **av)
{
	t_data	data;

	if (init_data(&data, av) == 0)
		return;
	init_mutex(&data);
	init_thread(&data);
	// print_all(data);
	free_data(&data);
}
