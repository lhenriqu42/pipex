# NAME
NAME := pipex
VALGRIND_LOG := valgrind.log

# FLAGS
CFLAGS := -O3 -fno-stack-protector -Wall -Wextra -g3 -Werror

# LIBS
LIB_PATH := ./libs/libft
LIB_NAME := libft.a

# PATHS
SRC_PATH := ./src/
BIN_PATH := ./bin/
HEADER_PATH := ./includes/

# COLORS
GREEN := \033[32m
RED := \033[31m
CYAN := \033[36m
VIOLET := \033[38;5;208m
COLOR_LIMITER := \033[0m

# SOURCES AND OBJECTS
FILES := main.c exec.c path.c cleaner.c init.c utils.c
SRCS := $(addprefix $(SRC_PATH), $(FILES))
OBJ := $(addprefix $(BIN_PATH), $(FILES:%.c=%.o))

# BONUS
BONUS_NAME := pipex_bonus
BONUS_SRC_PATH := ./src/bonus/
BONUS_FILES := main_bonus.c exec_bonus.c path_bonus.c cleaner_bonus.c init_bonus.c utils_bonus.c
BONUS_SRCS := $(addprefix $(BONUS_SRC_PATH), $(BONUS_FILES))
BONUS_OBJ := $(addprefix $(BIN_PATH), $(BONUS_FILES:%.c=%.o))

all: libft $(BIN_PATH) print $(NAME)
bonus: libft $(BIN_PATH) print_bonus $(BONUS_NAME)

libft:
ifeq ($(wildcard $(LIB_PATH)/$(LIB_NAME)),)
	@make build -C $(LIB_PATH) --no-print-directory
endif

$(BIN_PATH):
	@mkdir -p $(BIN_PATH)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIB_PATH) -lft -I$(HEADER_PATH)
	@printf "$(CYAN)----- --------------------------------------------- -----\n$(COLOR_LIMITER)"
	@printf "$(CYAN)---- | PIPEX executable was created successfully!! | ----\n$(COLOR_LIMITER)"
	@printf "$(CYAN)----- --------------------------------------------- -----\n$(COLOR_LIMITER)"

$(BONUS_NAME): $(BONUS_OBJ)
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJ) -L$(LIB_PATH) -lft -I$(HEADER_PATH)
	@printf "$(CYAN)----- --------------------------------------------------- -----\n$(COLOR_LIMITER)"
	@printf "$(CYAN)---- | PIPEX_BONUS executable was created successfully!! | ----\n$(COLOR_LIMITER)"
	@printf "$(CYAN)----- --------------------------------------------------- -----\n$(COLOR_LIMITER)"

print: 
ifeq ($(wildcard $(NAME)),)
	@printf "$(GREEN) ------------------------$(COLOR_LIMITER)"
	@printf "$(GREEN)| Compiling Main Project |$(COLOR_LIMITER)"
	@printf "$(GREEN)------------------------$(COLOR_LIMITER)"
	@echo " "
endif

print_bonus: 
ifeq ($(wildcard $(BONUS_NAME)),)
	@printf "$(GREEN) -------------------------$(COLOR_LIMITER)"
	@printf "$(GREEN)| Compiling Bonus Project |$(COLOR_LIMITER)"
	@printf "$(GREEN)-------------------------$(COLOR_LIMITER)"
	@echo " "
endif

$(BIN_PATH)%.o: $(SRC_PATH)%.c
	@printf "$(GREEN)[Compiling]$(COLOR_LIMITER) $(notdir $<)..."
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_PATH)
	@echo " "

$(BIN_PATH)%.o: $(BONUS_SRC_PATH)%.c
	@printf "$(GREEN)[Compiling]$(COLOR_LIMITER) $(notdir $<)..."
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_PATH)
	@echo " "

clean:
	@printf "$(RED)[Removing Objects...]$(COLOR_LIMITER)\n"
	@make clean -C $(LIB_PATH) --no-print-directory
	@rm -rf $(VALGRIND_LOG)
	@rm -rf $(BIN_PATH)

fclean: clean
	@printf "$(RED)[Removing $(notdir $(NAME))...]$(COLOR_LIMITER)\n"
	@make fclean -C $(LIB_PATH) --no-print-directory
	@rm -rf $(NAME)

re: fclean
	@make --no-print-directory

valgrind: all
	@valgrind --leak-check=full \
	--show-reachable=yes \
	--track-fds=yes \
	--show-leak-kinds=all -s \
	--track-origins=yes \
	--log-file=$(VALGRIND_LOG) \
	./$(NAME) infile ls ls outfile
	@cat $(VALGRIND_LOG)

.PHONY: all clean fclean re print libft valgrind print_bonus
