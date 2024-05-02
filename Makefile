# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 14:24:04 by bschmidt          #+#    #+#              #
#    Updated: 2024/04/25 16:30:24 by bschmidt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors for printing
GREEN = \033[0;32m
NC = \033[0m # No Color

# NAME
NAME = minishell

# SOURCES
SOURCES = main.c \
			execution/execute.c \
			execution/exec_commands.c \
			execution/exec_here_doc.c \
			execution/exec_argument.c \
			execution/prepare_execution.c \
			execution/handle_parts.c \
			execution/handle_beginning.c \
			execution/handle_middle.c \
			execution/handle_end.c \
			execution/handle_solo.c \
			execution/execute_pipes.c \
			execution/solo_part.c \
			exec_built_ins/exec_built_ins.c \
			exec_built_ins/exec_echo.c \
			exec_built_ins/exec_cd.c \
			exec_built_ins/exec_pwd.c \
			exec_built_ins/exec_export.c \
			exec_built_ins/exec_env.c \
			exec_built_ins/exec_unset.c \
			exec_built_ins/exec_exit.c \
			utils/helpers.c \
			utils/helpers2.c \
			utils/helpers3.c \
			utils/check_infile.c \
			utils/in_redir_helper.c \
			utils/out_redir_helper.c \
			utils/execute_helpers.c \
			utils/list_helper.c \
			utils/debugging.c \
			exiting/freeing.c \
			exiting/freeing2.c \
			parsing/parsing.c \
			parsing/parsing2.c \
			parsing/split_in_words.c \
			parsing/split_in_words2.c \
			parsing/tokenize_words.c \
			parsing/tokenize_words2.c \
			parsing/quote_bullshit.c \
			parsing/quote_bullshit2.c \
			parsing/expand.c \
			parsing/expand2.c \
			parsing/expand3.c \
			parsing/add_spaces.c \
			parsing/add_spaces2.c \
			parsing/sig_handler.c \
			parsing/helper_parsing.c \
			parsing/handle_syntax_errors.c \
			parsing/handle_syntax_errors2.c \

# DIRECTORIES AND PATHS
INCLDIR		:= incl/
SRCDIR		:= src/
OBJDIR		:= obj/
LIBFTDIR	:= libft/
HEADER		:= incl/minishell.h

# LIBRARIES
LIBFT		:= $(LIBFTDIR)libft.a

# COMPILER, COMMANDS & FLAGS
CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -g -I$(INCLDIR)
RM 			:= rm -fr
LIBFLAG		:= -L$(LIBFTDIR)
LIBFTLIB	:= -lft

# HEADERS
HEADERS		:= $(addprefix $(INCLDIR)/, minishell.h libft.h get_next_line.h ft_printf.h)

# CREATE OBJECTS
OBJ = $(SOURCES:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

# COMPILATION RULES
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# RULES
all: $(NAME) $(LIBFT)

# COMPILE LIBFT.A
$(LIBFT): $(LIBFTDIR)*.c
	@$(MAKE) -C $(LIBFTDIR) all --no-print-directory
	@echo "$(GREEN)libft.a is ready!$(NC)"

# COMPILE minishell
$(NAME): $(LIBFT) $(OBJDIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCS) -o $(NAME) $(LIBFLAG) $(LIBFTLIB) -lreadline
	@echo "$(GREEN)$(NAME) is ready!$(NC)"

#DEFINE OBJDIR
$(OBJDIR):
	mkdir -p $(OBJDIR)exec_built_ins $(OBJDIR)utils $(OBJDIR)execution $(OBJDIR)parsing $(OBJDIR)exiting

#COMPILING
$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJDIR)exec_built_ins/%.o: $(SRCDIR)exec_built_ins/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# CREATING HEADER-LINKS IN INCL FOLDER
$(HEADERS):
	ln $(LIBFTDIR)libft.h $(INCLDIR)libft.h
	ln $(LIBFTDIR)ft_printf.h $(INCLDIR)ft_printf.h
	ln $(LIBFTDIR)get_next_line_bonus.h $(INCLDIR)get_next_line_bonus.h

# CLEANING
clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(INCLDIR)libft.h
	$(RM) $(INCLDIR)ft_printf.h
	$(RM) $(INCLDIR)get_next_line_bonus.h

#val: $(NAME)
#	valgrind --suppressions=suppressions.supp --leak-check=full --track-origins=yes --show-leak-kinds=all ./minishell

re: fclean all

.PHONY: all clean fclean re
