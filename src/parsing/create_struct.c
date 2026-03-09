/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:02:57 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/09 16:01:30 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static int	create_coders(t_data *data);

int create_data(t_data *data, char **av)
{
	if (args_verif(av) == 0)
		return (0);
	fill_rules(&data->rules, av);
	if ((strcmp(data->rules.scheduler, "fifo") == 0 || (strcmp(data->rules.scheduler, "FIFO") == 0)))
		data->is_fifo = 1;
	else
		data->is_fifo = 0;
	return (create_coders(data));
}

static int	create_coders(t_data *data)
{
	unsigned int count;

	count = 0;
	data->coders = malloc(sizeof(t_coder) * data->rules.number_of_coders);
	if (!data->coders)
	{
		print_error(MALLOC_ERROR);
		return (0);
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
	return (1);
}
