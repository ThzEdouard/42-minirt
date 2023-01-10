NAME	= minirt
INCLUDE	= include/
SRC_DIR	= ./
OBJ_DIR	= obj/
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -I./include -I./minilibx-linux -I./libft -g
rm		= rm -f

SRC_MINIRT	= src/
FT_MINIRT	= main

SRC_PARSING	= src/parsing/
FT_PARSING	= name_file norm_file

SRC_FILES+=$(addprefix $(SRC_MINIRT),$(FT_MINIRT))
SRC_FILES+=$(addprefix $(SRC_PARSING),$(FT_PARSING))

SRC		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ		= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF	= .cache_exists

all:	$(NAME)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<

$(NAME):	$(OBJ) $(INCLUDE)
			make -C libft/
			mv libft/libft.a .
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft.a

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "\033[0;32m [OK] \033" $<
			$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
			mkdir -p $(OBJ_DIR)
			mkdir -p $(OBJ_DIR)$(SRC_MINIRT)
			mkdir -p $(OBJ_DIR)$(SRC_PARSING)

clean:
			$(RM) -rf $(OBJ_DIR)
			make clean -C libft/
			rm -rf libft.a

fclean:		clean
			$(RM) -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re