# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mhaan <mhaan@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/02 15:18:58 by mhaan         #+#    #+#                  #
#    Updated: 2023/08/18 14:43:54 by mhaan         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#GENERAL VARIABLES:
NAME	:= libft_ext.a
RM		:= /bin/rm -rf

#COMPILATION VARIABLES:
AR		:= ar -crs
CFLAGS	?= -Wall -Wextra -Werror

ifdef OPTIM
	CFLAGS += -Ofast -flto -march=native
endif

# Include files and directories:
INC_DIRS := ./includes
INCLUDES := $(foreach D,$(INC_DIRS),-I$(D))
INC_FILES := includes/libft.h includes/ft_printf.h includes/get_next_line_bonus.h

# Source files and directories:
LIBFT_DIR := 		./libft
LIBFT_SRC_DIR :=	$(LIBFT_DIR)
LIBFT_SRC :=		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
					ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
					ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
					ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
					ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
					ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
					ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
					ft_abs.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
					ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
					ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

PRINTF_DIR :=		./ft_printf
PRINTF_SRC_DIR :=	$(PRINTF_DIR)/src
PRINTF_SRC :=		ft_printf.c helpers.c

GNL_DIR			:=	./get_next_line
GNL_SRC_DIR		:=	$(GNL_DIR)
GNL_SRC			:=	get_next_line_bonus.c get_next_line_utils_bonus.c

SRC				:=	$(addprefix $(LIBFT_SRC_DIR)/, $(LIBFT_SRC)) \
					$(addprefix $(PRINTF_SRC_DIR)/, $(PRINTF_SRC)) \
					$(addprefix $(GNL_SRC_DIR)/, $(GNL_SRC))

# Object files and directories:
OBJ_DIR			:=	./obj
LIBFT_OBJS		:=	$(addprefix $(OBJ_DIR)/,$(notdir $(LIBFT_SRC:.c=.o)))
PRINTF_OBJS 	:=	$(addprefix $(OBJ_DIR)/,$(notdir $(PRINTF_SRC:.c=.o)))
GNL_OBJS		:=	$(addprefix $(OBJ_DIR)/,$(notdir $(GNL_SRC:.c=.o)))
OBJ				:=	$(LIBFT_OBJS) $(PRINTF_OBJS) $(GNL_OBJS)

# Archive files and directories:
LIBFT_AR		:=	$(LIBFT_DIR)/libft.a

#RECIPES:
all:	$(NAME)

optim:
	@$(MAKE) OPTIM=1 WITH_BONUS=1 all

reoptim:
	@$(MAKE) fclean
	$(MAKE) optim

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT_AR)

re:
	@$(MAKE) fclean
	@$(MAKE) all

#RULES:
$(NAME) : $(LIBFT_OBJS) $(PRINTF_OBJS) $(GNL_OBJS)
	@$(AR) $(NAME) $^

$(LIBFT_AR): $(NAME)
	@$(MAKE) bonus -j -C libft
	mv $(LIBFT_AR) ./$(NAME)

$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c $(INC_FILES)
	@mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)/%.o: $(PRINTF_SRC_DIR)/%.c $(INC_FILES)
	@mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<


$(OBJ_DIR)/%.o: $(GNL_SRC_DIR)/%.c $(INC_FILES)
	@mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c -D BUFFER_SIZE=10000 -o $@ $<

#OTHER:
.PHONY:
	all clean fclean re
