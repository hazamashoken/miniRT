# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 16:47:52 by tliangso          #+#    #+#              #
#    Updated: 2023/01/13 21:01:38 by abossel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
NAME		= miniRT

### DIR ###
HEAD			= -I./include
DIRSRC			= ./src
BUILD_DIR		= ./build
LIBFT_DIR		= ./src/libft

### TESTER GIT URL ###
TESTER1		=
TESTER2		=
TESTER3		=
TESTER4		=

### PATH ###
SRCS		= $(shell find $(DIRSRC) -name '*.c')

### OBJECT FILE ###
OBJS		= $(SRCS:%=$(BUILD_DIR)/%.o)
PROTO_OBJS		= $(PROTO_SRCS:%=$(BUILD_DIR)/%.o)
LEXER_OBJS		= $(LEXER_SRCS:%=$(BUILD_DIR)/%.o)

### INCLUDE ###
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	LIBMLX = minilibx-linux/libmlx.a
	MLX_DIR = minilibx-linux
else
	LIBMLX	= libmlx/libmlx.a
	MLX_DIR = libmlx
endif
LIB 	= $(LIBMLX)

### COMPILATION ###
CC		= cc
RM		= rm -r
CFLAGS	= -g -mavx -O2 #-Wall -Wextra -Werror
LFLAGS	= -lm -Llibmlx -lmlx

ifeq ($(UNAME), Linux)
	LFLAGS	+= -lXext -lX11 -Imlx_Linux -Lmlx_Linux -lmlx_Linux -lz
else
	LFLAGS	+= -framework OpenGL -framework Appkit
endif

### COLORS ###
NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

### RULES ###
all: $(LIBMLX) $(BUILD_DIR)/$(NAME)

$(BUILD_DIR)/$(NAME): $(OBJS)
	@${CC} ${CFLAGS} $(OBJS) $(LIB) $(LFLAGS) -o $@
	@echo "$(GREEN)$@$(NOC)"
	@cp $(BUILD_DIR)/$(NAME) .

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEAD)  -c -o $@ $<
	@echo "$(GREEN)$(CC) $@$(NOC)"

$(LIBMLX):
	echo "$(YELLOW)Compiling mlx...$(NOC)"
	echo "on $(UNAME)"
	make -C $(MLX_DIR)

test:
	@echo "$(LIB)\n"
	@echo "$(LEXER_SRCS)\n"
	@echo "$(BUILD_DIR)/$(LEXER_NAME)\n"
	@echo "$(LEXER_OBJS)\n"

bonus: ${BONUS_NAME}

clean:
	@echo "$(RED)clean$(NOC)"
	@if [ -f $(BUILD_DIR)/$(LEXER_NAME) ]; then\
		mv $(BUILD_DIR)/$(LEXER_NAME) .;\
	fi
	@if [ -d $(BUILD_DIR) ]; then\
		${RM} $(BUILD_DIR);\
	fi
  
fclean: clean
	@echo "$(RED)fclean$(NOC)"
	@if [ -f ${NAME} ]; then\
		${RM} ${NAME};\
	fi
  
re: fclean	all

tester:
	@echo "$(YELLOW)Testers are not perfect but its good enough$(NOC)"
	git clone ${TESTER1} TESTER1
	git clone ${TESTER2} TESTER2
	git clone ${TESTER3} TESTER3
	git clone ${TESTER3} TESTER4

norm:
	norminette

gitpush:
	git add .
	git status
	git commit -m ${NAME}
	git push

help:
	@clear
	@echo "$(GREEN)Avaibles options:$(NOC)"
	@echo "$(RED)==================$(NOC)"
	@echo "$(RED)| $(YELLOW)make ${NAME} $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make ${BONUS_NAME}   $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make norm      $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make tester    $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make clean     $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make fclean    $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make re        $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make help      $(RED)|$(NOC)"
	@echo "$(RED)==================$(NOC)"

tar:
	tar -zcvf ${NAME}.tar.gz *

.PHONY:		all	clean	fclean	re bonus norm gitpush tester help tar
