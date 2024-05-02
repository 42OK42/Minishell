/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:21:24 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/25 16:10:22 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_flag;

void	handle_sigint_l(int sig)
{
	if (sig != SIGINT)
		return ;
	g_sig_flag = 130;
	write(1, "\n", 1);
}

void	handle_sigint_include_rd(int sig)
{
	if (sig != SIGINT)
		return ;
	g_sig_flag = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	g_sig_flag = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	ft_handle_cat_backslash(int signum)
{
	if (signum != SIGQUIT)
		return ;
	g_sig_flag = 131;
	ft_printf("Quit (core dumped)\n");
}

void	handle_heredoc(int signum)
{
	if (signum != SIGINT)
		return ;
	g_sig_flag = 130;
	rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	return ;
}
