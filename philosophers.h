/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:13:12 by matt              #+#    #+#             */
/*   Updated: 2022/04/09 01:02:26 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_phi
{
	int				id;
	int				left;
	int				right;
	int				diner;
	bool			is_alive;
	unsigned int	last_diner;
	pthread_t		thread;
	struct s_phi	*prev;
	struct s_phi	*next;
	struct s_data	*data;
}				t_phi;

typedef struct s_data
{
	int				nb_phi;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	struct timeval	start;
	unsigned int	time_to_sleep;
	int				diner_goal;
	t_phi			*philist;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	*mutex_forks;
	int				phi_end;
}				t_data;

void			*routine(void *phi);
void			ft_sleep(t_phi *phi);
void			ft_eat(t_phi *phi);
void			ft_think(t_phi *phi);
t_phi			*new_phi(int id);
void			init_phi(t_data *data);
int				check_args(t_data *data, char **av);
int				init_data(t_data *data, char **av);
int				create_phi_thread(t_phi *phi, int nb);
int				check_death(t_data *data);
int				protect_write(char *str, t_phi *phi, int id);
void			print_timestamp(int ms);
int				ft_isdigit(int c);
int				ft_strlen(char *str);
int				nblen(int nb);
int				ft_atoi(const char *nptr);
void			free_phi(t_data *list, int n);
t_phi			*get_phi(t_phi *list, int id);
void			add_end(t_phi **list, t_phi *item);
void			add_start(t_phi **list, t_phi *item);
void			free_list(t_phi *list, int n);
unsigned int	get_time(struct timeval start);
void			get_forks(t_phi *phi);
void			put_forks_back(t_phi *phi);
int				checker_diner(t_phi *phi);
int				checker(t_phi *phi, t_data *data);
void			monitoring(t_phi *phi, t_data *data);
long long		get_ms_time(void);
void			ms_sleep(long long value);
void			free_mutex_forks(t_data *data, int n);

#endif
