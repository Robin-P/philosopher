/*
** EPITECH PROJECT, 2018
** philo
** File description:
** create
*/

#include <stdlib.h>
#include "philo.h"

t_philo *create_philo(t_info *info, int id)
{
	t_philo *philo = malloc(sizeof(*philo));

	if (philo == NULL)
		return (NULL);
	philo->max_eat = info->time;
	philo->nb = 0;
	philo->id = id;
	philo->bool_left = NONE;
	philo->bool_right = NONE;
	philo->left = NULL;
	philo->right = NULL;
	philo->think = 0;
	return (philo);
}
