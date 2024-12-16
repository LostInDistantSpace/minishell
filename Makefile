# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 16:41:52 by bmouhib           #+#    #+#              #
#    Updated: 2024/12/16 22:46:14 by bmouhib          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                  VARIABLES                                   #
# ---------------------------------------------------------------------------- #

NAME		:=	minishell

# --------------------------------- SOURCES ---------------------------------- #

SRC			:=	minishell.c
SRC			+=	env.c
SRC			+=	init.c
SRC			+=	cleaner.c
SRC			+=	parsing.c
SRC			+=	prompt.c
SRC			+=	str_utils.c
SRC			+=	syntax_utils.c
SRC			+=	syntax.c
SRC			+=	token_utils.c
SRC			+=	tokenization.c

# --------------------------------- COMMANDS --------------------------------- #

CC				:=	cc
RM				:=	rm -rf
AR				:=	ar -rc
MKDIR			:=	mkdir -p

# ----------------------------------- FILES ---------------------------------- #

INCLUDES		:=	includes/
INCLUDE_FILES	:=	colors.h
INCLUDE_FILES	+=	minishell.h

LIBFT_DIR		:=	libft/
LIBFT_NAME		:=	libft.a
LIBFT_INCLUDES	:=	$(LIBFT_DIR)$(INCLUDES)
LIBFT			:=	$(LIBFT_DIR)$(LIBFT_NAME)


INCLUDES_FLAGS	:=	-I $(INCLUDES)
INCLUDES_FLAGS	+=	-I $(LIBFT_INCLUDES)

SRCS_DIR		:=	srcs/
SRCS			:=	$(addprefix $(SRCS_DIR), $(SRC))

OBJS_DIR		:=	objs/
OBJS			:=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))

DEPS			:=	$(OBJS:.o=.d)

# ----------------------------------- FLAGS ---------------------------------- #

CFLAGS			:=	-Wall
CFLAGS			+=	-Wextra
CFLAGS			+=	-Werror
CFLAGS			+=	-g3

LIBFT_FLAGS		:=	-L$(LIBFT_DIR)
LIBFT_FLAGS		+=	-lft

MAKE_NO_PRINT	:=	--no-print-directory
MAKE_FLAGS		:=	$(MAKE_NO_PRINT)
MAKE_FLAGS		+=	-C

# ---------------------------------------------------------------------------- #
#                                   VISUALS                                    #
# ---------------------------------------------------------------------------- #

# ---------------------------------- STYLES ---------------------------------- #

RED				:=	"\033[0;31m\033[1m"
GREEN			:=	"\033[0;32m\033[1m"
BLUE			:=	"\033[0;34m\033[1m"
PURPLE			:=	"\033[0;35m\033[1m"
YELLOW			:=	"\033[1;33m\033[1m"
WHITE			:=	"\033[0;37m\033[1m"
NO_STYLE		:=	"\033[0m"

# ----------------------------------- ECHO ----------------------------------- #

ECHO			:=	echo

DELETION		:=	$(RED)Deletion$(NO_STYLE) of
CREATION		:=	$(GREEN)Creation$(NO_STYLE) of
OBJ_FILES		:=	$(BLUE)object files$(NO_STYLE)
DEPS_FILES		:=	$(BLUE)dependencies files$(NO_STYLE)
AND				:=	and
COMPLETE		:=	complete
NAME_FILE		:=	$(BLUE)$(NAME)$(NO_STYLE)

COMP_OBJS		:=	$(ECHO) $(CREATION) $(OBJ_FILES) $(AND) $(DEPS_FILES) $(COMPLETE)
COMP_MLX		:=	$(ECHO) $(CREATION) $(MLX_FILES) $(COMPLETE)
COMP_NAME		:=	$(ECHO) $(CREATION) $(NAME_FILE) $(COMPLETE)
COMP_CLEAN		:=	$(ECHO) $(DELETION) $(OBJ_FILES) $(AND) $(DEPS_FILES) $(COMPLETE)
COMP_FCLEAN		:=	$(ECHO) $(DELETION) $(NAME_FILE) $(COMPLETE)

# ---------------------------------------------------------------------------- #
#                                    RULES                                     #
# ---------------------------------------------------------------------------- #

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c
					@$(MKDIR) $(dir $@)
					@$(CC) $(CFLAGS) $(INCLUDES_FLAGS) -c $< -o $@

all:				$(NAME)

$(LIBFT):
					@$(MAKE) $(MAKE_FLAGS) $(LIBFT_DIR)

$(NAME): 			$(OBJS) $(LIBFT) 
					@$(COMP_OBJS)
					@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline $(LIBFT_FLAGS)
					@$(COMP_NAME)


clean_project:
					@$(RM) $(OBJS_DIR)
					@$(COMP_CLEAN)

clean:				clean_project
					@$(MAKE) $(MAKE_FLAGS) $(LIBFT_DIR) clean

fclean:				clean_project
					@$(MAKE) $(MAKE_FLAGS) $(LIBFT_DIR) fclean
					@$(RM) $(NAME)
					@$(COMP_FCLEAN)

re:					fclean all

help:
					$(HELP)

-include			$(DEPS)

.PHONY:				all clean fclean re norm

