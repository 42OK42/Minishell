/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:21:24 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/03 13:50:47 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_flag;

void	handle_sigint_l(int sig)
{
	if (sig != SIGINT)
		return ;
	//ft_printf("sigint_l");
	g_sig_flag = 130;
	write(1, "\n", 1);
}

void	handle_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	g_sig_flag = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_handle_cat_backslash(int signum)
{
	if (signum != SIGQUIT)
		return ;
	g_sig_flag = 131;
	printf("Quit (core dumped)\n");
}

void	handle_heredoc(int signum)
{
	if (signum != SIGINT)
		return ;
	//ft_printf("heredoc_handler");
	g_sig_flag = 130;
	//write(2,"test44",6);
	rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	return ;
}
