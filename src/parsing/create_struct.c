/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:02:57 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/09 12:29:55 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	create_coders(t_data *data);

int create_data(t_data *data, char **av)
{
	if (args_verif(av) == 0)
		return (0);
	fill_rules(&data->rules, av);
	create_coders(data);
	return (1);
}

static void	create_coders(t_data *data)
{
	unsigned int count;

	count = 0;
	data->coders = malloc(sizeof(t_coder) * data->rules.number_of_coders);
	if (!data->coders)
	{
		print_error(MALLOC_ERROR);
		return;
	}
	while (count < data->rules.number_of_coders)
	{
		data->coders[count].data = data;
		data->coders[count].id = count + 1;
		data->coders[count].nbr_of_compilations = 0;
		data->coders[count].finished = 0;
		data->coders[count].left_dongle = NULL;
		data->coders[count].right_dongle = NULL;
		count++;
	}
}
