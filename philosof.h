/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosof.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:56:54 by oqatim            #+#    #+#             */
/*   Updated: 2022/10/04 17:50:03 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOF_H
# define PHILOSOF_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_data
{
	int				nb_philo;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				nb_of_meals;
	long			save_time;
	int				flag;
	int				all_ate;
	pthread_mutex_t	print;
}	t_data;
typedef struct s_philo
{
	int				id;
	long			should_die;
	int				leave;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*second_fork;
	t_data			*data;
}	t_philo;

void		activities(t_philo *philos);
void		*ft_philo(void *philo);
void		init_philo(t_data *data, t_philo *philo);
t_philo		*ft_creat_philo(t_data *data);
void		ft_usleep(int time);
void		ft_atoi_args(t_data *data, int ac, char **av);
int			ft_check_args(t_data data, int ac, char **av);
void		ft_check_dead(t_philo *philo);
long long	ft_current_time(void);
void		print_message(char *s, int id, t_data *data);
int			ft_isdigit(int c);
int			check_if_int(char *str);
int			ft_atoi(const char *str);
int			ft_strlen(char *str);
int			ft_puterr(char *err);

#endif
