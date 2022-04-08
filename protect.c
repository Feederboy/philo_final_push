/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 00:52:04 by maquentr          #+#    #+#             */
/*   Updated: 2022/04/09 00:52:55 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->mutex_death);
	if (data->phi_end == 1)
		res = 1;
	pthread_mutex_unlock(&data->mutex_death);
	return (res);
}

int	protect_write(char *str, t_phi *phi, int id)
{
	if (!check_death(phi->data))
	{
		pthread_mutex_lock(&phi->data->mutex_write);
		printf(str, get_time(phi->data->start), id);
		pthread_mutex_unlock(&phi->data->mutex_write);
		return (1);
	}
	return (0);
}
