/*
** EPITECH PROJECT, 2018
** philo
** File description:
** include
*/

#ifndef PHILO_H_
#define PHILO_H_

#include "extern.h"
#define THINK_MAX 200
#define UNKNOWN '\0'
#define NONE 0
#define TAKE 1

typedef struct s_info {
	size_t time;
	size_t nb;
} t_info;

typedef struct s_philo {
	pthread_t thread;
	char state;
	size_t max_eat;
	size_t nb;
	size_t id;
	char bool_left;
	char bool_right;
	pthread_mutex_t *right;
	pthread_mutex_t *left;
	size_t think;
} t_philo;

int philosopher(t_info *info);
t_philo *create_philo(t_info *info, int id);

#endif /* !PHILO_H_ */
