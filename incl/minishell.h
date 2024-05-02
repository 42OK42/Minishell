/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:41:45 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/25 16:28:25 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../libft/get_next_line_bonus.h"
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <time.h>
# include <errno.h>

extern volatile sig_atomic_t	g_sig_flag;

typedef enum e_type
{
	ARGUMENT,
	IN_REDIR,
	OUT_REDIR,
	HERE_DOC,
	APPEND,
	PIPE,
	COMMAND,
	BUILT_IN,
	HD_PREP,
}	t_type;

typedef struct s_token 
{
	char			*content;
	t_type			type;
	int				quoted;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_data
{
	int		i;
	int		j;
	int		j2;
	char	current_quote;
	int		index1;
	int		command_flag;
	int		argc;
	int		len;
	char	*env_value;
	int		env_len;
	int		*quote_flag;
	int		exit;
	int		pipes;
	int		args;
	int		cmds;
	int		x;
	int		solo;
	int		in_dirs;
	int		out_dirs;
	int		fd_in;
	int		fd_out;
	int		fd[2];
	int		fd2[2];
	int		pid;
	pid_t	*pids;
	int		part;
	int		cat_flag;
	int		parts;
	int		index;
	char	**env;
	int		saved_stdin;
	int		saved_stdout;
	int		closed;
	int		here_doc;
	int		hd_flag;
	int		infile_flag;
	int		open_flags;
	int		app_flags;
	char	**cmd_args;
	char	**echo_args;
	char	**files;
}	t_data;

typedef struct s_space_info
{
	char	*new_str;
	int		j;
	int		i;
	int		special_char_count;
}	t_space_info;

//main
int			main(int argc, char **argv, char **env);

//parsing
void		handle_sigint_include_rd(int sig);
char		*get_env_value2(t_data *data, char *str);
void		part2(t_token *first_token, t_data *data);
int			is_builtin(char *word);
char		*check_access_and_allocate(char **paths, char *command);
char		*find_command_path(char *command, t_data *data);
int			count_words(const char *s, char c);
void		assign_word(char **result, int word_index, \
	char const *start, int length);
int			is_enclosed_in_quotes(char const *start, int length, char quote);
char		*ft_strndup(const char *s, size_t n);
int			ft_count_words10(char const *s, char c);
void		free_allocated_memory(char **array, int index);
char		*handle_quotes(const char *s, char c, t_data *data, char \
	*current_quote);
char		**ft_split_modified(char const *s, char c, t_data *data);
t_type		check_redirections(char *word, t_data *data, int word_index);
int			is_redirection(t_type type);
t_type		get_token_type(char *word, t_data *data, \
	int word_index, t_token *last);
t_token		*create_token(char *word, t_data *data, \
	int word_index, t_token *last);
t_token		*add_token(t_token *last, char *word, t_data *data, int word_index);
void		free_word_and_replace(int i, int j, char **words);
void		remove_empty_quotes(char **words);
int			process_single_quote(char *word, int \
	*result, t_data *data, int word_index);
int			process_double_quote(char *word, int \
	*result, t_data *data, int word_index);
int			find_length_new_word(char *word, t_data *data, int word_index);
void		process_quotes(char *word, char *new_word, t_data *data, int *nwi);
char		*create_new_word(char *word, t_data *data, \
	int word_index, int length_new_word);
char		*update_word(char *word, t_data *data, int word_index);
int			quote_bullshit(char **words, t_data *data);
int			find_length_var(char *line, int i);
void		fetch_env_value(t_data *data, char *line, int i, int len_var);
char		*actually_expand(t_data *data, char *line, int i);
int			line_only_spaces(char	*line, int i);
int			count_dollar_pairs(char *s);
char		*replace_double_dollar(char *line);
void		update_quote_flags(int *single_q, int *double_q, char c);
char		*process_dollar_expansion(char *line, t_data *data, int *i);
char		*expand(char *line, t_data *data);
int			find_dollar(char *line);
void		free_words(char **words);
int			count_special_char_sequence(const char *s, int \
	*i, char target_char);
void		prep_signals(t_token *arg, t_data *data);
int			count_pipe_characters(const char *s, int *i);
int			count_additional_spaces(const char *s);
char		*add_spaces_to_str(char *s, int len, int additional_spaces);
char		*add_spaces(char *s);
void		print_words(char **words, t_data *data);
void		process_tokens(char **words, t_data *data, \
	t_token **first_token, t_token **last_token);
int			process_input_line(char *line, t_data *data, \
	t_token **first_token, t_token **last_token);
int			pipe_errors(t_token *args);
int			outredir_errors(t_token *args);
int			inredir_errors(t_token *args);
void		find_input(t_token *arg, t_data *data);
int			count_heredoc_errors(t_token *args);
int			handle_heredoc_error_output(int counter);
int			heredoc_errors(t_token *args);
int			append_errors(t_token *args);
int			handle_redirection_errors(t_token *arg);
int			handle_errors(t_token *args);
void		process_line(char *line, t_data *data);
void		parsing(t_data *data);
void		handle_special_char(t_space_info *info, char *s, char c);
void		process_line(char *line, t_data *data);
int			line_only_spaces1(char *line);
void		handle_sigint_l(int sig);
void		handle_sigint(int sig);
void		ft_handle_cat_backslash(int signum);
void		handle_heredoc(int signum);
void		read_here_doc(t_token *args, t_data *data);
int			not_heredoc(char *line, int i);

//execute parts
void		handle_part(t_token *arg, t_data *data);
void		handle_beginning(t_token *args, t_data *data);
void		handle_middle(t_token *args, t_data *data);
void		handle_end(t_token *args, t_data *data);
int			check_in_redir(t_data *data);
void		handle_solo(t_token *args, t_data *data);
t_token		*get_correct_args(t_token *args, t_data *data);
t_token		*get_correct_place(t_token *args);

//execute REDIRS helper
void		counting_redirs(t_token *args, t_data *data);
void		get_fd_in(t_token *args, t_data *data);
void		get_fd_in_solo(t_token *args, t_data *data);
char		*get_correct_infile(t_token *args, t_data *data);
char		*get_infile_name(t_token *args, t_data *data);
void		get_fd_out(t_token *args, t_data *data);
char		*get_outfile_name(t_token *args, t_data *data);
void		create_files(t_token *args, t_data *data);
int			get_file_type(t_token *args, t_data *data);
char		*get_correct_outfile(t_token *args, t_data *data);
void		handle_in_redirection_s(t_token *args, t_data *data);
void		handle_out_redirection_s(t_token *args, t_data *data);
void		handle_in_redirection_b(t_token *args, t_data *data);
void		handle_out_redirection_b(t_token *args, t_data *data);
void		handle_in_redirection_m(t_token *args, t_data *data);
void		handle_out_redirection_m(t_token *args, t_data *data);
void		handle_in_redirection_e(t_token *args, t_data *data);
void		handle_out_redirection_e(t_token *args, t_data *data);
void		restore_std_io(t_data *data);

//execute commands
void		exec_args(t_token *first_token, t_data *data);
void		exec_args2(t_token *args, t_data *data);
void		exec_args3(t_token *args, t_data *data);
void		exec_args4(t_token *args, t_data *data);
void		exec_command(t_token *args, t_data *data);
char		**get_cmd_args(t_token *args, char *cmd);
void		execution(t_token *args, char *cmd_path, t_data *data, \
		char **envp);
char		*find_command_path3(t_data *data, char *str);
void		solo_command(t_data *data, t_token *arg);

//execute HERE_DOC
void		handle_here_doc(t_data *data, char *end, int fd_out);
char		*execute_here_doc(t_data *data, char *delimiter);
void		limit_error(t_data *data, char *end);

//execute built_ins
void		exec_built_ins(t_token *args, t_data *data);
char		**get_cmd_arg2(t_token *args);
void		exec_echo(t_data *data, t_token *args);
void		get_echo_args(t_data *data, t_token *arg);
void		fill_array(t_data *data, t_token *arg2);
void		exec_cd(char **cmd_args, t_data *data);
void		cdhome(t_data *data, char *old_pwd);
void		exec_pwd(void);
void		exec_export(char **cmd_args, t_data *data);
void		exec_env(t_data *data);
void		exec_unset(char **cmd_args, t_data *data);
void		exec_exit(t_token *args, char **cmd_args, t_data *data);
void		exec_exit2(char **cmd_args, t_data *data);
void		non_numeric_argument(char **cmd_args, t_token *args, t_data *data);

//execute arguments
void		exec_argument(t_token *arg, t_data *data);
void		exec_argument2(t_token *arg, t_data *data);
void		add_pwd_to_path(t_data *data);
void		increase_sh_level(t_data *data);
char		*get_cmd_path(t_token *arg, t_data *data);
void		replace_in_env(char *var_delete, char *var_add, t_data *data);
void		wait_for_children(t_data *data);
char		**get_right_args(t_token *args);
void		solo_argument(t_data *data, t_token *arg);

//built_ins helper
int			is_only_n(char *arg);
int			isnewlineflag(char *arg);
int			cmd_check(char *cmd_args);
int			check_variable_name(char *cmd, char *disallowed_chars);
char		**erase_var(t_data *data, char *var);
char		*var_name(char *env_name);
void		empty_export(t_data *data);
void		ft_print_export(t_data *data);
int			modulo(long int status);
int			negative(int status);
char		*get_wd(void);
int			var_in_env(char	*str, t_data *data);
int			find_variable_to_replace(char *var_delete, t_data *data);
void		replace_variable_in_env(int index, char *var_add, t_data *data);
int			check_variable(char *var);
void		replace_or_add_env_var(char *cmd_arg, t_data *data);

//general helpers
char		*ft_strncpy(char *dest, const char *src, size_t n);
char		*ft_strcat(char *dest, const char *src);
void		*malloc1(size_t size);
char		**convert_str_to_array(char *str);

//execute helpers
void		copy_env(char **env, t_data *data);
int			fork1(void);
char		*trim_strfront(char *str, int x);
char		*get_env_value(t_data *data, char *str);
char		*get_env_value1(t_data *data, char *str);
char		*find_command_path2(char *cmd, t_data *data);

//execute_prep
void		init_struct(t_data *data);
void		prep_next_part(t_data *data);
void		check_infile(t_data *data, char *filename);
void		add_infile(t_data *data, char *filename);
void		counting(t_token *args, t_data *data);
void		get_fd_nums(char **argv, t_data *data);

//list_helper
t_token		*find_beginning(t_token *args);

//exiting
void		free_list(t_token *args);
void		free_array(char **array);
void		free_pids(t_data *data);
void		free_data(t_data *data);
void		free_all1(t_token *args, t_data *data);
void		unlink_here_doc(const char *filename);
void		prep_next_input(t_token *args, t_data *data);
void		free_quote_flag(t_data *data);
void		free_middle_list(t_token *args);
void		ft_perror_arg(char *str1, char *str);
void		ft_perror(char *str);
void		ft_perror_arg_middle(char *str1, char *str2, char *str3);
void		free_child(t_data *data, t_token *arg);
void		free_child_s(t_data *data, t_token *arg);

//debugging
void		ft_print_array(char **array);
void		test_env(char **env, t_data *data);
void		print_args(t_token *args);

#endif
