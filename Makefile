NAME = minishell

SRCS := srcs/main.c \
	srcs/init/init.c \
	srcs/parsing/get_input.c \
	srcs/parsing/parsing.c \
	srcs/parsing/utils.c \
	srcs/parsing/handle_tokens/handle_word.c \
	srcs/parsing/handle_tokens/handle_tokens.c \
	srcs/parsing/handle_tokens/create_node_for_token.c \
	srcs/parsing/parser_srcs/parser.c \
	srcs/parsing/parser_srcs/fill_cmd_lst.c \
	srcs/parsing/parser_srcs/fill_special_operator_cmd.c \
	srcs/parsing/clear_data.c \
	srcs/parsing/expand/expand_tokens.c \
	
HEADER := includes/minishell.h \
		includes/parsing.h \
		libft/libft.h
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3
CPPFFLAGS := -MMD -MP

RM := rm -rf

SRC_DIR := srcs/
OBJ_DIR := .objs/
DEPS := $(OBJS:.o=.d)
INCS := -I./includes -I./libft

OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

BOLD := \033[1m
GREEN := \033[0;32m
RED := \033[0;31m
BLUE := \033[0;34m
MAGENTA := \033[0;35m
CYAN    := \033[0;36m
YELLOW := \033[0;33m
END := \033[0m

CHECKMARK := "✔️"
WARNING := "⚠️"
FIRE := "🔥"
OK := "✅"
CLEAN := "🧹"
BUILD := "🛠️"
SUCCESS := "🎉"
DONE := "🏁"

-include $(DEPS)

all: $(NAME)

$(NAME): libft/libft.a $(OBJS) Makefile
	@$(CC) $(CFLAGS) -lreadline $(OBJS) $(INCS) ./libft/libft.a -o $@
	@echo "$(OK)$(MAGENTA)$(BOLD) Compilation successful !$(SUCCESS)$(END)"


$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	@echo "$(BUILD)$(GREEN)$(BOLD) [Compiling]$(END) $<"
	@$(CC) $(CFLAGS) $(INCS) $(CPPFFLAGS) -c -o $@ $<

libft/libft.a : FORCE
	@$(MAKE) --no-print-directory -C libft

FORCE: 

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C libft clean
	@echo "$(YELLOW)$(BOLD)$(CLEAN)Clean up...$(END)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C libft fclean
	@echo "$(YELLOW)$(BOLD)$(CLEAN)Everything is clean !$(DONE)$(END)"

re: fclean all

.PHONY: all clean fclean re libft FORCE
