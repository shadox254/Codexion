/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:15:00 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/21 10:51:06 by rruiz            ###   ########.fr       */
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

void	sleep_for_cooldown(t_coder *coder, t_dongle *d1, t_dongle *d2)
{
	long long	wait_time;
	long long	d1_rel;
	long long	d2_rel;

	d1_rel = d1->last_release;
	d2_rel = d2->last_release;
	pthread_mutex_unlock(&d1->lock);
	pthread_mutex_unlock(&d2->lock);
	if (d1_rel > d2_rel)
		wait_time = d1_rel + coder->data->rules.dongle_cooldown - get_time();
	else
		wait_time = d2_rel + coder->data->rules.dongle_cooldown - get_time();
	if (wait_time > 0)
		custom_sleep(wait_time, coder->data);
}
