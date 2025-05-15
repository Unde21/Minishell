NAME = libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror
CPPFFLAGS = -MD -MP -MF

RM := rm -rf
AR := ar -rcs

SRC_DIR := srcs/
OBJ_DIR := .objs/
DEP_DIR = .deps/
OBJB_DIR := .objs_bonus/
DEPB_DIR := .deps_bonus/

INCS = -I .

SRCS := srcs/isbool_functions/ft_isalpha.c \
	srcs/isbool_functions/ft_isdigit.c \
	srcs/isbool_functions/ft_isalnum.c \
	srcs/isbool_functions/ft_isascii.c \
	srcs/isbool_functions/ft_isprint.c \
	srcs/isbool_functions/ft_isspace.c \
	srcs/convert_functions/ft_toupper.c \
	srcs/convert_functions/ft_tolower.c \
	srcs/convert_functions/ft_atoi.c \
	srcs/convert_functions/ft_itoa.c \
	srcs/str_functions/ft_strlen.c \
	srcs/str_functions/ft_strlcpy.c \
	srcs/str_functions/ft_strlcat.c \
	srcs/str_functions/ft_strdup.c \
	srcs/str_functions/ft_substr.c \
	srcs/str_functions/ft_strjoin.c \
	srcs/str_functions/ft_strtrim.c \
	srcs/str_functions/ft_split.c \
	srcs/str_functions/ft_striteri.c \
	srcs/str_functions/ft_strmapi.c \
	srcs/str_functions/ft_strchr.c \
	srcs/str_functions/ft_strrchr.c \
	srcs/str_functions/ft_strncmp.c \
	srcs/str_functions/ft_strcmp.c \
	srcs/str_functions/ft_strnstr.c \
	srcs/memory_functions/ft_memset.c \
	srcs/memory_functions/ft_bzero.c \
	srcs/memory_functions/ft_memcpy.c \
	srcs/memory_functions/ft_memmove.c \
	srcs/memory_functions/ft_memchr.c \
	srcs/memory_functions/ft_memcmp.c \
	srcs/memory_functions/ft_calloc.c \
	srcs/print_functions/ft_putchar_fd.c \
	srcs/print_functions/ft_putstr_fd.c \
	srcs/print_functions/ft_putendl_fd.c \
	srcs/print_functions/ft_putnbr_fd.c \
	srcs/print_functions/ft_printf.c \
	srcs/print_functions/ft_print_format.c \
	srcs/print_functions/ft_dprintf.c \
	srcs/print_functions/ft_dprint_format.c \
	srcs/list_functions/ft_lstnew.c \
	srcs/list_functions/ft_lstadd_front.c \
	srcs/list_functions/ft_lstsize.c \
	srcs/list_functions/ft_lstlast.c \
	srcs/list_functions/ft_lstadd_back.c \
	srcs/list_functions/ft_lstdelone.c \
	srcs/list_functions/ft_lstclear.c \
	srcs/list_functions/ft_lstiter.c \
	srcs/list_functions/ft_lstmap.c \
	srcs/get_next_line/get_next_line.c \
	srcs/get_next_line/get_next_line_utils.c \
	

OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DEPS := $(SRCS:$(SRC_DIR)%.c=$(DEP_DIR)%.d)

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

all: $(NAME)

$(NAME): $(OBJS) Makefile
	@$(AR) $(NAME) $(OBJS)
	@echo "$(CYAN)$(BOLD)$(OK)$(NAME) created successfully!$(SUCCESS)$(END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR) $(DEP_DIR)
	@mkdir -p $(dir $@) $(dir $(DEP_DIR)$*)
	@echo "$(BUILD)$(GREEN)$(BOLD) [Compiling]$(END) $<"
	@$(CC) $(CFLAGS) $(INCS) $(CPPFFLAGS) $(DEP_DIR)$*.d -c $< -o $@

$(OBJ_DIR) $(DEP_DIR):
	@mkdir -p $@

clean:
	@$(RM) $(OBJ_DIR) $(DEP_DIR)
	@echo "$(YELLOW)$(BOLD)$(CLEAN)$(NAME): Clean up...$(END)"

fclean: clean
	@$(RM) $(NAME) $(OBJS_DIR)
	@echo "$(YELLOW)$(BOLD)$(CLEAN)Everything is clean for $(NAME)!$(DONE)$(END)"

re : 
	@$(MAKE) fclean
	@$(MAKE) all

-include $(DEPS)

.PHONY: all clean fclean re
