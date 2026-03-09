/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:17:26 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/09 12:29:55 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	print_error(char *str)
{
	fprintf(stderr, "%s\n", str);
}

void	free_data(t_data *data)
{
	unsigned int	count;

	count = 0;
	while (count < data->rules.number_of_coders)
	{
		if (data->coders[count].left_dongle != NULL)
			free(data->coders[count].left_dongle);
		if (data->coders[count].right_dongle != NULL)
			free(data->coders[count].right_dongle);
		count++;
	}
	if (data->coders)
		free(data->coders);
}