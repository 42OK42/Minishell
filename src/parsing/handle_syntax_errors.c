/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:20:03 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/05 02:51:28 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_errors(t_token *args)
{
	while (args)
	{
		if (args->prev == NULL)
			return (ft_perror("syntax error near "
					"unexpected token '|'\n"), -1);
		if (args->next)
		{
			if (args->type == PIPE && args->next->type == PIPE)
				return (ft_perror("syntax error near "
						"unexpected token '||'\n"), -1);
		}
		args = args->next;
	}
	return (1);
}

int	append_errors(t_token *args)
{
	if (args->next == NULL)
		return (ft_perror("syntax error near unexpected token `newline'\n"), -1);
	if (ft_strcmp(args->next->content, ">") == 0)
		return (ft_perror("syntax error near unexpected token `>'\n"), -1);
	if (ft_strcmp(args->next->content, ">>") == 0)
		return (ft_perror("syntax error near unexpected token `>>'\n"), -1);
	return (1);
}

int	handle_redirection_errors(t_token *arg)
{
	if (arg->type == IN_REDIR)
	{
		if (inredir_errors(arg) == -1)
			return (-1);
	}
	else if (arg->type == OUT_REDIR)
	{
		if (outredir_errors(arg) == -1)
			return (-1);
	}
	else if (arg->type == HERE_DOC)
	{
		if (heredoc_errors(arg) == -1)
			return (-1);
	}
	else if (arg->type == APPEND)
	{
		if (append_errors(arg) == -1)
			return (-1);
	}
	return (0);
}

int	handle_errors(t_token *args)
{
	while (args)
	{
		if (handle_redirection_errors(args) == -1)
			return (-1);
		if (args->type == PIPE)
		{
			if (pipe_errors(args) == -1)
				return (-1);
		}
		args = args->next;
	}
	return (1);
}
