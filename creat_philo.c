/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:46:37 by oqatim            #+#    #+#             */
/*   Updated: 2022/10/04 17:44:39 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosof.h"

void	activities(t_philo *philos)
{
	pthread_mutex_lock(&philos->fork);
	print_message("has taken the first fork", philos->id, philos->data);
	pthread_mutex_lock(philos->second_fork);
	print_message("has taken the second fork", philos->id, philos->data);
	philos->should_die = ft_current_time() + philos->data->time_to_die;
	print_message("is eating", philos->id, philos->data);
	ft_usleep(philos->data->time_to_eat);
	pthread_mutex_unlock(&philos->fork);
	pthread_mutex_unlock(philos->second_fork);
	print_message("is sleeping", philos->id, philos->data);
	ft_usleep(philos->data->time_to_sleep);
	print_message("is thinking", philos->id, philos->data);
}

void	*ft_philo(void *philo)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)philo;
	if (philos->id % 2 == 0)
		usleep(20);
	philos->leave = 0;
	philos->should_die = philos->data->save_time + philos->data->time_to_die;
	while (i < philos->data->nb_of_meals || !(philos->data->nb_of_meals))
	{
		activities(philos);
		i++;
		usleep(20);
	}
	philos->leave = 1;
	return (NULL);
}

void	init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		if (i == data->nb_philo - 1)
			philo[i].second_fork = &philo[0].fork;
		else
			philo[i].second_fork = &philo[i + 1].fork;
		i++;
	}
}

t_philo	*ft_creat_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (NULL);
	while (++i < data ->nb_philo)
		pthread_mutex_init(&philo[i].fork, NULL);
	init_philo(data, philo);
	data->save_time = ft_current_time();
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_philo, &philo[i]))
			return (free(philo), NULL);
		usleep(10);
	}
	i = -1;
	while (++i < data->nb_philo)
		pthread_detach(philo[i].thread);
	return (philo);
}

void	ft_usleep(int time)
{
	long long	t;
	long long	time2;

	time2 = time;
	t = ft_current_time();
	while (ft_current_time() - t < time2)
		usleep(1);
}
