# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Directories
LIBFT_DIR = libft
INCDIR = headers
SRCDIR = src
OBJDIR = obj
LIBFT = $(LIBFT_DIR)/libft.a

# Output executable
NAME = push_swap

# Explicitly listed source files
SRC = \
	src/push_swap_helpers.c \
	src/push_swap.c \
	src/helpers/lst_help.c \
	src/helpers/ft_atoi_modded.c \
	src/helpers/lst_help2.c \
	src/operations/reverse_rotate_operations.c \
	src/operations/rotate_operations.c \
	src/operations/push_operations.c \
	src/operations/swap_operations.c \
	src/radix_and_helpers/indices_rank.c \
	src/radix_and_helpers/radix_utils.c \
	src/radix_and_helpers/radix.c \
	src/radix_and_helpers/sort.c \
	src/radix_and_helpers/small_sorts.c \
	src/radix_and_helpers/main_sort.c

# Object files
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Default target
all: $(LIBFT) $(NAME)

# Create object files from source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Link all objects into executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lm -o $(NAME)

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -rf $(OBJDIR)
	$(MAKE) clean -C $(LIBFT_DIR)

# Clean all generated files
fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
