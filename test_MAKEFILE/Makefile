.PHONY: all clean fclean re

ifeq ($(HOSTTYPE),)
    		HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_

all: $(NAME)

$(NAME):
	echo $(NAME).$(HOSTTYPE).so

