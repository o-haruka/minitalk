NAME_CLIENT = client
NAME_SERVER = server

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_PATH	= srcs
SRC			= client.c \
			server.c \
			error.c \

SRCS		= $(addprefix $(SRC_PATH)/, $(SRC))

OBJ_PATH	= obj
OBJ 		= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH)/, $(OBJ))

INC_PATH	= includes
INCS		= -I$(INC_PATH)

LIB_PATH	= libft
LIB			= libft.a
LIBS		= $(addprefix $(LIB_PATH)/, $(LIB))

RM			= rm -f

all: $(NAME_CLIENT) $(NAME_SERVER)

$(LIBS):
	@ make -C $(LIB_PATH)

$(NAME_CLIENT): $(OBJ_PATH)/client.o $(OBJ_PATH)/error.o $(LIBS)
	$(CC) $(CFLAGS) $(INCS) $(OBJ_PATH)/client.o $(OBJ_PATH)/error.o $(LIBS) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_PATH)/server.o $(OBJ_PATH)/error.o $(LIBS)
	$(CC) $(CFLAGS) $(INCS) $(OBJ_PATH)/server.o $(OBJ_PATH)/error.o $(LIBS) -o $(NAME_SERVER)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@ mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@ make clean -C $(LIB_PATH)
	$(RM) $(OBJ_PATH)/*.o
	@ rm -rf $(OBJ_PATH)

fclean: clean
	@ make fclean -C $(LIB_PATH)
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)
	@ rm -rf $(OBJ_PATH)

re: fclean all

.PHONY: all clean fclean re