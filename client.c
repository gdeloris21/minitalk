/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdeloris <gdeloris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:39:43 by gdeloris          #+#    #+#             */
/*   Updated: 2022/02/28 21:48:23 by gdeloris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int bit, int pid)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			write(1, "Problem sending the signal!\n", 29);
			exit(1);
		}
		usleep(150);
	}
	if (bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			write(1, "Problem sending the signal!\n", 29);
			exit(1);
		}
		usleep(150);
	}
}

void	convert(int c, int pid)
{
	t_byte_struct	byte_char;

	*(unsigned char *)&byte_char = (unsigned char)c;
	send_signal(byte_char.b1, pid);
	send_signal(byte_char.b2, pid);
	send_signal(byte_char.b3, pid);
	send_signal(byte_char.b4, pid);
	send_signal(byte_char.b5, pid);
	send_signal(byte_char.b6, pid);
	send_signal(byte_char.b7, pid);
	send_signal(byte_char.b8, pid);
}

void	handler(int sig)
{
	if (sig == SIGUSR2)
		write(1, "Singnal received!\n", 19);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	signal(SIGUSR2, handler);
	if (argc == 3)
	{
		pid = ft_atoi((const char *)argv[1]);
		if (pid == 0 || pid < 0)
		{
			write(1, "Invalid PID!\n", 13);
			return (0);
		}
		while (argv[2][i])
		{
			convert((int)argv[2][i], pid);
			i++;
		}
	}
	else
		write(1, "Usage: ./client [PID] [STRING_TO_PASS]\n", 40);
	return (0);
}
