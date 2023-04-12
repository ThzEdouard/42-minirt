NAME	= minirt
INCLUDE	= include/
SRC_DIR	= ./
OBJ_DIR	= obj/
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -I./include -I./minilibx-linux -I./libft -g
rm		= rm -f

SRC_MINIRT	= src/
FT_MINIRT	= main

SRC_CHECKER = src/parsing/Checker/
FT_CHECKER = check_coord check_vector check_range_rgb check_a check_c check_l check_sp check_pl check_cy

SRC_PARSING	= src/parsing/
FT_PARSING	= name_file norm_file check_id

SRC_CALCUL	= src/calcul/
FT_CALCUL	= ray plane util sphere cylindre

SRC_WINDOW = src/window/
FT_WINDOW = creat_window

SRC_FILES+=$(addprefix $(SRC_MINIRT),$(FT_MINIRT))
SRC_FILES+=$(addprefix $(SRC_PARSING),$(FT_PARSING))
SRC_FILES+=$(addprefix $(SRC_CHECKER),$(FT_CHECKER))
SRC_FILES+=$(addprefix $(SRC_WINDOW),$(FT_WINDOW))
SRC_FILES+=$(addprefix $(SRC_CALCUL),$(FT_CALCUL))

SRC		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ		= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all:	$(NAME)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<

$(NAME):	$(OBJ) $(INCLUDE)
			make -C libft/
			make -C minilibx-linux
			mv libft/libft.a .
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft.a minilibx-linux/libmlx_Linux.a minilibx-linux/libmlx.a  -L/usr/include/../lib -lXext -lX11 -lm -lbsd

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)$(SRC_MINIRT)
			@mkdir -p $(OBJ_DIR)$(SRC_PARSING)
			@mkdir -p $(OBJ_DIR)$(SRC_CHECKER)
			@mkdir -p $(OBJ_DIR)$(SRC_WINDOW)
			@mkdir -p $(OBJ_DIR)$(SRC_CALCUL)
			@echo "\033[0;32m [OK] \033[0;32m" $<
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) -rf $(OBJ_DIR)
			make clean -C libft/
			make clean -C minilibx-linux
			rm -rf libft.a
			rm -rf libmlx_Linux.a

fclean:		clean
			$(RM) -f $(NAME)

val:		$(NAME)
			valgrind --leak-check=full --show-leak-kinds=all ./minirt map.rt

re:		fclean all

.PHONY:		all clean fclean re
