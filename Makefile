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

# === COMPILER FLAGS ===
CMD = cc
CFLAGS = -Werror -Wall -Wextra -g -fsanitize=address,undefined -I$(LIBFT_DIR) $(MLX42_INCLUDE)
LDFLAGS = -L$(MLX42_DIR)/build -lmlx42 -ldl -lglfw -pthread -lm $(LIBFT_A)

# === SOURCES ===
SRCS = \
	main.c

OBJS = $(SRCS:.c=.o)

# === BUILD TARGETS ===
all : $(LIBFT_A) $(MLX42_LIB) $(PROG)

$(PROG) : $(OBJS)
	$(CMD) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# === LIBFT SETUP ===
$(LIBFT_A) :
	@if [ ! -d $(LIBFT_DIR) ]; then\
		echo "Cloning ft_libft...";\
		git clone $(LIBFT_REPO);\
	fi
	@$(MAKE) -C $(LIBFT_DIR)

# === MLX42 SETUP ===
$(MLX42_LIB) :
	@if [ ! -d $(MLX42_DIR) ]; then\
		echo "Cloning MLX42...";\
		git clone $(MLX42_REPO);\
	fi
	@echo "Building MLX42...";\
	$(MLX42_BUILD_CMD)

%.o : %.c
	$(CMD) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(MLX42_DIR)/build

fclean : clean
	rm -rf $(PROG)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY : all clean fclean re
