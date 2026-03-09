/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:16:28 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/09 12:15:14 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	codexion(char **av)
{
	t_data	data;

	if (create_data(&data, av) == 0)
		return;
	print_data(data);
	free_data(&data);
}
