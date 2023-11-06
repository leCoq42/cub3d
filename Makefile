#GENERAL VARIABLES
NAME := cub3D
RM := /bin/rm -rf

#COMPILATION VARIABLES
CFLAGS ?= -Wall -Wextra -Werror

ifdef OPTIM
	CFLAGS += -Ofast -march=native -flto
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

MAIN		:=	src/main.c
SRC_DIR		:=	src
SRC			:=	main.c \
				parsing/parse.c \
				parsing/parse_header.c \
				parsing/parsing_utils.c \
				parsing/color.c \
				parsing/texture.c \
				parsing/parse_map.c \
				parsing/get_map_info.c \
<<<<<<< HEAD
				drawing/raycasting.c \
=======
				parsing/floodfill.c \
				drawing/test.c \
>>>>>>> 4f68921c3285d1725283177ea200a3f39e4f1970
				drawing/move.c \
				drawing/init.c \
				drawing/draw.c \
				drawing/color.c \
				drawing/time.c \
<<<<<<< HEAD
				drawing/textures.c
=======
				drawing/mouse.c \
				error_handling/clean.c \
>>>>>>> 4f68921c3285d1725283177ea200a3f39e4f1970

OBJ_DIR		:=	./obj
MAIN_OBJ	:=	$(MAIN:src/%.c=$(OBJ_DIR)/%.o)

SRC     	:=	$(SRC:%=$(SRC_DIR)/%)
# ODIR		:=	$(sort $(dir $(SRC:%=$(OBJ_DIR)/%)))
ODIR 		:= $(sort $(subst src,./,$(dir $(SRC:%=$(OBJ_DIR)/%))))

OBJS		:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#RECIPES:
all: $(ODIR) $(NAME)

optim:
	@$(MAKE) OPTIM=1 all

reoptim: clean optim

debug:
	$(MAKE) DEBUG=1

rebug: clean
	@rm -rf $(LIBMLX)/build/
	cmake -DDEBUG=1 -DGLFW_FETCH=0 $(LIBMLX) -B $(LIBMLX)/build && cmake --build $(LIBMLX)/build -j
	$(MAKE) DEBUG=1

fsan:
	$(MAKE) FSAN=1

resan: clean fsan

libs:
	git submodule update --remote --init --recursive
	@cmake $(LIBMLX) -B $(LIBMLX)/build && cmake --build $(LIBMLX)/build -j
	@$(MAKE) -j -C $(LIBFT)

oplibs:
	git submodule update --remote --init --recursive
	@cmake $(LIBMLX) -B $(LIBMLX)/build && cmake --build $(LIBMLX)/build -j
	@$(MAKE) -j -C $(LIBFT) optim

relibs:
	git submodule update --remote --init --recursive
	@$(MAKE) fclean -C $(LIBFT)
	@rm -rf $(LIBMLX)/build/
	@cmake $(LIBMLX) -B $(LIBMLX)/build && cmake --build $(LIBMLX)/build -j
	@$(MAKE) -j -C $(LIBFT)

reoplibs:
	git submodule update --remote --init --recursive
	@$(MAKE) fclean -C $(LIBFT)
	@rm -rf $(LIBMLX)/build/
	@cmake $(LIBMLX) -B $(LIBMLX)/build && cmake --build $(LIBMLX)/build -j
	@$(MAKE) -j -C $(LIBFT) optim

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
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME)
# @$(CC) $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME) -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(NAME): $(OBJS) $(MAIN_OBJ)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME)
# @$(CC) $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME) -lm
#&& printf "Compiling: $(notdir $<)\n"

#OTHER:
.PHONY:	all, re, optim, reoptim, debug, rebug, fsan, resan, libs, oplibs, relibs, reoplibs, clean, fclean
