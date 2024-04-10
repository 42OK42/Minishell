/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_words2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:24:38 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/01 00:53:46 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *word)
{
	char	*builtins[8];
	int		i;

	i = 0;
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	while (builtins[i])
	{
		if (strcmp(word, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*check_access_and_allocate(char **paths, char *command)
{
	char	*full_path;
	int		i;

	full_path = malloc(256);
	i = 0;
	while (paths[i] != NULL)
	{
		ft_strlcpy(full_path, paths[i], 256);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}
		i++;
	}
	free(full_path);
	return (NULL);
}

char	*find_command_path(char *command)
{
	char	*path;
	char	**paths;
	char	*full_path;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	full_path = check_access_and_allocate(paths, command);
	if (full_path)
	{
		free_array(paths);
		return (full_path);
	}
	free_array(paths);
	return (NULL);
}

t_type	check_redirections(char *word, t_data *data, int word_index)
{
	if (ft_strcmp(word, "<") == 0 && data->quote_flag[word_index] \
		!= (int) '\'' && data->quote_flag[word_index] != (int) '\"')
		return (IN_REDIR);
	if (ft_strcmp(word, ">") == 0 && data->quote_flag[word_index] \
		!= (int) '\'' && data->quote_flag[word_index] != (int ) '\"')
		return (OUT_REDIR);
	if (ft_strcmp(word, ">>") == 0 && data->quote_flag[word_index] \
		!= (int) '\'' && data->quote_flag[word_index] != (int) '\"')
		return (APPEND);
	if (ft_strcmp(word, "<<") == 0 && data->quote_flag[word_index] \
		!= (int) '\'' && data->quote_flag[word_index] != (int) '\"')
		return (HERE_DOC);
	return (ARGUMENT);
}

int	is_redirection(t_type type)
{
	return (type == IN_REDIR || type == OUT_REDIR \
		|| type == APPEND || type == HERE_DOC);
}
