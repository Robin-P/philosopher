/*
** EPITECH PROJECT, 2018
** ex
** File description:
** e
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void help()
{
	printf("USAGE\n\t./philo -p nbr_p -e nbr_e\n\nDESCRIPTION");
	printf("\n\t-p nbr_p number of philosophers\n\t-e nbr_e maximum ");
	printf("number times a philosopher eats before exiting the program\n");
	exit(0);
}

void flag_manager(int ac, char **av, t_info *info)
{
	int index = 1;

	while (index < ac) {
		if (av[index + 1] && strcmp(av[index], "-p") == 0)
			info->nb = atoi(av[++index]);
		else if (av[index + 1] && strcmp(av[index], "-e") == 0)
			info->time = atoi(av[++index]);
		else if (strcmp(av[index], "--help") == 0
			|| strcmp(av[index], "-h") == 0)
			help();
		++index;
	}
}

int check_flag(t_info *info)
{
	return (info->nb > 1 && info->time > 0 ? 0 : 84);
}

t_info *create()
{
	t_info *info = malloc(sizeof(*info));

	if (info == NULL)
		return (NULL);
	info->nb = -1;
	info->time = -1;
	return (info);
}

int main(int ac, char **av)
{
	int res = 0;
	t_info *info = create();

	RCFStartup(ac, av);
	if (info == NULL)
		return (84);
	flag_manager(ac, av, info);
	res = check_flag(info);
	if (res == 0)
		res = philosopher(info);
	free(info);
	RCFCleanup();
	return (res);
}
