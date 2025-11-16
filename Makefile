NAME_CLIENT = client
NAME_SERVER = server

CLIENT_SRCS = src/client.c
SERVER_SRCS = src/server.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCS = include/minitalk.h

LIBFT = libft/libft.a
LIBFT_PATH = libft

# CHECK = \033[32m[✔]\033[0m
# REMOVE = \033[31m[✘]\033[0m
# BLUE = \033[1;34m
# RESET = \033[0m

CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(CLIENT_OBJS)
	@ make -C $(LIBFT_PATH)
	@ $(CC) $(CFLAGS) -I $(INCS) $(LIBFT) -o $(NAME_CLIENT) $(CLIENT_OBJS)
	@ ac rc $(NAME_CLIENT) $(CLIENT_OBJS)
	@echo "$(CHECK) $(BLUE)client ready$(RESET)"

$(NAME_SERVER): $(SERVER_OBJS)
	@ $(CC) $(CFLAGS) -I $(INCS) $(LIBFT) -o $(NAME_SERVER) $(SERVER_OBJS)
	@ ac rc $(NAME_SERVER) $(SERVER_OBJS)
	@echo "$(CHECK) $(BLUE)server ready$(RESET)"

.c.o:
	@ $(CC) $(CFLAGS) -I $(INCS) -c $< -o $@

clean:
	@ make clean -C $(LIBFT_PATH)
	@ $(RM) $(CLIENT_SRCS:.c=.o) $(SERVER_SRCS:.c=.o)
	@echo "$(REMOVE) $(BLUE)Remove client and server object files... $(RESET)"

fclean: clean
	@ make fclean -C $(LIBFT_PATH)
	@ $(RM) $(NAME_CLIENT) $(NAME_SERVER)
	@echo "$(REMOVE) $(BLUE)Remove $(NAME_CLIENT) and $(NAME_SERVER)$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re