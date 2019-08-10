NAME = ft_ls

INC_DIR :=		./include

SRC_DIR :=		./src
SRC :=			main.c			\
			parse_flags.c		\
			process_files.c		\
			process_directories.c	\

vpath %.c		$(SRC_DIR)

LIB_DIR :=		./subprojects

LIBFT_DIR :=		$(LIB_DIR)/libft
LIBFT_INC :=		$(LIBFT_DIR)/includes
LIBFT_LFLAGS :=		-lft -L$(LIBFT_DIR)
LIBFT :=		$(LIBFT_DIR)/libft.a

OBJ_DIR :=	./obj
OBJ :=		$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CC = clang
CFLAGS = -Wall -Wextra -Werror
LFLAGS = $(LIBFT_LFLAGS)

INC := $(LIBFT_INC) $(INC_DIR)
INC_PARAMS := $(INC:%=-I%)

all: $(NAME)

debug: CFLAGS += -DDEBUG -g -O0
debug: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(LFLAGS) -o $(NAME) $(OBJ)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INC_PARAMS) -c $< -o $@


#libft rules

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)
	
.PHONY: clean fclean
