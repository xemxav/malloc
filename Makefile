.PHONY: all clean fclean re

CC = gcc
CFLAGS = -Wall -Wextra -Werror

ifeq ($(HOSTTYPE),)
    		HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
SYM_LINK = libft_malloc.so
PATH_OBJ = ./obj/
PATH_SRC = ./src/
PATH_INC = ./includes/

#******************************************************************************#
#                              MALLOC TEST                                  #
#******************************************************************************#

FILES = malloc free realloc zoning tiny small show_alloc_mem show_alloc_mem_ex \
print_adress deleting


OBJ = $(addprefix $(PATH_OBJ), $(addsuffix .o , $(FILES)))
SRC = $(addprefix $(PATH_SRC), $(addsuffix .c , $(FILES)))

#******************************************************************************#
#                                  LIBFT                                       #
#******************************************************************************#

PATH_LIB = ./libft/
PATH_INC_LIB = ./libft/
NAME_LIB = ft
INC_LIB = -L $(PATH_LIB) -l $(NAME_LIB)

#******************************************************************************#
#                                    RULES                                     #
#******************************************************************************#

all: $(NAME)

clean:
	@printf "\n\033[1m SUPPRESSION DES OBJETS\033[0m\n"
	@rm -rf $(PATH_OBJ)
	@make clean -C $(PATH_LIB)

fclean: clean
	@printf "\n\033[1mSUPPRESSION DE $(NAME)\033[0m\n"
	@rm -rf $(NAME)
	@rm -rf $(SYM_LINK)
	@rm -rf $(PATH_OBJ)
	@make clean -C $(PATH_LIB)

re: fclean all

#******************************************************************************#
#                                  Compilation                                 #
#******************************************************************************#

suptest:
	rm test0 test1 test2 test3 test4 test5

comptestfree: $(NAME)
	./run.sh /usr/bin/time -l ./test2
	./run.sh /usr/bin/time -l ./test1
	./run.sh /usr/bin/time -l ./test0

comptest: $(NAME)
	./run.sh /usr/bin/time -l ./test0
	./run.sh /usr/bin/time -l ./test1

test5: $(NAME)
	@$(CC) -L. -lft_malloc correc/test5.c -o test5
	./test5

test4: $(NAME)
	@$(CC) correc/test4.c -o test4
#	/usr/bin/time -l ./test4
	@echo "avec le mien:"
	./run.sh /usr/bin/time -l ./test4

test3bis: $(NAME)
	@$(CC) correc/test3bis.c -o test3bis
	/usr/bin/time -l ./test3bis
	@echo "avec le mien:"
	./run.sh /usr/bin/time -l ./test3bis

test3: $(NAME)
	@$(CC) correc/test3.c -o test3
	/usr/bin/time -l ./test3
	@echo "avec le mien:"
	./run.sh /usr/bin/time -l ./test3

test2: $(NAME)
	@$(CC) correc/test2.c -L. -lft_malloc -o test2
	/usr/bin/time -l ./test2
	@echo "avec le mien:"
	./run.sh /usr/bin/time -l ./test2

test1: $(NAME)
	@$(CC) correc/test1.c -o test1
	/usr/bin/time -l ./test1
	@echo "avec le mien:"
	./run.sh /usr/bin/time -l ./test1

test0: $(NAME)
	@$(CC)  correc/test0.c -o test0
	/usr/bin/time -l ./test0
	@echo "avec le mien:"
	./run.sh /usr/bin/time -l ./test0

test: $(NAME)
	$(CC) $(CFLAGS) libft_malloc.so test.c -o my_test.out
	./run.sh ./my_test.out


$(NAME): $(PATH_OBJ) $(OBJ)
	@echo "creation of lib"
	@make -C $(PATH_LIB)
	@$(CC) $(CFLAGS) $(OBJ) -I $(PATH_INC) $(INC_LIB) -shared -o $(NAME)
	@echo "$(NAME) has been compiled"
	@ln -sf $(NAME) $(SYM_LINK)
	@echo "Symbolic link created"
	cp $(NAME) test_malloc

$(PATH_OBJ)%.o: $(PATH_SRC)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -fPIC -I $(PATH_INC) -I $(PATH_INC_LIB) -c $< -o $@

$(PATH_OBJ):
	@mkdir -p $(PATH_OBJ)