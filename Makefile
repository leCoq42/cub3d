#GENERAL VARIABLES
NAME := cub3D
RM := /bin/rm -rf

#COMPILATION VARIABLES
CFLAGS ?= -Wall -Wextra -Werror


ifdef OPTIM
	CFLAGS += -Ofast -march=native #-flto
endif

ifdef DEBUG
	CFLAGS += -g -Og
endif

ifdef FSAN
	CFLAGS += -Og -fsanitize=address,undefined
endif

AR := ar -crs

#DEPENDENCIES:
LIBMLX		:= ./libs/MLX42
LIBFT		:= ./libs/libft_ext
LIBS		:= $(LIBFT)/libft_ext.a $(LIBMLX)/build/libmlx42.a -lglfw -lm -ldl -pthread

#DIRS AND FILES
INCLUDES	:=	-I./include -I$(LIBMLX)/include/MLX42 -I$(LIBFT)/includes

SRC_DIR		:=	./src
OBJ_DIR		:=	./obj

SRC			:=	test.c bresenham.c move.c init.c wu_line.c

SRC     	:=	$(SRC:%=$(SRC_DIR)/%)
ODIR		:=	$(sort $(dir $(SRC:%=$(OBJ_DIR)/%)))

OBJS		:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# OBJS		:=	$(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))

#RECIPES:
all: $(ODIR) $(NAME)

optim:
	@$(MAKE) OPTIM=1 all

reoptim: clean optim

debug:
	$(MAKE) DEBUG=1

rebug: clean debug

fsan:
	$(MAKE) FSAN=1

resan: clean fsanitize

libs-update:
	@$(MAKE) fclean -C $(LIBFT)
	@rm -rf $(LIBMLX)/build/
	git submodule update --init --recursive
	@cmake $(LIBMLX) -B $(LIBMLX)/build && cmake --build $(LIBMLX)/build -j
	@make -j -C $(LIBFT) #OPTIM=1

libmlx:
	git submodule update --init --recursive
	@cmake $(LIBMLX) -B $(LIBMLX)/build && cmake --build $(LIBMLX)/build -j
# @cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j

libft:
	git submodule update --init --recursive
	@make -j -C $(LIBFT) #OPTIM=1

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT)

fclean: clean
	@$(RM) $(NAME)
	@rm -rf $(LIBMLX)/build/
	@$(MAKE) fclean -C $(LIBFT)

re: clean all

#RULES:
$(ODIR):
	mkdir -p $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME)
# @$(CC) $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME) -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)
#&& printf "Compiling: $(notdir $<)\n"

#OTHER:
.PHONY:	all, re, optim, reoptim, debug, rebug, fsan, resan, libs-update, libmlx, clean, fclean
