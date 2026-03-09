/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:02:57 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/09 11:20:54 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void test(t_coder *coder, unsigned int count);

static void	create_coders(t_data *data);

int create_data(t_data *data, char **av)
{
	if (args_verif(av) == 0)
		return (1);
	fill_rules(&data->rules, av);
	create_coders(data);
	return (0);
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
		test(&data->coders[count], count);
		count++;
	}
}

void test(t_coder *coder, unsigned int count)
{
	coder->id = count + 1;
	coder->nbr_of_compilations = 0;
	coder->finished = 0;
	coder->left_dongle = NULL;
	coder->right_dongle = NULL;
}