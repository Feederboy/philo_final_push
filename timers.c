/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:49:41 by matt              #+#    #+#             */
/*   Updated: 2022/04/09 00:59:20 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	get_time(struct timeval start)
{
	unsigned int	timestamp;
	struct timeval	end;

	gettimeofday(&end, NULL);
	timestamp = ((end.tv_sec - start.tv_sec)
			+ 1e-6 * (end.tv_usec - start.tv_usec)) * 1000;
	return (timestamp);
}

long long	get_ms_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ms_sleep(long long value)
{
	long long	start;

	start = get_ms_time();
	while ((get_ms_time() - start) < value)
	{
		usleep(500);
	}
}
