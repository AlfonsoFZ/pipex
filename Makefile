NAME= pipex
CC= gcc
INCLUDE = ./include/
CFLAGS= -Wall -Werror -Wextra -I./$(INCLUDE)
SRC_DIR= src/
OBJ_DIR= obj/
SRC_FILES= pipex.c ft_split_pipex.c ft_putendl_fd.c ft_putstr_fd.c ft_split.c \
ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
ft_substr.c ft_strtrim.c ft_pipex_utils.c ft_pipex_parse.c  
SRC= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS= $(SRC_FILES:.c=.o)
OBJ= $(addprefix $(OBJ_DIR), $(OBJS))
OBJF= .cache_existsmake

all: $(NAME) 

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) ./$(SRC) -o $(NAME) 

$(OBJF):
	@mkdir -p $(OBJ_DIR)	

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJF)
	@$(CC) -c $(CFLAGS) $< -o $@ 
clean:
	@rm -rf $(OBJ_DIR)

fclean: clean 
	@rm -rf $(NAME)

re: fclean all
.PHONY: all re fclean clean bonus