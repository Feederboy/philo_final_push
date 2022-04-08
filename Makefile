# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matt <maquentr@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 14:46:13 by matt              #+#    #+#              #
#    Updated: 2022/04/09 00:23:12 by maquentr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

CC=gcc

OBJDIR = obj

CFLAGS=-Wall -Wextra -Werror -g3# -fsanitize=thread

PATHS= $(OBJDIR)/srcs

SRC=main.c \
	utils3.c \
	utils2.c \
	utils1.c \
	utils3.c \
	timers.c \
	routine.c \
	protect.c \
	init.c \
	forks.c


RM=rm -rf

OBJ=$(SRC:%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread -D_REENTRANT

$(OBJDIR) :
	mkdir $(OBJDIR) $(PATHS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(OBJDIR)

re: fclean all

.PHONY: clean fclean
