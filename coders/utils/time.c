/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:15:00 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/16 16:50:43 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	custom_sleep(long long time_in_ms, t_data *data)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
	{
		if (is_simu(data) == 0)
			break ;
		usleep(500);
	}
}
