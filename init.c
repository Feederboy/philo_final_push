/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:33:42 by maquentr          #+#    #+#             */
/*   Updated: 2022/04/09 00:50:04 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_phi	*new_phi(int id)
{
	t_phi	*res;

	res = malloc(sizeof(t_phi));
	if (!res)
		return (NULL);
	res->id = id;
	res->diner = 0;
	res->last_diner = 0;
	res->thread = 0;
	res->prev = NULL;
	res->next = NULL;
	res->is_alive = true;
	return (res);
}

void	init_phi(t_data *data)
{
	int		i;
	t_phi	*new;

	i = 1;
	data->philist = NULL;
	while (i <= data->nb_phi)
	{
		new = new_phi(i);
		if (!new)
			return ;
		new->data = data;
		new->right = i - 1;
		if (i == data->nb_phi)
			new->left = 0;
		else
			new->left = i;
		new->last_diner = 0;
		add_end(&data->philist, new);
		i++;
	}
	return ;
}

int	check_args(t_data *data, char **av)
{
	data->nb_phi = ft_atoi(av[1]);
	if ((nblen(data->nb_phi) != ft_strlen(av[1])) || !data->nb_phi)
		return (0);
	data->time_to_die = ft_atoi(av[2]);
	if (nblen(data->time_to_die) != ft_strlen(av[2]))
		return (0);
	data->time_to_eat = ft_atoi(av[3]);
	if (nblen(data->time_to_eat) != ft_strlen(av[3]))
		return (0);
	data->time_to_sleep = ft_atoi(av[4]);
	if (nblen(data->time_to_sleep) != ft_strlen(av[4]))
		return (0);
	if (av[5])
	{
		data->diner_goal = ft_atoi(av[5]);
		if (data->diner_goal < 0)
			return (0);
		if (nblen(data->diner_goal) != ft_strlen(av[5]))
			return (0);
	}
	else
		data->diner_goal = -1;
	return (1);
}

int	init_data(t_data *data, char **av)
{
	int	i;

	i = 0;
	if (!check_args(data, av))
		return (0);
	data->mutex_forks = malloc(sizeof(pthread_mutex_t) * (data->nb_phi));
	if (!data->mutex_forks)
		return (0);
	while (i < data->nb_phi)
		pthread_mutex_init(&data->mutex_forks[i++], NULL);
	gettimeofday(&data->start, NULL);
	pthread_mutex_init(&data->mutex_death, NULL);
	pthread_mutex_init(&data->mutex_write, NULL);
	data->phi_end = 0;
	return (1);
}
