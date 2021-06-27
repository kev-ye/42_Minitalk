/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:45:38 by kaye              #+#    #+#             */
/*   Updated: 2021/06/27 22:08:49 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	exit_with_msg(char *msg)
{
	if (msg)
		ft_putstr(msg);
	exit(EXIT_FAILURE);
}

static void	send_char(unsigned int c, pid_t pid)
{
	int	i;
	int	bit;

	i = 0;
	bit = 7;
	while(bit >= 0)
	{
		if (((c >> bit) % 2) == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit_with_msg(B_RED"Kill failed !\n"NONE);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit_with_msg(B_RED"Kill failed !\n"NONE);
		}
		usleep(100);
		--bit;
	}
}

static void	send_len(pid_t pid, char *str)
{
	size_t	len;
	int		i;
	int		bit;

	i = 0;
	bit = 31;
	len = ft_strlen(str);
	while(bit >= 0)
	{
		if (((len >> bit) % 2) == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit_with_msg(B_RED"Kill failed !\n"NONE);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit_with_msg(B_RED"Kill failed !\n"NONE);
		}
		usleep(100);
		--bit;
	}
}

static void	send_str(pid_t pid, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		send_char(str[i++], pid);
	ft_putstr(B_GREEN"--- STRING SUBMITTED ! ---\n"NONE);
}

static void	check_pid(char *pid)
{
	int	i;

	i = 0;
	while (pid && pid[i])
	{
		if (pid[i] < 48 || pid[i] > 57)
			exit_with_msg(B_RED"Not a valid pid!\n"NONE);
		++i;
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
		exit_with_msg(B_RED"Number of args is not valid!\n"NONE);
	check_pid(av[1]);
	send_len(ft_atoi(av[1]), av[2]);
	send_str(ft_atoi(av[1]), av[2]);
	return (SUCCESS);
}