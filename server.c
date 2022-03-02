/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdeloris <gdeloris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:56:21 by ael-hask          #+#    #+#             */
/*   Updated: 2022/02/28 22:00:00 by gdeloris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_byte_struct	g_char_byte;

void	set_bit(int bit, int	*i, siginfo_t *siginfo)
{
	if (*i == 1)
		g_char_byte.b1 = bit;
	if (*i == 2)
		g_char_byte.b2 = bit;
	if (*i == 3)
		g_char_byte.b3 = bit;
	if (*i == 4)
		g_char_byte.b4 = bit;
	if (*i == 5)
		g_char_byte.b5 = bit;
	if (*i == 6)
		g_char_byte.b6 = bit;
	if (*i == 7)
		g_char_byte.b7 = bit;
	if (*i == 8)
	{
		g_char_byte.b8 = bit;
		write(1, &*(unsigned char *)&g_char_byte, 1);
		kill(siginfo->si_pid, SIGUSR2);
		*i = 0;
	}
}

void	handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	static int	i;

	(void)ucontext;
	if (!i)
		i = 1;
	if (sig == SIGUSR1)
	{
		set_bit(0, &i, siginfo);
		i++;
	}
	if (sig == SIGUSR2)
	{
		set_bit(1, &i, siginfo);
		i++;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "PID: ", 6);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
