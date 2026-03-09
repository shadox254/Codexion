/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:17:40 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/09 12:29:55 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	print_data(t_data data)
{
	printf("=============== RULES ===============\n");
	print_rules(data.rules);
	printf("\n=============== CODERS ===============\n");
	print_coders(data);
}

void	print_rules(t_rules rules)
{
	printf("number of coders:%i\n", rules.number_of_coders);
	printf("time to burnout: %i\n", rules.time_to_burnout);
	printf("time to compile: %i\n", rules.time_to_compile);
	printf("time to debug: %i\n", rules.time_to_debug);
	printf("time to refractor: %i\n", rules.time_to_refactor);
	printf("numbers of compilation required: %i\n", rules.number_of_compiles_required);
	printf("dongle cooldown: %i\n", rules.dongle_cooldown);
	printf("schelduler: %s\n", rules.scheduler);
}

void	print_coders(t_data data)
{
	unsigned int	count;

	count = 0;
	while (count < data.rules.number_of_coders)
	{
		printf("\n======= CODERS %u =======\n", count + 1);
		printf("id: %i\n", data.coders[count].id);
		printf("nbr_of_compilations: %i\n", data.coders[count].nbr_of_compilations);
		printf("finished: %i\n", data.coders[count].finished);
		printf("left_dongle: %p\n", data.coders[count].left_dongle);
		printf("right_dongle: %p\n", data.coders[count].right_dongle);
		count++;
	}
}