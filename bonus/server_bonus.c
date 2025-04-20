/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:44:14 by noaziki           #+#    #+#             */
/*   Updated: 2025/04/20 20:48:33 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	check_bytes(char *arr)
{
	if ((arr[0] & 128) == 0)
		return (1);
	if ((arr[0] & 224) == 192)
		return (2);
	if ((arr[0] & 240) == 224)
		return (3);
	if ((arr[0] & 248) == 240)
		return (4);
	return (1);
}

static void	handle_byte(char *arr, int *bit, int *byte)
{
	static int	exp;

	(*byte)++;
	if (*byte == 1)
		exp = check_bytes(arr);
	if (*byte == 1 && exp == 1)
	{
		write(1, &arr[0], 1);
		*byte = 0;
		ft_bzero(arr, 1);
	}
	if (*byte == exp && exp != 1)
	{
		write(1, arr, exp);
		*byte = 0;
		ft_bzero(arr, 4);
	}
	*bit = 0;
}

void	handle_sig(int sig, siginfo_t *info, void *context)
{
	static char		arr[4];
	static int		bit;
	static int		byte;
	static pid_t	id;

	(void)context;
	if (id == 0)
		id = info->si_pid;
	if (id != info->si_pid)
	{
		id = 0;
		bit = 0;
		byte = 0;
		ft_bzero(arr, 4);
	}
	if (sig == SIGUSR1)
		arr[byte] |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		if (arr[0] == '\0')
			kill(info->si_pid, SIGUSR1);
		handle_byte(arr, &bit, &byte);
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = getpid();
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	sa.sa_sigaction = &handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
