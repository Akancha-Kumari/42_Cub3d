NAME	:= cub3d

CC      := cc
CFLAGS	:= -Wall -Wextra -Werror

LIBMLX	:= ./MLX42
MLX_REPO := https://github.com/codam-coding-college/MLX42.git

HEADERS	:= -I ./include -I $(LIBMLX)/include -I/opt/homebrew/opt/glfw/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -L/opt/homebrew/opt/glfw/lib -lglfw -ldl -pthread -lm

SRCS	:= ./src/cube.c
OBJDIR	:= obj

OBJS	:= $(patsubst ./src/%.c,$(OBJDIR)/%.o,$(SRCS))

all: libmlx $(NAME)
	@echo "Build finished!"

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "Cloning MLX42..."; \
		git clone $(MLX_REPO) $(LIBMLX); \
	fi
	@if [ ! -f "$(LIBMLX)/build/libmlx42.a" ]; then \
		cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; \
	fi

$(OBJDIR)/%.o: ./src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)

re: fclean all

.PHONY: all clean fclean re libmlx

# NAME = cub3d
# CC = cc
# CFLAGS = -Wall -Wextra -Werror

# SRC = src/main.c
# OBJ = $(SRC:.c=.o)

# MLX_DIR = includes/minilibx-linux
# MLX_LIB = $(MLX_DIR)/libmlx.a
# INCLUDES = -Iincludes -I$(MLX_DIR)
# LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# all: $(NAME)
# 	@echo "Build complete."

# $(MLX_LIB):
# 	@$(MAKE) -C $(MLX_DIR)

# $(NAME): $(MLX_LIB) $(OBJ)
# 	@$(CC) $(OBJ) -o $(NAME) $(MLX_LIB) $(LFLAGS)

# %.o: %.c
# 	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"

# clean:
# 	@rm -rf $(OBJ)

# fclean: clean
# 	@rm -rf $(NAME)

# re: fclean all

# .PHONY: all clean fclean re
