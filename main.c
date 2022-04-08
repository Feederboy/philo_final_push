/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:35:01 by maquentr          #+#    #+#             */
/*   Updated: 2022/04/09 01:03:03 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	checker_diner(t_phi *phi)
{
	t_phi	*tmp;
	int		i;

	tmp = phi;
	i = 0;
	if (tmp->data->diner_goal < 0)
		return (0);
	while (i < tmp->data->diner_goal)
	{
		pthread_mutex_lock(&tmp->data->mutex_death);
		if (tmp->diner < tmp->data->diner_goal)
		{
			pthread_mutex_unlock(&tmp->data->mutex_death);
			return (0);
		}
		pthread_mutex_unlock(&tmp->data->mutex_death);
		tmp = tmp->next;
		i++;
	}
	return (1);
}

void	monitoring(t_phi *phi, t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->mutex_death);
		if (phi->is_alive == true)
		{
			if (get_time(data->start) - phi->last_diner > data->time_to_die)
			{
				pthread_mutex_lock(&data->mutex_write);
				printf("%d : philosopher %d has died.\n",
					get_time(data->start), phi->id);
				pthread_mutex_unlock(&data->mutex_write);
				break ;
			}
		}
		if (!data->nb_phi)
			break ;
		pthread_mutex_unlock(&data->mutex_death);
		phi = phi->next;
	}
	data->phi_end = 1;
	pthread_mutex_unlock(&data->mutex_death);
}

int	create_phi_thread(t_phi *phi, int nb_phi)
{
	t_phi	*tmp;
	int		i;

	i = 0;
	tmp = phi;
	while (i < nb_phi)
	{
		pthread_create(&tmp->thread, NULL, &routine, (void *)tmp);
		tmp = tmp->next;
		i++;
	}
	tmp = phi;
	monitoring(phi, phi->data);
	i = 0;
	while (i < nb_phi)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		nb_phi;

	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"));
	if (init_data(&data, av) == 0)
		return (printf("Check args format\n"));
	init_phi(&data);
	if (!data.philist)
		return (EXIT_FAILURE);
	nb_phi = data.nb_phi;
	if (create_phi_thread(data.philist, nb_phi) == 0)
		return (0);
	free_phi(&data, nb_phi);
	free_mutex_forks(&data, nb_phi);
	pthread_mutex_destroy(&data.mutex_death);
	pthread_mutex_destroy(&data.mutex_write);
	return (EXIT_SUCCESS);
}
