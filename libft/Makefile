# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 13:53:15 by bschmidt          #+#    #+#              #
#    Updated: 2024/03/05 02:58:32 by bschmidt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES = ft_memset \
		ft_bzero \
		ft_memcpy \
		ft_memmove \
		ft_strlen \
		ft_toupper \
		ft_tolower \
		ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_strlcpy \
		ft_strncpy \
		ft_strlcat \
		ft_strcat \
		ft_strchr \
		ft_strrchr \
		ft_strncmp \
		ft_memchr \
		ft_memcmp \
		ft_strnstr \
		ft_atoi \
		ft_atoli \
		ft_calloc \
		ft_strdup \
		ft_strcmp \
		ft_substr \
		ft_strjoin \
		ft_strtrim \
		ft_split \
		ft_itoa \
		ft_strmapi \
		ft_striteri \
		ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_print_char \
		ft_printf \
		ft_print_int \
		ft_print_lowerhexa \
		ft_print_pointer \
		ft_print_string \
		ft_print_ui \
		ft_print_upperhexa \
		ft_putchar_fd \
		ft_lstnew \
		ft_lstadd_front \
		ft_lstsize \
		ft_lstlast \
		ft_lstadd_back \
		ft_lstdelone \
		ft_lstclear \
		ft_lstiter \
		ft_lstmap \
		get_next_line_bonus \
		get_next_line_utils_bonus \
		free_array \
		ft_charsinstr \
		ft_extend_array \
		ft_onlydigits \

CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADER = libft.h ft_printf.h get_next_line_bonus.h
AR = ar rcs
RM = rm -f

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS) $(HEADER)
	$(AR) $(NAME) $(OBJS)
	
all: $(NAME)

clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
