# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 16:41:52 by bmouhib           #+#    #+#              #
#    Updated: 2025/01/23 22:58:01 by bmouhib          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                  VARIABLES                                   #
# ---------------------------------------------------------------------------- #

NAME		:=	minishell
PARS_PATH	:=	parsing/
EXEC_PATH	:=	exec/

# --------------------------------- SOURCES ---------------------------------- #

SRC			:=	minishell.c
SRC			+=	$(PARS_PATH)ast.c
SRC			+=	$(PARS_PATH)cleaner_ptr.c
SRC			+=	$(PARS_PATH)cleaner_struct.c
SRC			+=	$(PARS_PATH)env.c
SRC			+=	$(PARS_PATH)expand_utils.c
SRC			+=	$(PARS_PATH)expand.c
SRC			+=	$(PARS_PATH)heredoc.c
SRC			+=	$(PARS_PATH)init.c
SRC			+=	$(PARS_PATH)parsing.c
SRC			+=	$(PARS_PATH)prompt.c
SRC			+=	$(PARS_PATH)signal.c
SRC			+=	$(PARS_PATH)str_utils.c
SRC			+=	$(PARS_PATH)substr_del.c
SRC			+=	$(PARS_PATH)syntax_errors.c
SRC			+=	$(PARS_PATH)syntax_utils.c
SRC			+=	$(PARS_PATH)syntax.c
SRC			+=	$(PARS_PATH)token_utils.c
SRC			+=	$(PARS_PATH)token_words.c
SRC			+=	$(PARS_PATH)tokenization.c
SRC			+=	TESTS.c
SRC			+=	$(EXEC_PATH)built_ins.c
SRC			+=	$(EXEC_PATH)built_in_utils.c
SRC			+=	$(EXEC_PATH)export.c
SRC			+=	$(EXEC_PATH)find_path.c
SRC			+=	$(EXEC_PATH)get_env.c
SRC			+=	$(EXEC_PATH)handle_commands.c
SRC			+=	$(EXEC_PATH)handle_in_out.c
SRC			+=	$(EXEC_PATH)pipe.c
SRC			+=	$(EXEC_PATH)unset.c
SRC			+=	$(EXEC_PATH)exec.c
SRC			+=	$(EXEC_PATH)free_exec.c
SRC			+=	$(EXEC_PATH)ft_atoui.c


# --------------------------------- COMMANDS --------------------------------- #

CC				:=	cc
RM				:=	rm -rf
AR				:=	ar -rc
MKDIR			:=	mkdir -p

# ----------------------------------- FILES ---------------------------------- #

INCLUDES		:=	includes/
INCLUDE_FILES	:=	colors.h
INCLUDE_FILES	+=	minishell.h
INCLUDE_FILES	+=	parsing.h
INCLUDE_FILES	+=	exec.h

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
