/*
** EPITECH PROJECT, 2018
** zerefsfdsdfsdffsd
** File description:
** fsdfsdfsdf
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "philo.h"

void get_stick(t_philo *philo)
{
	if ((philo->bool_right == NONE)
	    && (pthread_mutex_trylock(philo->right) == 0)) {
		philo->bool_right = TAKE;
		lphilo_take_chopstick(philo->right);
	}
	if ((philo->bool_left == NONE)
	    && (pthread_mutex_trylock(philo->left) == 0)) {
		philo->bool_left = TAKE;
		lphilo_take_chopstick(philo->left);
	}
}

void philo_eat(t_philo *philo)
{
	philo->nb += 1;
	philo->bool_right = NONE;
	philo->bool_left = NONE;
	lphilo_eat();
	lphilo_release_chopstick(philo->right);
	pthread_mutex_unlock(philo->right);
	lphilo_release_chopstick(philo->left);
	pthread_mutex_unlock(philo->left);
}

int philo_think(t_philo *philo)
{
	philo->think = 0;
	while ((philo->think < THINK_MAX)
	       && (philo->bool_right == NONE || philo->bool_left == NONE)) {
		get_stick(philo);
		philo->think += 1;
	}
	if (philo->think < THINK_MAX)
		return (0);
	lphilo_think();
	if (philo->bool_right == TAKE) {
		philo->bool_right = NONE;
		lphilo_release_chopstick(philo->right);
		pthread_mutex_unlock(philo->right);
	} else if (philo->bool_left == TAKE) {
		philo->bool_left = NONE;
		lphilo_release_chopstick(philo->left);
		pthread_mutex_unlock(philo->left);
	}
	return (1);
}

void *process(void *data)
{
	t_philo *philo = (t_philo*) data;

	while (philo->nb < philo->max_eat) {
		if (philo_think(philo) == 0) {
			philo_eat(philo);
			lphilo_sleep();
		}
	}
	pthread_exit(NULL);
}

int philosopher(t_info *info)
{
	t_philo *array[info->nb];
	pthread_mutex_t mutex[info->nb];

	for (size_t index = 0 ; index < info->nb ; ++index) {
		pthread_mutex_init(&mutex[index], NULL);
	}
	for (size_t index = 0 ; index < info->nb ; ++index) {
		array[index] = create_philo(info, index);
		array[index]->left = &mutex[index];
		array[index]->right = ((index == 0) ? &mutex[info->nb - 1] : &mutex[index - 1]);
		if ((array[index] == NULL)
		    || (pthread_create(&array[index]->thread, NULL, process, array[index]) != 0))
			exit(84);
	}
	for (size_t index = 0 ; index < info->nb ; ++index)
		pthread_join(array[index]->thread, NULL);
	for (size_t index = 0 ; index < info->nb ; ++index) {
		pthread_mutex_destroy(&mutex[index]);
		free(array[index]);
	}
	return (0);
}
