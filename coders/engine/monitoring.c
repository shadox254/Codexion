/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 09:04:37 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/16 16:52:46 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int			burnout_arrived(t_data *data);
static unsigned int	is_finished(t_data *data);
static void			end_all(t_data *data);

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *) arg;
	while (is_simu(data) == 1)
	{
		if (burnout_arrived(data) == 1)
		{
			end_all(data);
			return (NULL);
		}
		if (is_finished(data) == data->rules.number_of_coders)
		{
			end_all(data);
			return (NULL);
		}
	}
	return (NULL);
}

static int	burnout_arrived(t_data *data)
{
	unsigned int	count;
	long long		last_comp;

	count = 0;
	while (count < data->rules.number_of_coders)
	{
		pthread_mutex_lock(&data->coders[count].data_lock);
		last_comp = data->coders[count].last_compile;
		if (get_time() - last_comp > data->rules.time_to_burnout)
		{
			print_action(&data->coders[count], BURNOUT);
			pthread_mutex_unlock(&data->coders[count].data_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->coders[count].data_lock);
		count++;
	}
	return (0);
}

static unsigned int	is_finished(t_data *data)
{
	unsigned int	count;
	unsigned int	finish;

	count = 0;
	finish = 0;
	while (count < data->rules.number_of_coders)
	{
		pthread_mutex_lock(&data->coders[count].data_lock);
		if (data->coders[count].finished == 1)
			finish++;
		pthread_mutex_unlock(&data->coders[count].data_lock);
		count++;
	}
	return (finish);
}

int	is_simu(t_data *data)
{
	int	simu;

	pthread_mutex_lock(&data->lock);
	simu = data->is_simu;
	pthread_mutex_unlock(&data->lock);
	return (simu);
}

static void	end_all(t_data *data)
{
	unsigned int	count;

	count = 0;
	pthread_mutex_lock(&data->lock);
	data->is_simu = 0;
	pthread_mutex_unlock(&data->lock);
	while (count < data->rules.number_of_coders)
	{
		pthread_mutex_lock(&data->dongles[count].lock);
		pthread_cond_broadcast(&data->dongles[count].cond);
		pthread_mutex_unlock(&data->dongles[count].lock);
		count++;
	}
}
