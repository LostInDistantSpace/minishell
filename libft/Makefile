# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 18:13:50 by bmouhib           #+#    #+#              #
#    Updated: 2024/10/30 17:01:25 by bmouhib          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                  VARIABLES                                   #
# ---------------------------------------------------------------------------- #

NAME			:=	libft.a

# --------------------------------- PATHNAMES -------------------------------- #

SRC_LIBC		:=	libc/
SRC_BONUS		:=	bonus/
SRC_FT_PRINTF	:=	ft_printf/
SRC_GNL			:=	gnl/
SRC_ADD			:=	add/

# ----------------------------------- LIBC ----------------------------------- #

SRC				:=	$(SRC_LIBC)ft_atoi.c
SRC				+=	$(SRC_LIBC)ft_bzero.c
SRC				+=	$(SRC_LIBC)ft_calloc.c
SRC				+=	$(SRC_LIBC)ft_isalnum.c
SRC				+=	$(SRC_LIBC)ft_isalpha.c
SRC				+=	$(SRC_LIBC)ft_isascii.c
SRC				+=	$(SRC_LIBC)ft_isdigit.c
SRC				+=	$(SRC_LIBC)ft_isprint.c
SRC				+=	$(SRC_LIBC)ft_itoa.c
SRC				+=	$(SRC_LIBC)ft_memchr.c
SRC				+=	$(SRC_LIBC)ft_memcmp.c
SRC				+=	$(SRC_LIBC)ft_memcpy.c
SRC				+=	$(SRC_LIBC)ft_memmove.c
SRC				+=	$(SRC_LIBC)ft_memset.c
SRC				+=	$(SRC_LIBC)ft_putchar_fd.c
SRC				+=	$(SRC_LIBC)ft_putendl_fd.c
SRC				+=	$(SRC_LIBC)ft_putnbr_fd.c
SRC				+=	$(SRC_LIBC)ft_putstr_fd.c
SRC				+=	$(SRC_LIBC)ft_split.c
SRC				+=	$(SRC_LIBC)ft_strchr.c
SRC				+=	$(SRC_LIBC)ft_strdup.c
SRC				+=	$(SRC_LIBC)ft_striteri.c
SRC				+=	$(SRC_LIBC)ft_strjoin.c
SRC				+=	$(SRC_LIBC)ft_strlcat.c
SRC				+=	$(SRC_LIBC)ft_strlcpy.c
SRC				+=	$(SRC_LIBC)ft_strlen.c
SRC				+=	$(SRC_LIBC)ft_strmapi.c
SRC				+=	$(SRC_LIBC)ft_strncmp.c
SRC				+=	$(SRC_LIBC)ft_strnstr.c
SRC				+=	$(SRC_LIBC)ft_strrchr.c
SRC				+=	$(SRC_LIBC)ft_strtrim.c
SRC				+=	$(SRC_LIBC)ft_substr.c
SRC				+=	$(SRC_LIBC)ft_tolower.c
SRC				+=	$(SRC_LIBC)ft_toupper.c

# ------------------------------ BONUS FUNCTIONS ----------------------------- #

SRC				+=	$(SRC_BONUS)ft_lstadd_back.c
SRC				+=	$(SRC_BONUS)ft_lstadd_front.c
SRC				+=	$(SRC_BONUS)ft_lstclear.c
SRC				+=	$(SRC_BONUS)ft_lstdelone.c
SRC				+=	$(SRC_BONUS)ft_lstiter.c
SRC				+=	$(SRC_BONUS)ft_lstmap.c
SRC				+=	$(SRC_BONUS)ft_lstnew.c
SRC				+=	$(SRC_BONUS)ft_lstsize.c
SRC				+=	$(SRC_BONUS)ft_lstlast.c

# --------------------------------- FT_PRINTF -------------------------------- #

SRC				+=	$(SRC_FT_PRINTF)ft_printf.c
SRC				+=	$(SRC_FT_PRINTF)ft_flags.c
SRC				+=	$(SRC_FT_PRINTF)ft_flag_digits.c
SRC				+=	$(SRC_FT_PRINTF)ft_print.c
SRC				+=	$(SRC_FT_PRINTF)ft_print_char.c
SRC				+=	$(SRC_FT_PRINTF)ft_print_s.c
SRC				+=	$(SRC_FT_PRINTF)ft_print_u.c
SRC				+=	$(SRC_FT_PRINTF)ft_print_nb.c
SRC				+=	$(SRC_FT_PRINTF)ft_print_hex.c
SRC				+=	$(SRC_FT_PRINTF)ft_print_padding.c
SRC				+=	$(SRC_FT_PRINTF)ft_nbtoa.c
SRC				+=	$(SRC_FT_PRINTF)ft_putnbr.c

# ------------------------------------ GNL ----------------------------------- #

SRC				+=	$(SRC_ADD)ft_isnumber.c
SRC				+=	$(SRC_ADD)ft_hasprefix.c
SRC				+=	$(SRC_ADD)ft_atoi_base.c
SRC				+=	$(SRC_ADD)ft_isdigit_base.c
SRC				+=	$(SRC_ADD)ft_iswhitespace.c

# ------------------------------------ ADD ----------------------------------- #

SRC				+=	$(SRC_GNL)get_next_line.c
SRC				+=	$(SRC_GNL)get_next_line_utils.c

# --------------------------------- COMMANDS --------------------------------- #

CC				:= gcc
RM				:= rm -rf
AR				:= ar -rc
MKDIR			:=	mkdir -p

# ----------------------------------- FLAGS ---------------------------------- #

CFLAGS			:=	-Wall
CFLAGS			+=	-Wextra
CFLAGS			+=	-Werror
CFLAGS			+=	-MMD
CFLAGS			+=	-MP

CFLAGS			+=	-g3

MAKE_NO_PRINT	:=	--no-print-directory
MAKE_FLAGS		:=	$(MAKE_NO_PRINT)
MAKE_FLAGS		+=	-C

# ----------------------------------- FILES ---------------------------------- #

INCLUDES		:=	includes/

SRCS_DIR		:=	srcs/
SRCS			:=	$(addprefix $(SRCS_DIR), $(SRC))

OBJS_DIR		:=	objs/
OBJS			:=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))

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
TO_UPPER		:=	tr '[:lower:]' '[:upper:]'
TRUNC_A			:=	tr -d '.a'
PROJECT			:=	$(shell $(ECHO) $(NAME) | $(TRUNC_A) | $(TO_UPPER))
OBJ_FILES		:=	$(BLUE)object files$(NO_STYLE)
DEPS_FILES		:=	$(BLUE)dependencies files$(NO_STYLE)
AND				:=	and
COMPLETE		:=	complete
BONUS_FILES		:=	bonus object files
TO_UPPER		:=	tr '[:lower:]' '[:upper:]'
TRUNC_A			:=	tr -d '.a'
PROJECT			:=	$(shell $(ECHO) $(NAME) | $(TRUNC_A) | $(TO_UPPER))
PROJECT_NAME	:=	$(WHITE)$(PROJECT)$(NO_STYLE)
NAME_FILE		:=	$(BLUE)$(NAME)$(NO_STYLE)
NORM_MSG		:=	$(GREEN)Norminette on $(PROJECT_NAME)$(GREEN): OK!$(NO_STYLE)

COMP_OBJS		:=	$(ECHO) $(CREATION) $(PROJECT_NAME) $(OBJ_FILES) $(AND) $(DEPS_FILES) $(COMPLETE)
COMP_NAME		:=	$(ECHO) $(CREATION) $(PROJECT_NAME) $(NAME_FILE) $(COMPLETE)
OK_NORM			:=	$(ECHO) $(NORM_MSG)
COMP_CLEAN		:=	$(ECHO) $(DELETION) $(PROJECT_NAME) $(OBJ_FILES) $(AND) $(DEPS_FILES) $(COMPLETE)
COMP_FCLEAN		:=	$(ECHO) $(DELETION) $(PROJECT_NAME) $(NAME_FILE) $(COMPLETE)

define HELP_MSG
Usage: make [TARGET]
		all         - Create the archive file(s)
		clean       - Remove object file(s)
		fclean      - Remove object file(s) and archive file(s)
		re          - Recreate the archive file(s)
		bonus       - Build the bonus part of the program
		norm        - Run norminette checks
		debug       - Activate debug flags
		help        - Display this help message
endef
export HELP_MSG

HELP			:=	@$(ECHO) "$$HELP_MSG"

# -------------------------------- NORMINETTE -------------------------------- #

NORMINETTE		:=	norminette
NORMSH			:=	$(NORMINETTE) -R CheckForbiddenSourceHeader $(SRCS)
NORMD			:=	$(NORMINETTE) -R CheckDefine $(INCLUDES)

# ---------------------------------------------------------------------------- #
#                                    RULES                                     #
# ---------------------------------------------------------------------------- #


$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c
					@$(MKDIR) $(dir $@)
					@$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

all:				$(NAME)

$(NAME):			$(OBJS)
					@$(COMP_OBJS)
					@$(AR) $(NAME) $(OBJS)
					@$(COMP_NAME)

clean:
					@$(RM) $(OBJS_DIR)
					@$(COMP_CLEAN)

fclean:				clean
					@$(RM) $(NAME)
					@$(COMP_FCLEAN)

re:					fclean all

bonus:				all

norm:
					@$(NORMSH)
					@$(NORMD)
					@$(OK_NORM)

debug:
					@$(MAKE) $(MAKE_NO_PRINT) CFLAGS+="$(DEBUG_CFLAGS)" re

help:
					$(HELP)

-include $(DEPS)

.PHONY:				all clean fclean re bonus norm