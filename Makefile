# Parent Makefile

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LIBFT_DIR = libft
INCDIR = headers
SRCDIR = src
OBJDIR = obj
LIBFT = $(LIBFT_DIR)/libft.a

# Sources
SRC = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/operations/*.c) $(wildcard $(SRCDIR)/helpers/*.c) $(wildcard $(SRCDIR)/radix_and_helpers/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Output executable
NAME = push_swap

# Makefile targets
all: $(LIBFT) $(NAME)

# Create object directory if it doesn't exist
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Create the subdirectories under obj/ for each source subdir
$(OBJDIR)/operations:
	@mkdir -p $(OBJDIR)/operations

$(OBJDIR)/helpers:
	@mkdir -p $(OBJDIR)/helpers

$(OBJDIR)/radix_and_helpers:
	@mkdir -p $(OBJDIR)/radix_and_helpers

# Rule to compile .c files into .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(OBJDIR)/operations $(OBJDIR)/helpers $(OBJDIR)/radix_and_helpers
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Rule to create the push_swap executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

# Rule to build the libft library
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean up object files and other build artifacts
clean:
	rm -rf $(OBJDIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

