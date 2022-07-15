NAME = minishell
BUILD_DIR = build
VPATH = srcs/:srcs/utils
SRCS = $(wildcard srcs/*.c srcs/utils/*.c) 
OBJ_FILES = $(addprefix $(BUILD_DIR)/, $(notdir $(patsubst %.c, %.o, $(SRCS))))
HEADER_FILES = -I includes/ -I includes/utils/
CFLAGS = -Wall -Werror -Wextra #-lreadline #-fsanitize=address
READLINE = -lreadline
CC = gcc

all: build_dir $(NAME)

$(NAME): $(OBJ_FILES)
	@echo Assembling $(NAME)
	@$(CC) $(READLINE) -o $@ $^ $(CFLAGS)
	@echo $(NAME) has been made!

$(BUILD_DIR)/%.o: %.c
	@$(CC) $(HEADER_FILES) -c $(CFLAGS) -o $@ $<

build_dir:
	clear
	@if [ -d "./$(BUILD_DIR)" ]; then \
	echo "Build Directory Already Exists"; \
	else \
	mkdir -p $(BUILD_DIR); \
	fi

clean:
	clear
	@echo Cleaning all object files 
	@ rm -f $(BUILD_DIR)/*.o
	@echo Removing Build Directory
	@if [ -d "./$(BUILD_DIR)" ]; then \
	rmdir $(BUILD_DIR); fi

fclean: clean
	@echo Removing $(NAME)
	@rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re build_dir bonus