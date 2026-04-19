PROG = miniRt

# === LIBRARIES ===
LIBFT_DIR = ft_libft
LIBFT_REPO = https://github.com/ThiwankaS/ft_libft
LIBFT_A = $(LIBFT_DIR)/libft.a

MLX42_DIR = MLX42
MLX42_REPO = https://github.com/codam-coding-college/MLX42
MLX42_INCLUDE = -I$(MLX42_DIR)/include
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a
MLX42_BUILD_CMD = cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR) && cmake --build $(MLX42_DIR)/build

# === COMPILER & FLAGS ===
CMD = cc

# Debug and Release Flags
DEBUG_FLAGS = -Wall -Wextra -Werror -g -O0 -fsanitize=address,undefined
RELEASE_FLAGS = -Wall -Wextra -Werror -O3

# Default to RELEASE
CFLAGS = $(RELEASE_FLAGS) -I$(LIBFT_DIR) $(MLX42_INCLUDE) -std=c11
GLFW_A_DIR = $(MLX42_DIR)/build/_deps/glfw-build/src
# Static GLFW from MLX42 needs X11; with system libglfw use: -lglfw instead of -L$(GLFW_A_DIR) -lglfw3
LDFLAGS = -L$(MLX42_DIR)/build -L$(GLFW_A_DIR) -lmlx42 -lglfw3 \
	-lX11 -lXrandr -lXi -lXxf86vm -lXcursor -lXinerama -lXext -ldl -pthread -lm $(LIBFT_A)

# === SOURCES ===
SRCS = \
	srcs/tuples/tuple.c\
	srcs/matrices/matrix.c\
	srcs/graphics/ray.c\
	srcs/graphics/hit_cylinder.c\
	srcs/graphics/hit_sp.c\
	srcs/graphics/hit_pl.c\
	srcs/graphics/helper.c\
	srcs/graphics/shading.c\
	srcs/graphics/normal.c\
	srcs/graphics/world.c\
	srcs/error/file.c\
	srcs/parsing/atof.c\
	srcs/parsing/reader.c\
	srcs/parsing/world.c\
	srcs/parsing/light.c\
	srcs/parsing/camera.c\
	srcs/parsing/common.c\
	srcs/parsing/sphere.c\
	srcs/parsing/plane.c\
	srcs/parsing/cylinder.c\
	srcs/render/draw.c\
	srcs/render/hook.c\
	srcs/render/window.c\
	srcs/render/interact.c\
	srcs/help/menu.c\
	main.c

OBJS = $(SRCS:.c=.o)

# === TARGETS ===
all: $(LIBFT_A) $(MLX42_LIB) $(PROG)

$(PROG): $(OBJS)
	$(CMD) $(CFLAGS) -o $@ $^ $(LDFLAGS)

debug: CFLAGS = $(DEBUG_FLAGS) -I$(LIBFT_DIR) $(MLX42_INCLUDE) -std=c11
debug: re

# === LIBFT ===
$(LIBFT_A):
	@if [ ! -d $(LIBFT_DIR) ]; then \
		echo "Cloning ft_libft..."; \
		git clone $(LIBFT_REPO); \
	fi
	@$(MAKE) -C $(LIBFT_DIR)

# === MLX42 ===
$(MLX42_LIB):
	@if [ ! -d $(MLX42_DIR) ]; then \
		echo "Cloning MLX42..."; \
		git clone $(MLX42_REPO); \
	fi
	@echo "Building MLX42..."; \
	$(MLX42_BUILD_CMD)

# === BUILD RULE ===
%.o: %.c
	@mkdir -p $(dir $@)
	$(CMD) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(MLX42_DIR)/build

fclean: clean
	rm -f $(PROG)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re debug
