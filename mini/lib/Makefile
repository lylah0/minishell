CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRC_DIR = src/
OBJ_DIR = obj/

SRC = ft_atoi.c ft_putendl_fd.c ft_strlen.c ft_bzero.c \
		ft_putnbr_fd.c ft_strmapi.c\
		ft_calloc.c        ft_putnbr_fd.c       ft_strncmp.c\
		ft_isalnum.c       ft_putnbr_hex_ptr.c  ft_strncpy.c\
		ft_isalpha.c       ft_putnbr_hex_xlo.c  ft_strnstr.c\
		ft_isascii.c       ft_putnbr_hex_xup.c  ft_strrchr.c\
		ft_isdigit.c       ft_putnbr_u.c        ft_strstr.c\
		ft_isprint.c       ft_putptr.c          ft_strtrim.c\
		ft_iswhitespace.c  ft_putstr.c          ft_substr.c\
		ft_itoa.c          ft_putstr_fd.c       ft_tolower.c\
		ft_memchr.c        ft_split.c           ft_toupper.c\
		ft_memcmp.c        ft_strchr.c          get_next_line.c\
		ft_memcpy.c        ft_strcmp.c         \
		ft_memmove.c       ft_strcpy.c          get_next_line_utils.c\
		ft_memset.c        ft_strdup.c          \
		ft_printf.c        ft_striteri.c        \
		ft_strjoin.c       ft_putnbr.c\
		ft_putchar.c       ft_strlcat.c\
		ft_putchar_fd.c    ft_strlcpy.c


# OBJS = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJS = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all