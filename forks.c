/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 00:48:40 by maquentr          #+#    #+#             */
/*   Updated: 2022/04/09 00:49:13 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_forks(t_phi *phi)
{
	if (phi->id % 2 != 0)
	{
		pthread_mutex_lock(&phi->data->mutex_forks[phi->right]);
		protect_write("%d : Philosopher %d has taken a fork\n", phi, phi->id);
		pthread_mutex_lock(&phi->data->mutex_forks[phi->left]);
		protect_write("%d : Philosopher %d has taken a fork\n", phi, phi->id);
	}
	else
	{
		pthread_mutex_lock(&phi->data->mutex_forks[phi->left]);
		protect_write("%d : Philosopher %d has taken a fork\n", phi, phi->id);
		pthread_mutex_lock(&phi->data->mutex_forks[phi->right]);
		protect_write("%d : Philosopher %d has taken a fork\n", phi, phi->id);
	}
}

void	put_forks_back(t_phi *phi)
{
	if (phi->id % 2 == 0)
	{
		pthread_mutex_unlock(&phi->data->mutex_forks[phi->right]);
		pthread_mutex_unlock(&phi->data->mutex_forks[phi->left]);
	}
	else
	{
		pthread_mutex_unlock(&phi->data->mutex_forks[phi->left]);
		pthread_mutex_unlock(&phi->data->mutex_forks[phi->right]);
	}
}
