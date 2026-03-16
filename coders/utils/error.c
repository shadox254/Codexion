/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:17:26 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/16 16:50:51 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_error(char *str)
{
	fprintf(stderr, "%s\n", str);
}

void	free_data(t_data *data)
{
	if (data->dongles)
		free(data->dongles);
	if (data->coders)
		free(data->coders);
}
