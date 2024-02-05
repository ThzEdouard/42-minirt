NAME	= minirt
INCLUDE	= include/
SRC_DIR	= ./
OBJ_DIR	= obj/
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -I./include -I./minilibx-linux -I./libft -g
RM		= rm -f

SRC_MINIRT	= src/
FT_MINIRT	= main

SRC_CHECKER = src/parsing/checker/
FT_CHECKER = check_coord check_vector check_range_rgb check_a check_c check_l check_sp check_pl check_cy

SRC_PARSING	= src/parsing/
FT_PARSING	= filename norm_file check_id check_utils

SRC_CALCUL	= src/calcul/
FT_CALCUL	= ray plane util sphere cylindre scene color

SRC_VECTOR = src/vector_color/
FT_VECTOR = my_color my_color2 my_vector my_vector2 rotate

SRC_WINDOW = src/window/
FT_WINDOW = mlx_window mlx_img mlx_event

SRC_FILES+=$(addprefix $(SRC_MINIRT),$(FT_MINIRT))
SRC_FILES+=$(addprefix $(SRC_PARSING),$(FT_PARSING))
SRC_FILES+=$(addprefix $(SRC_CHECKER),$(FT_CHECKER))
SRC_FILES+=$(addprefix $(SRC_WINDOW),$(FT_WINDOW))
SRC_FILES+=$(addprefix $(SRC_CALCUL),$(FT_CALCUL))
SRC_FILES+=$(addprefix $(SRC_VECTOR),$(FT_VECTOR))

SRC		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ		= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

NUM_FILES = $(words $(SRC_FILES))
CURRENT_FILE = 1

define show_progress
	@echo -n "\033[0;34m [$(CURRENT_FILE)/$(NUM_FILES)] \033[0m"
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
endef

all:	$(NAME)

$(NAME):	$(OBJ) $(INCLUDE)
	make -C libft/
	@make -C minilibx-linux
	mv libft/libft.a .
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft.a minilibx-linux/libmlx_Linux.a minilibx-linux/libmlx.a  -L/usr/include/../lib -lXext -lX11 -lm -lbsd
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $(NAME)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_MINIRT)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSING)
	@mkdir -p $(OBJ_DIR)$(SRC_CHECKER)
	@mkdir -p $(OBJ_DIR)$(SRC_WINDOW)
	@mkdir -p $(OBJ_DIR)$(SRC_CALCUL)
	@mkdir -p $(OBJ_DIR)$(SRC_VECTOR)
	@echo "\033[0;32m [OK] \033[0m" $<
	$(show_progress)
	@($(CC) $(CFLAGS) -c $< -o $@) 2> /dev/null || (echo "\033[0;31m [ERROR] \033[0m" $< && $(CC) $(CFLAGS) -c $< -o $@ && exit@) || (echo "\033[0;31m [ERROR] \033[0m" $< && exit 1)

clean:
	$(RM) -rf $(OBJ_DIR)
	@make clean -C libft/
	@make clean -C minilibx-linux
	rm -rf libft.a
	rm -rf libmlx_Linux.a

fclean:		clean
	$(RM) -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
