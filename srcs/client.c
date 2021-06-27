/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:45:38 by kaye              #+#    #+#             */
/*   Updated: 2021/06/27 19:28:12 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <libc.h>

static void exit_with_msg(char *msg)
{
    if (msg)
        ft_putstr(msg);
    exit(EXIT_FAILURE);
}

int	ft_conv_dh_pf(int n, int low_up)
{
	if (n < 10)
		return (n + '0');
	else
	{
		if (low_up)
			return (n - 10 + 'A');
		else
			return (n - 10 + 'a');
	}
}

size_t	ft_uintlen_base_pf(unsigned int n, int base)
{
	size_t	count;

	if (n)
		count = 0;
	else
		count = 1;
	while (n)
	{
		n = n / base;
		++count;
	}
	return (count);
}

char	*ft_utoa_base_pf(unsigned int un, int base, int low_up)
{
	size_t	len;
	char	*str;

	len = ft_uintlen_base_pf(un, base);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = ft_conv_dh_pf((un % base), low_up);
		un /= base;
	}
	return (str);
}


static void send_char(unsigned int c, pid_t pid)
{
    // write(1, &c, 1);
    // return ;
    printf("%u\n", c);
    char *c_to_bit;
    size_t len;
    int i;

    c_to_bit = ft_utoa_base_pf(c, 2, 0);
    if (!c_to_bit)
        exit_with_msg(B_RED"Malloc failed!\n"NONE);
    len = ft_strlen(c_to_bit);
    i = 0;
    while(c_to_bit[len - 1])
    {
        if (c_to_bit[len - 1] == '1')
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(100);
        --len;
        ++i;
    }
    while (i++ < 8)
    {
        kill(pid, SIGUSR2);
        usleep(100);
    }
    free(c_to_bit);
}

// static void send_len(pid_t pid, char *str)
// {
//     size_t len;

//     len = ft_strlen(str);
//     send_char((int)len, pid);
// }

static void send_str(pid_t pid, char *str)
{
    int i;

    i = 0;
    while (str && str[i])
        send_char(str[i++], pid);
}

static void  check_pid(char *pid)
{
    int i;

    i = 0;
    while (pid && pid[i])
    {
        if (!ft_isdigit(pid[i]))
            exit_with_msg(B_RED"Not a valid pid!\n"NONE);
        ++i;
    }
}

int main(int ac, char **av)
{
    if (ac != 3)
        exit_with_msg(B_RED"Number of args is not valid!\n"NONE);
    check_pid(av[1]);
    // send_len(ft_atoi(av[1]), av[2]);
    send_str(ft_atoi(av[1]), av[2]);
    return (SUCCESS);
}