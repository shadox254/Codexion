/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:17:40 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/20 08:30:59 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_all(t_data data)
{
	printf("=============== DATA ===============\n");
	print_data(data);
	printf("\n=============== RULES ===============\n");
	print_rules(data.rules);
	printf("\n=============== CODERS ===============\n");
	print_coders(data);
	printf("\n=============== DONGLES ===============\n");
	print_dongles(data);
}

void	print_data(t_data data)
{
	printf("is fifo: %i\n", data.is_fifo);
	printf("start time: %lli\n", data.start_time);
	printf("is simulation: %i\n", data.is_simu);
}

void	print_rules(t_rules rules)
{
	printf("number of coders:%i\n", rules.number_of_coders);
	printf("time to burnout: %i\n", rules.time_to_burnout);
	printf("time to compile: %i\n", rules.time_to_compile);
	printf("time to debug: %i\n", rules.time_to_debug);
	printf("time to refractor: %i\n", rules.time_to_refactor);
	printf("numbers of compilation required: %i\n",
		rules.number_of_compiles_required);
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
		printf("nbr_of_compilations: %i\n",
			data.coders[count].nbr_of_compilations);
		printf("finished: %i\n", data.coders[count].finished);
		printf("last compilation: %lli\n", data.coders[count].last_compile);
		count++;
	}
}

void	print_dongles(t_data data)
{
	unsigned int	count;

	count = 0;
	while (count < data.rules.number_of_coders)
	{
		printf("\n======= DONGLES %u =======\n", count + 1);
		printf("last release: %lli\n", data.dongles[count].last_release);
		printf("ticket counter: %d\n", data.dongles[count].ticket_counter);
		printf("serving ticket: %d\n", data.dongles[count].serving_ticket);
		count++;
	}
}
