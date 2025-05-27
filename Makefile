NAME = minishell

SRCS := srcs/main.c \
		srcs/utils.c \
		srcs/get_input/get_input.c \
		srcs/get_input/handle_signal.c \
		srcs/init/init.c \
		srcs/parsing/parsing.c \
		srcs/parsing/utils_parsing.c \
		srcs/parsing/handle_tokens/handle_word.c \
		srcs/parsing/handle_tokens/handle_tokens.c \
		srcs/parsing/handle_tokens/create_node_for_token.c \
		srcs/parsing/parser_srcs/parser.c \
		srcs/parsing/parser_srcs/convert_lst_to_array.c \
		srcs/parsing/parser_srcs/fill_cmd_lst.c \
		srcs/parsing/parser_srcs/fill_special_operator_cmd.c \
		srcs/parsing/handle_tokens/handle_word_utils.c \
		srcs/parsing/clear_data.c \
		srcs/parsing/expand/expand_tokens.c \
		srcs/parsing/expand/handle_expansion.c \
		srcs/parsing/expand/expand_utils.c \
		srcs/parsing/expand/remove_quote.c \
		srcs/parsing/expand/wildcards/expand_wildcards.c \
		srcs/parsing/expand/wildcards/wildcards_utils.c \
		srcs/exec/listed_env_init.c \
		srcs/exec/utils_exec/getters.c \
		srcs/exec/exec.c \
		srcs/here_doc/here_doc_init.c \
		srcs/builtins/exit.c \
		srcs/debug/print_tokenizer.c \
		srcs/debug/print_parser.c \
		srcs/debug/print_expand.c \

HEADER := 	includes/minishell.h \
			includes/parsing.h \
			includes/exec.h \
			includes/debug.h \
			includes/builtins.h \
			libft/libft.h
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3
CPPFFLAGS := -MMD -MP
SHELL = /bin/bash

DEBUGFLAGS := valgrind --leak-check=full  --trace-children=yes --track-fds=yes
DEBUG_VALUE ?= 0
DEBUG_FILE := .debug_value
CFLAGS += -DDEBUG_VALUE=$(DEBUG_VALUE)
LAST_DEBUG_VALUE := $(shell if [ -f $(DEBUG_FILE) ]; then cat $(DEBUG_FILE); else echo 0; fi)
REBUILD_NEEDED := $(shell if [ $(DEBUG_VALUE) -ne $(LAST_DEBUG_VALUE) ]; then echo 1; else echo 0; fi)
DEBUG_FILE_EXIST := $(shell if [ -f $(DEBUG_FILE) ]; then echo 1; else echo 0; fi)

RM := rm -rf

SRC_DIR := srcs/
OBJ_DIR := .objs/
DEPS := $(OBJS:.o=.d)
INCS := -I./includes -I./libft

OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DEPS:= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.d,$(SRCS))

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
FINGER := "👉​"
FINGER_LEFT := "👈​"
DONE := "🏁"

.DEFAULT_GOAL=all

-include $(DEPS)

all: $(NAME)

$(NAME): reset_debug libft/libft.a $(OBJS) Makefile
	@$(CC) $(CFLAGS) -lreadline $(OBJS) $(INCS) -DDEBUG_VALUE=$(DEBUG_VALUE) ./libft/libft.a -o $@
	@echo -e "$(OK)$(MAGENTA)$(BOLD) Compilation successful !$(SUCCESS)$(END)"
	@echo $(DEBUG_VALUE) > $(DEBUG_FILE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@echo -e "$(BUILD)$(GREEN)$(BOLD) [Compiling]$(END) $<"
	@$(CC) $(CFLAGS) $(INCS) $(CPPFFLAGS) -c -o $@ $<

libft/libft.a : FORCE
	@$(MAKE) --no-print-directory -C libft

FORCE:

debug:
	@echo -e "$(YELLOW)$(BOLD)$(FINGER) Wich debug level ? $(FINGER_LEFT)$(END)\
	\n\n$(CYAN)$(BOLD)0- $(END)Only Valgrind\n\
	$(CYAN)$(BOLD)1- $(END)Tokenizer\n\
	$(CYAN)$(BOLD)2- $(END)Parser\n\
	$(CYAN)$(BOLD)3- $(END)Expand\n\
	$(CYAN)$(BOLD)4- $(END)???????\n\
	$(CYAN)$(BOLD)5- $(END)All\n"
	@read -s -n 1 value; \
	while ! echo "$$value" | grep -Eq '^[0-5]+$$'; do \
		clear; \
		echo -e "$(RED)$(BOLD)$(WARNING) Input must be a number [0-5] $(WARNING)$(END)\
		\n\n$(CYAN)$(BOLD)0- $(END)Only Valgrind\n\
	$(CYAN)$(BOLD)1- $(END)Tokenizer\n\
	$(CYAN)$(BOLD)2- $(END)Parser\n\
	$(CYAN)$(BOLD)3- $(END)Expand\n\
	$(CYAN)$(BOLD)4- $(END)???????\n\
	$(CYAN)$(BOLD)5- $(END)All\n"; \
		read -s -n 1 value; \
	done;\
	touch includes/debug.h; \
	$(MAKE) --no-print-directory DEBUG_VALUE=$$value; \
	echo -e "$(CYAN)$(BOLD)DEBUG_VALUE = $$value$(END)"
	$(DEBUGFLAGS) ./$(NAME)

reset_debug:
	@if [ $(DEBUG_FILE_EXIST) -eq 0 ]; then \
		touch includes/debug.h; \
	fi
	@if [ $(REBUILD_NEEDED) -eq 1 ]; then \
		echo -e "$(YELLOW)$(BOLD) DEBUG_VALUE changed from $(LAST_DEBUG_VALUE) to $(DEBUG_VALUE), rebuilding...$(END)"; \
		touch includes/debug.h; \
	fi

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C libft clean
	@echo -e "$(YELLOW)$(BOLD)$(CLEAN)Clean up...$(END)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(DEBUG_FILE)
	@$(MAKE) --no-print-directory -C libft fclean
	@echo -e "$(YELLOW)$(BOLD)$(CLEAN)Everything is clean !$(DONE)$(END)"

re: fclean all

.PHONY: all clean fclean re libft FORCE reset_debug debug
