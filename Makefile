SOURCE=conv.c
NAME=$(basename $(SOURCE))

$(NAME): $(SOURCE)
	cc -Wall -Werror $(SOURCE) -o $(NAME) -g -lm

.PHONY: clean
clean:
	rm -rf $(NAME) $(NAME).dSYM

