/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:45:53 by kaye              #+#    #+#             */
/*   Updated: 2021/06/27 23:19:41 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_len(int *len, int *c, int *i, int *max)
{
	if (*len == 0)
	{
		ft_putstr(B_GREEN"--- String length: [");
		ft_putnbr(*c);
		ft_putstr("] ---\n"NONE);
		ft_putstr(B_YELLOW"-> Content : ["NONE);
		*max = *c;
		*len = 32;
		*i = 8;
		*c = 0;
	}
}

static void	print_end(int *len, int *c, int *i, int *max)
{
	if (*max == 0)
	{
		*len = 32; // bug here
		*i = 8;
		*c = 0;
		*max = -1;
		ft_putstr(B_YELLOW"] <-\n"NONE);
		ft_putstr(B_GREEN"--- END OF STRING ! ---\n"NONE);
	}
}

static void	print_str(int opt)
{
	static int	c = 0;
	static int	i = 7;
	static int	len = 31;
	static int	max = -1;

	if (opt == SIGUSR1 && len != 32)
		c = c | (1 << len);
	else if (opt == SIGUSR1 && len == 32)	
		c = c | (1 << i);
	print_len(&len, &c, &i, &max);
	if (i == 0)
	{
		ft_putchar(c);
		i = 8;
		c = 0;
		--max;
	}
	print_end(&len, &c, &i, &max);
	if (len != 32) // bug here
		--len;
	if (len == 32)
		--i;
}

static void	ft_handle(int code)
{
	if (code == SIGUSR1)
		print_str(SIGUSR1);
	else
		print_str(SIGUSR2);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putstr("PID : ["B_CYAN);
	ft_putnbr(pid);
	ft_putstr(NONE"]\n");
	while(1)
	{
		signal(SIGUSR1, ft_handle);
		signal(SIGUSR2, ft_handle);
		pause();
	}
	return (SUCCESS);
}