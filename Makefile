NAME    := cub3D

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g

# === Directories ===
LIBMLX  := ./MLX42
MLX_REPO := https://github.com/codam-coding-college/MLX42.git
OBJDIR  := obj

# === Headers ===
HEADERS := -I ./include -I ./src/arena -I ./get_next_line \
           -I $(LIBMLX)/include -I libft -I/opt/homebrew/opt/glfw/include

# === Libs ===
LIBS    := $(LIBMLX)/build/libmlx42.a libft/libft.a \
           -L/opt/homebrew/opt/glfw/lib -lglfw -ldl -pthread -lm

# === Sources ===
SRCS := src/arena/arena.c src/error.c src/main.c\
        get_next_line/get_next_line.c \
        src/parse/parse_map.c src/parse/parse_read.c src/parse/parse_texture.c src/parse/parse_util.c \
        src/graphics/init.c src/graphics/key.c src/graphics/render.c

OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

# === Build rules ===
all: libmlx libft $(NAME)
	@echo "Build finished!"

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<)\n"

# === External libs ===
libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "Cloning MLX42..."; \
		git clone $(MLX_REPO) $(LIBMLX); \
	fi
	@if [ ! -f "$(LIBMLX)/build/libmlx42.a" ]; then \
		cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; \
	fi

libft/libft.a:
	@$(MAKE) -C libft

# === Cleaning ===
clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft
