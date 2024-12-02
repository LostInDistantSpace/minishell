# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 16:41:52 by bmouhib           #+#    #+#              #
#    Updated: 2024/11/11 18:26:10 by bmouhib          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                  VARIABLES                                   #
# ---------------------------------------------------------------------------- #

NAME		:=	fdf

# --------------------------------- SOURCES ---------------------------------- #

SRC				:=	fdf.c
SRC				+=	mlx_helpers.c
SRC				+=	mouse_hook.c
SRC				+=	mini_maths.c
SRC				+=	map_utils.c
SRC				+=	map_init.c
SRC				+=	parsing.c
SRC				+=	points.c
SRC				+=	hooks.c
SRC				+=	error.c
SRC				+=	color.c
SRC				+=	frees.c
SRC				+=	draw.c
SRC				+=	init.c

# --------------------------------- COMMANDS --------------------------------- #

CC				:=	gcc
RM				:=	rm -rf
AR				:=	ar -rc
MKDIR			:=	mkdir -p

# ----------------------------------- FILES ---------------------------------- #

INCLUDES		:=	includes/
INCLUDE_FILE	:=	fdf.h

LIBFT_DIR		:=	libft/
LIBFT_NAME		:=	libft.a
LIBFT_INCLUDES	:=	$(LIBFT_DIR)$(INCLUDES)
LIBFT			:=	$(LIBFT_DIR)$(LIBFT_NAME)

MLX_DIR			:=	minilibx-linux/
MLX_NAME		:=	libmlx_Linux.a
MLX				:=	$(MLX_DIR)$(MLX_NAME)
MLX_FILE		:=	libmlx.a
MLX_FLAG		:=	-lX11 -lXext
MLX_LIB			:=	$(addprefix $(MLX_DIR), $(MLX_FILE))
MLX_CLONE		:=	https://github.com/42Paris/minilibx-linux.git

INCLUDES_FLAGS	:=	-I $(INCLUDES)
INCLUDES_FLAGS	+=	 -I $(LIBFT_INCLUDES)
INCLUDES_FLAGS	+=	 -I $(MLX_DIR)

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

LIB_FLAGS		:=	-L$(LIBFT_DIR)
LIB_FLAGS		+=	-lft
LIB_FLAGS		+=	-L$(MLX_DIR)
LIB_FLAGS		+=	-lm
LIB_FLAGS		+=	-lmlx_Linux
LIB_FLAGS		+=	-L/usr/lib -Imlx_linux -lXext -lX11

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
MLX_FILES		:=	$(BLUE)mlx$(NO_STYLE)
DEPS_FILES		:=	$(BLUE)dependencies files$(NO_STYLE)
AND				:=	and
COMPLETE		:=	complete
TO_UPPER		:=	tr '[:lower:]' '[:upper:]'
PROJECT			:=	$(shell $(ECHO) $(NAME) | $(TO_UPPER))
PROJECT_NAME	:=	$(WHITE)$(PROJECT)$(NO_STYLE)
NAME_FILE		:=	$(BLUE)$(NAME)$(NO_STYLE)

COMP_OBJS		:=	$(ECHO) $(CREATION) $(PROJECT_NAME) $(OBJ_FILES) $(AND) $(DEPS_FILES) $(COMPLETE)
COMP_MLX		:=	$(ECHO) $(CREATION) $(PROJECT_NAME) $(MLX_FILES) $(COMPLETE)
COMP_NAME		:=	$(ECHO) $(CREATION) $(PROJECT_NAME) $(NAME_FILE) $(COMPLETE)
COMP_CLEAN		:=	$(ECHO) $(DELETION) $(PROJECT_NAME) $(OBJ_FILES) $(AND) $(DEPS_FILES) $(COMPLETE)
COMP_FCLEAN		:=	$(ECHO) $(DELETION) $(PROJECT_NAME) $(NAME_FILE) $(COMPLETE)

define HELP_MSG
Usage: make [TARGET]
		all         - Create the archive file(s)
		clean       - Remove object file(s)
		fclean      - Remove object file(s) and archive file(s)
		re          - Recreate the archive file(s)
		help        - Display this help message
endef
export HELP_MSG

HELP			:=	@$(ECHO) "$$HELP_MSG"

# ---------------------------------------------------------------------------- #
#                                    RULES                                     #
# ---------------------------------------------------------------------------- #

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c $(INCLUDES)$(INCLUDE_FILE)
					@$(MKDIR) $(dir $@)
					@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES_FLAGS)

all:				$(NAME)

$(LIBFT):
					@$(MAKE) $(MAKE_FLAGS) $(LIBFT_DIR)

$(NAME): 			$(LIBFT) $(MLX_LIB) $(OBJS)
					@$(COMP_OBJS)
					@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB_FLAGS)
					@$(COMP_NAME)

$(MLX_LIB):
					@if [ ! -d "$(MLX_DIR)" ]; then \
						git clone -q $(MLX_CLONE); \
						echo "\033[1;32m$(MLX_DIR) created"; \
					else \
						echo "\033[1;32mRepository already exists."; \
					fi
					@make -sC $(MLX_DIR)
					

clean_project:
					@$(RM) $(OBJS_DIR)
					@$(RM) $(MLX_DIR)
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

