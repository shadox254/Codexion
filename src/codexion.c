/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:16:28 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/11 15:11:54 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	codexion(char **av)
{
	t_data	data;

	if (create_data(&data, av) == 0)
		return;
	init_mutex(&data);
	print_all(data);
	free_data(&data);
}
