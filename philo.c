/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:58:22 by oqatim            #+#    #+#             */
/*   Updated: 2022/10/04 17:47:30 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosof.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data	data;
	int		i;

	if (ac < 5 || ac > 6)
		return (printf("Error 404"), 0);
	ft_atoi_args(&data, ac, av);
	if (ft_check_args(data, ac, av) == 1)
		return (0);
	pthread_mutex_init(&data.print, NULL);
	philo = ft_creat_philo(&data);
	if (philo == NULL)
		return (0);
	while (data.flag == 0)
	{
		if (philo->leave == 1)
			philo->data->all_ate++;
		ft_check_dead(philo);
	}
	i = -1;
	while (++i < data.nb_philo)
		pthread_mutex_destroy(&philo[i].fork);
	pthread_mutex_destroy(&data.print);
	free(philo);
	return (0);
}
