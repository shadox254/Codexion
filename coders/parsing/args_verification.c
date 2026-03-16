/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_verification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:16:31 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/13 14:08:11 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_digit(int c);
static int	is_int(char *n);


int	args_verif(char **av)
{
	int	i;

	i = 1;
	while (i < 8)
	{
		if (is_int(av[i]) == 0)
		{
			print_error(ARGS_ERROR);
			return (0);
		}
		if (atoi(av[i]) < 0)
		{
			print_error(ARGS_ERROR);
			return (0);
		}
		i++;
	}
	if ((strcmp(av[8], "fifo") && strcmp(av[8], "edf"))
	&& (strcmp(av[8], "FIFO") && strcmp(av[8], "EDF")))
	{
		print_error(LAST_ARGS_ERROR);
		return (0);
	}
	return (1);
}

static int	is_digit(int c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

static int	is_int(char *n)
{
	int			i;
	long long	nb;

	i = 0;
	nb = 0;
	if (n[i] == '+')
		i++;
	while (n[i])
	{
		if (is_digit(n[i]) == 0)
			return (0);
		nb = (nb *10) + n[i] - '0';
		i++;
	}
	if (nb > INT_MAX)
		return (0);
	return (1);
}

