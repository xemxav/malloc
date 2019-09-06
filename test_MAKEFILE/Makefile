.PHONY: all clean fclean re

NAME = libft_malloc_$$(HOSTTYPE).so

all: $(NAME)

$(NAME): make_name
	echo $(NAME)

make_name:
	ifeq ($(HOSTTYPE),)
    		HOSTTYPE := $(shell uname -m)_$(shell uname -s)
    endif