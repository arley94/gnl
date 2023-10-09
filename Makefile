CC = cc
CFLAGS = -I. #-Wextra -Werror -Wall
DEPS = 
FILES = get_next_line get_next_line_utils
TEST_FILES = main

OBJ = $(FILES:%=%.o)

T_OBJ = $(TEST_FILES:%=%.o)

NAME = 

$(NAME): $(OBJ)
	ar -rc $@ $^

all: $(NAME)

bonus: $(B_OBJ) $(OBJ)
	ar -rc $(NAME) $^

clean: 
	rm -f $(OBJ) $(B_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(OBJ) $(T_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -D BUFFER_SIZE=1

testb:
	$(CC) -o $@ main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -D BUFFER_SIZE=1
.PHONY: all bonus clean fclean re
