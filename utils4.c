/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:25:48 by maquentr          #+#    #+#             */
/*   Updated: 2022/04/06 16:27:56 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*
int		is_ok(t_phi *philo, t_data *data)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->current_time
			- philo->last_diner >= data->time_to_eat && philo->diner)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex);
	return (0);
}
*/