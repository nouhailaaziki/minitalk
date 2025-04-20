/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:44:21 by noaziki           #+#    #+#             */
/*   Updated: 2025/04/20 20:47:12 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(pid_t pid, char c)
{
	int	bit;
	int	k;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 1)
			k = kill(pid, SIGUSR1);
		else
			k = kill(pid, SIGUSR2);
		if (k != 0)
		{
			ft_putstr_fd("PID not found or invalid!\n", 2);
			exit (1);
		}
		usleep(250);
		usleep(100);
		bit++;
	}
}

void	send_message(pid_t pid, const char *str)
{
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
}

void	check_forbidden_chars(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '+' || argv[i] == '-')
		{
			if (!argv[i + 1] || argv[i + 1] < '0' || argv[i + 1] > '9')
			{
				ft_putstr_fd("PID must be numeric value!\n", 2);
				exit(1);
			}
			if (i > 0 && argv[i - 1] != ' ')
			{
				ft_putstr_fd("PID must be numeric value!\n", 2);
				exit(1);
			}
		}
		else if (argv[i] < '0' || argv[i] > '9')
		{
			ft_putstr_fd("PID must be numeric value!\n", 2);
			exit(1);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client <PID> <message>\n", 2);
		return (1);
	}
	check_forbidden_chars(argv[1]);
	pid = ft_atoi(argv[1]);
	if ((pid <= 2147483647 && pid > 100)
		|| (pid > -2147483648 && pid < -100))
		send_message(pid, argv[2]);
	else
		ft_putstr_fd("The PID is out of acceptable range!\n", 2);
	return (0);
}
