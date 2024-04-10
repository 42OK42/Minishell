/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:18:10 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/05 03:09:09 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_space_info *info, char *s)
{
	if (info->j > 0 && (info->new_str)[info->j - 1] != ' ')
		(info->new_str)[info->j++] = ' ';
	while (s[info->i] == '|')
	{
		(info->new_str)[info->j++] = s[info->i++];
		if (s[info->i] != ' ')
			(info->new_str)[info->j++] = ' ';
	}
}

char	*add_spaces_to_str(char *s, int len, int additional_spaces)
{
	int				s_q;
	int				d_q;
	t_space_info	info;

	info.new_str = malloc1(len + additional_spaces + 1);
	info.i = 0;
	info.j = 0;
	s_q = 0;
	d_q = 0;
	info.special_char_count = 0;
	while (info.i < len)
	{
		update_quote_flags(&s_q, &d_q, s[info.i]);
		if ((s[info.i] == '<' || s[info.i] == '>' || \
			s[info.i] == '|') && !s_q && !d_q)
		{
			handle_special_char(&info, s, '<');
			handle_special_char(&info, s, '>');
			handle_pipe(&info, s);
		}
		else
			info.new_str[info.j++] = s[info.i++];
	}
	info.new_str[info.j] = '\0';
	return (info.new_str);
}

char	*add_spaces(char *s)
{
	int		len;
	int		additional_spaces;
	char	*new_str;
	int		seq_count;

	len = strlen(s);
	seq_count = 0;
	additional_spaces = count_additional_spaces(s, seq_count);
	new_str = add_spaces_to_str(s, len, additional_spaces);
	free(s);
	return (new_str);
}
