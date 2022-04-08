/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 00:56:16 by maquentr          #+#    #+#             */
/*   Updated: 2022/04/09 00:58:48 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_phi *phi)
{
	get_forks(phi);
	pthread_mutex_lock(&phi->data->mutex_death);
	phi->last_diner = get_time(phi->data->start);
	phi->diner += 1;
	pthread_mutex_unlock(&phi->data->mutex_death);
	protect_write("%d : philosopher %d is eating\n", phi, phi->id);
	if (!check_death(phi->data))
		ms_sleep(phi->data->time_to_eat);
	put_forks_back(phi);
}

void	ft_sleep(t_phi *phi)
{
	protect_write("%d : philosopher %d is sleeping\n", phi, phi->id);
	if (!check_death(phi->data))
		ms_sleep(phi->data->time_to_sleep);
}

void	ft_think(t_phi *phi)
{
	protect_write("%d : philosopher %d is thinking\n", phi, phi->id);
	if (phi->data->time_to_eat > phi->data->time_to_sleep)
		ms_sleep((phi->data->time_to_eat - phi->data->time_to_sleep) + 1);
}

void	*routine(void *phi)
{
	t_phi	*tmp;
	t_data	*data;

	tmp = (t_phi *) phi;
	data = tmp->data;
	while (1)
	{
		pthread_mutex_lock(&data->mutex_death);
		if ((data->phi_end == 1) || (tmp->diner == data->diner_goal))
		{
			data->nb_phi--;
			tmp->is_alive = false;
			pthread_mutex_unlock(&data->mutex_death);
			return (NULL);
		}
		pthread_mutex_unlock(&data->mutex_death);
		ft_eat(tmp);
		ft_sleep(tmp);
		ft_think(tmp);
	}
}
