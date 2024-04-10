/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:49:09 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 03:19:41 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	data = malloc1(sizeof(t_data));
	argv = argv + 1;
	data->argc = argc;
	copy_env(env, data);
	parsing(data);
}
