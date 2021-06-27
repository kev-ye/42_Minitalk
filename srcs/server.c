/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:45:53 by kaye              #+#    #+#             */
/*   Updated: 2021/06/27 19:13:35 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <libc.h>

static void print_str(int opt)
{
    static int c = 0;
    static int i = 0;
    // static int len = 0;
    // static int max = -1;

    if (opt == SIGUSR1)
        c = c | (1 << i);
    ++i;
    // if (len != -1)
    //     ++len;
    // if (len == 32)
    // {
    //     ft_printf(B_GREEN"String length: [%d]\n"NONE, c);
    //     ft_printf(B_YELLOW"Content : ["NONE);
    //     max = c;
    //     len = -1;
    //     i = 0;
    //     c = 0;
    // }
    if (i == 8)
    {
        // ft_putchar(c);
        write(1, &c, 1);
        i = 0;
        c = 0;
        // --max;
    }
    // if (max == 0)
    // {
    //     len = 0;
    //     i = 0;
    //     c = 0;
    //     max = -1;
    //     ft_printf(B_YELLOW"]\n"NONE);
    //     ft_printf(B_GREEN"END OF STRING!\n"NONE);
    // }
}

static void  ft_handle(int code)
{
    if (code == SIGUSR1)
        print_str(SIGUSR1);
    else
        print_str(SIGUSR2);
}

int main(void)
{
    pid_t pid;

    pid = getpid();
    ft_printf("PID : "B_CYAN"%d\n"NONE, pid);

    signal(SIGUSR1, ft_handle);
    signal(SIGUSR2, ft_handle);
    while(1)
        pause();
    return (SUCCESS);
}