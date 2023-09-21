# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 14:11:40 by npaolett          #+#    #+#              #
#    Updated: 2023/09/14 16:26:15 by npaolett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS = pipex_bonus
CC = cc

RM = rm -fr

CFLAGS = -g3 -Wall -Wextra -Werror 

INCL = -I -I./libft 

SRC =	src/main.c        \
		src/pipex_utils.c \
		src/stack_init.c  \
		src/err.c 		  \

SRC_BONUS = src/main_bonus.c \
			src/pipex_utils.c \
			src/stack_init.c \
			src/here_doc_bonus.c \
			src/err.c		\

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
#	cc -o $(NAME) $(OBJ)

LIBFT = ./libft/libft.a


$(NAME): $(OBJ)
	make lib
	cc -o $(NAME) $(OBJ) $(LIBFT) 

$(BONUS): $(OBJ_BONUS)
	make lib
	cc -o $(BONUS) $(OBJ_BONUS) $(LIBFT) 

all : $(NAME)

bonus : $(BONUS)

%.o: %.c
	cc $(INCL) $(CFLAGS) -o $@ -c $<


lib:
	make -C ./libft/ all
	
clean:
	@make -C libft/ clean
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(LIBFT)  $(BONUS)

re: fclean 
	make all

rebonus: fclean
		make bonus 

.PHONY: all clean fclean re