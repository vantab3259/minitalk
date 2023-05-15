/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:17:59 by mudoh             #+#    #+#             */
/*   Updated: 2023/03/12 14:40:21 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	g_mess[5000000];

//puisque un octet = 8 bit que char et 1 octet donc on  vérifie si
//le bit à la position nb_bit de l'octet g_message[indice] est à 1 ou à 0.
void	handle_signal(int signal, siginfo_t *siginfo, void *context)
{
	static int	nb_bit;
	static int	i;

	(void)context;
	if (signal == SIGUSR1)
	{
		if (g_mess[i] & 1 << nb_bit)
			signal_error(kill(siginfo->si_pid, SIGUSR2));
		else
			signal_error(kill(siginfo->si_pid, SIGUSR1));
		nb_bit++;
		if (nb_bit == 8)
		{
			i++;
			nb_bit = 0;
		}
	}
	else
		exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	struct sigaction sa;

	if (argc == 3)
	{
		ft_checkpid(argv[1]);
		sigemptyset(&sa.sa_mask);
		sa.sa_sigaction = handle_signal;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		ft_strcpy(g_mess, argv[2]);
		signal_error(kill(ft_atoi(argv[1]), SIGUSR1));
		while (1)
			pause();
	}
	else
	{
		ft_printf(ROUGE "You nedd 3 argument" NORMAL);
		exit(EXIT_FAILURE);
	}
	return (0);
}