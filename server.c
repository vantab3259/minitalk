/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:32:12 by mudoh             #+#    #+#             */
/*   Updated: 2023/03/11 13:35:46 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	g_mess[5000000];

void	ft_reverse(int *i, char *byte, int *start, siginfo_t *siginfo)
{
	int	check_kill;

	check_kill = 1;
	g_mess[*i] = *byte;
	*byte = 0;
	if (g_mess[*i] == '\0')
	{
		ft_printf("%s\n", g_mess);
		*i = 0;
		*start = 0;
		check_kill = kill(siginfo->si_pid, SIGUSR2);
		signal_error(check_kill);
		return ;
	}
	(*i)++;
}

void	ft_handle_signal(int signum, siginfo_t *siginfo, void *context)
{
	static char	byte;
	static int	bit_received;
	static int	i;
	static int	start;

	(void)context;
	if (start == 1)
	{
		if (signum == SIGUSR2)
			byte |= (1 << bit_received);
		bit_received++;
		if (bit_received == 8)
		{
			bit_received = 0;
			ft_reverse(&i, &byte, &start, siginfo);
		}
		signal_error(kill(siginfo->si_pid, SIGUSR1));
	}
	else
	{
		start = 1;
		signal_error(kill(siginfo->si_pid, SIGUSR1));
	}
}
//sa.sa_mask est un objet de type sigset_t  structure contenant 
//les signaux a bloquer et qui est init a vide grace a sigemtyset.
// gerer les signaux, ta le choix entre 
//ft_handle et ft_sigaction (sigaction y'a plus de parametre).
//sa_sigaction a la place de la fonction standar sa_handler

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc > 1)
		ft_printf(VIOLET "To mush argument!\n" NORMAL);
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = ft_handle_signal;
	sa.sa_flags = SA_SIGINFO ;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf(JAUNE "PID : %d\n" NORMAL, getpid());
	while (1)
		pause();
	return (0);
}
