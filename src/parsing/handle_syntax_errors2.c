/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_errors2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:19:50 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/24 21:32:43 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outredir_errors(t_token *args)
{
	if (args->next == NULL)
		return (ft_perror("syntax error near unexpected token `newline'\n"), -1);
	if (args->next)
	{
		if (args->next->type == PIPE || \
			ft_strcmp(args->next->content, "|") == 0)
			return (ft_perror("syntax error near "
					"unexpected token '|'\n"), -1);
	}
	return (1);
}

int	inredir_errors(t_token *args)
{
	if (args->next)
	{
		if (args->next->type == ARGUMENT && args->next->content[0] == '|')
		{
			if (args->next->content[1] == '|')
				return (ft_perror("syntax error near "
						"unexpected token `||'\n"), -1);
			else
				return (ft_perror("syntax error near "
						"unexpected token `|'\n"), -1);
		}
	}
	else
		return (ft_perror(" syntax error near \
			unexpected token `newline'\n"), -1);
	return (1);
}

int	count_heredoc_errors(t_token *args)
{
	int	counter;

	counter = 0;
	while (args && (args->type == HERE_DOC || \
		ft_strcmp(args->content, "<<") == 0))
	{
		counter += 2;
		args = args->next;
	}
	if (args && (args->type == IN_REDIR || ft_strcmp(args->content, "<") == 0))
		counter++;
	if (counter > 6)
		counter = 6;
	return (counter);
}

int	handle_heredoc_error_output(int counter)
{
	int	i;

	i = 0;
	if (counter == 2)
		return (1);
	if (counter == 3)
		return (ft_perror("syntax error near unexpected token `newline'\n"), -1);
	ft_perror("syntax error near unexpected token '");
	while (i < (counter - 3))
	{
		ft_printf("<");
		i++;
	}
	return (ft_printf("'\n"), -1);
}

int	heredoc_errors(t_token *args)
{
	int	counter;

	if (args->next == NULL)
		return (ft_perror("syntax error near unexpected token `newline'\n"), -1);
	if (ft_strcmp(args->next->content, ">") == 0)
		return (ft_perror("syntax error near unexpected token `>'\n"), -1);
	if (ft_strcmp(args->next->content, ">>") == 0)
		return (ft_perror("syntax error near unexpected token `>>'\n"), -1);
	counter = count_heredoc_errors(args);
	return (handle_heredoc_error_output(counter));
}
