# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/17 11:11:59 by lsimon            #+#    #+#              #
#    Updated: 2019/08/22 16:27:27 by lsimon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g

SRCS_DIR = srcs
INC_DIR = inc
OBJS_DIR = objs

SERVER_NAME = server
CLIENT_NAME = client

COMMONS_DIR = commons
SERVER_DIR = server
CLIENT_DIR = client

SERVER_SRC_NAMES = server.c
SERVER_SRC_NAMES += connect_server.c
SERVER_SRC_NAMES += leave_server.c
SERVER_SRC_NAMES += process_command.c
SERVER_SRC_NAMES += ls_command.c
SERVER_SRC_NAMES += exec_builtin.c

CLIENT_SRC_NAMES = client.c
CLIENT_SRC_NAMES += client_ui.c
CLIENT_SRC_NAMES += client_handler.c

COMMONS_SRC_NAMES = create_socket.c
COMMONS_SRC_NAMES += errors.c

SERVER_SRCS = $(addprefix $(SRCS_DIR)/$(SERVER_DIR)/, $(SERVER_SRC_NAMES))
CLIENT_SRCS = $(addprefix $(SRCS_DIR)/$(CLIENT_DIR)/, $(CLIENT_SRC_NAMES))
COMMON_SRCS = $(addprefix $(SRCS_DIR)/$(COMMONS_DIR), $(COMMONS_SRC_NAMES))

SERVER_OBJ_NAMES = $(SERVER_SRC_NAMES:.c=.o)
CLIENT_OBJ_NAMES = $(CLIENT_SRC_NAMES:.c=.o)
COMMON_OBJ_NAMES = $(COMMONS_SRC_NAMES:.c=.o)

SERVER_OBJS_DIR = $(OBJS_DIR)/$(SERVER_DIR)
CLIENT_OBJS_DIR = $(OBJS_DIR)/$(CLIENT_DIR)
COMMON_OBJS_DIR = $(OBJS_DIR)/$(COMMONS_DIR)

SERVER_OBJS = $(addprefix $(SERVER_OBJS_DIR)/, $(SERVER_OBJ_NAMES))
CLIENT_OBJS = $(addprefix $(CLIENT_OBJS_DIR)/, $(CLIENT_OBJ_NAMES))
COMMON_OBJS = $(addprefix $(COMMON_OBJS_DIR)/, $(COMMON_OBJ_NAMES))

all: $(SERVER_NAME) $(CLIENT_NAME)

libft/libft.a:
	@make -C libft/

$(SERVER_NAME): $(SERVER_OBJS) $(COMMON_OBJS) libft/libft.a
	$(CC) -o $@ $^

$(CLIENT_NAME): $(CLIENT_OBJS) $(COMMON_OBJS) libft/libft.a
	$(CC) -o $@ $^

$(SERVER_OBJS_DIR)/%.o: $(SRCS_DIR)/$(SERVER_DIR)/%.c
	@mkdir -p $(SERVER_OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $^

$(CLIENT_OBJS_DIR)/%.o: $(SRCS_DIR)/$(CLIENT_DIR)/%.c
	@mkdir -p $(CLIENT_OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $^

$(COMMON_OBJS_DIR)/%.o: $(SRCS_DIR)/$(COMMONS_DIR)/%.c
	@mkdir -p $(COMMON_OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@make clean -C libft/
	rm -f $(SERVER_OBJS)
	rm -f $(CLIENT_OBJS)
	rm -f $(COMMON_OBJS)

fclean: clean
	@make fclean -C libft/
	rm -f $(SERVER_NAME)
	rm -f $(CLIENT_NAME)

re: fclean all