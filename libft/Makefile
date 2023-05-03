SRCS =	\
		ft_memset.c     \
		ft_memmove.c    \
		ft_memchr.c     \
		ft_memcmp.c     \
		ft_memcpy.c     \
		ft_bzero.c      \
		ft_atoi.c       \
		ft_strlen.c     \
		ft_strlcpy.c    \
		ft_strlcat.c    \
		ft_strchr.c     \
		ft_strrchr.c    \
		ft_strnstr.c    \
		ft_strncmp.c    \
		ft_atoi.c       \
		ft_isalnum.c    \
		ft_isdigit.c    \
		ft_isalpha.c    \
		ft_isascii.c    \
		ft_isprint.c    \
		ft_tolower.c    \
		ft_toupper.c    \
		ft_calloc.c     \
		ft_strdup.c     \
		ft_substr.c     \
		ft_strjoin.c    \
		ft_strtrim.c    \
		ft_split.c      \
		ft_putchar_fd.c \
		ft_putstr_fd.c  \
		ft_putendl_fd.c \
		ft_putnbr_fd.c  \
		ft_itoa.c       \
		ft_strmapi.c    \
		ft_striteri.c   \
		get_next_line.c \
		get_next_line_utils.c

BONUS = ft_lstnew.c \
        ft_lstadd_front.c \
        ft_lstsize.c  \
        ft_lstlast.c \
        ft_lstadd_back.c \
        ft_lstdelone.c \
        ft_lstclear.c \
        ft_lstiter.c \
        ft_lstmap.c

SRC_FILES = $(SRCS) $(BONUS)

OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

NAME = libft.a

CC = cc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror -I.

NUM_FILES = $(words $(SRC_FILES))
CURRENT_FILE = 1

define show_progress
	@echo -n "\033[0;34m [$(CURRENT_FILE)/$(NUM_FILES)] \033[0m"
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
endef

$(OBJ_DIR)%.o: %.c
		@mkdir -p $(OBJ_DIR)
		@echo "\033[0;32m [OK] \033[0m" $<
		$(show_progress)
		@${CC}  ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
		@ar rcs ${NAME} ${OBJS}
		@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling: \033[0m" ${NAME}

bonus: ${OBJS}
		ar rcs ${NAME} ${OBJS}
all:		${NAME}

clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all clean fclean re bonus
