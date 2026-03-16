/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:16:26 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/16 16:57:06 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	fill_rules(t_rules *rules, char **av)
{
	rules->number_of_coders = atoi(av[1]);
	rules->time_to_burnout = atoi(av[2]);
	rules->time_to_compile = atoi(av[3]);
	rules->time_to_debug = atoi(av[4]);
	rules->time_to_refactor = atoi(av[5]);
	rules->number_of_compiles_required = atoi(av[6]);
	rules->dongle_cooldown = atoi(av[7]);
	rules->scheduler = av[8];
}
