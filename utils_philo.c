/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 09:40:44 by oqatim            #+#    #+#             */
/*   Updated: 2022/10/04 17:47:11 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosof.h"

void	ft_atoi_args(t_data *data, int ac, char **av)
{
	data->flag = 0;
	data->all_ate = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_of_meals = ft_atoi(av[5]);
	else
		data->nb_of_meals = 0;
}

int	ft_check_args(t_data data, int ac, char **av)
{
	if (ac == 6 && data.nb_of_meals == 0)
		return (ft_puterr("ERROR : Wrong num of must_eat\n"));
	if (data.nb_philo < 0 || !check_if_int(av[1]))
		return (ft_puterr("ERROR : Wrong number of philosophers"));
	if (data.time_to_die < 60 || !check_if_int(av[2]))
		return (ft_puterr("ERROR : Wrong number of time_to_die\n"));
	if (data.time_to_eat < 60 || !check_if_int(av[3]))
		return (ft_puterr("ERROR : Wrong number of time_to_eat\n"));
	if (data.time_to_sleep < 60 || !check_if_int(av[4]))
		return (ft_puterr("ERROR : Wrong number of time_to_sleep\n"));
	return (0);
}

void	ft_check_dead(t_philo *philo)
{
	if (philo->data->all_ate == philo->data->nb_philo)
	{
		usleep(200);
		pthread_mutex_lock(&philo->data->print);
		philo->data->flag = 1;
	}
	if (ft_current_time() >= philo->should_die)
	{
		print_message("died", philo->id, philo->data);
		pthread_mutex_lock(&philo->data->print);
		philo->data->flag = 1;
	}
}

long long	ft_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	print_message(char *s, int id, t_data *data)
{
	pthread_mutex_lock(&data->print);
	printf("[%lld] %d %s\n", ft_current_time() - data->save_time, id, s);
	pthread_mutex_unlock(&data->print);
}
