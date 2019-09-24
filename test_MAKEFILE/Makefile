.PHONY: all clean fclean re

ifeq ($(HOSTTYPE),)
    		HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libmalloc_

all: $(NAME)

$(NAME):
	echo $(NAME).$(HOSTTYPE).so

