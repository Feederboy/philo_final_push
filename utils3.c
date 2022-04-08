/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:32:33 by matt              #+#    #+#             */
/*   Updated: 2022/04/09 00:59:55 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	add_end(t_phi **list, t_phi *item)
{
	t_phi	*tmp;

	if (!(*list))
	{
		*list = item;
		item->next = item;
		item->prev = item;
		return ;
	}
	tmp = *list;
	while (tmp->next != *list)
		tmp = tmp->next;
	tmp->next = item;
	item->prev = tmp;
	item->next = *list;
	(*list)->prev = item;
}

void	free_mutex_forks(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&data->mutex_forks[i]);
		i++;
	}
	free(data->mutex_forks);
}
