# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/16 00:00:00 by dwilun            #+#    #+#              #
#    Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libmegaft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INC			= -I.
AR			= ar rcs
OBJDIR		= obj

# ----------------------------- MODULO 1: libft ------------------------------ #
# ft_calloc.c, ft_strchr.c e ft_strjoin.c non compaiono: quelle versioni sono
# fornite dal modulo get_next_line, che nella gerarchia ha la precedenza.
LIBFT_SRC	= ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			  ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
			  ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
			  ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
			  ft_strdup.c ft_striteri.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
			  ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
			  ft_substr.c ft_tolower.c ft_toupper.c
LIBFT		= $(addprefix src/libft/, $(LIBFT_SRC))

# --------------------- MODULO 1 bis: libft bonus (ft_lst*) ------------------ #
# Unica differenza fra `make` e `make bonus`.
LIBFTB_SRC	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			  ft_lstmap.c
LIBFT_BONUS	= $(addprefix src/libft_bonus/, $(LIBFTB_SRC))

# --------------------------- MODULO 2: ft_printf ---------------------------- #
# ft_strlen.c non compare: e' identico a quello di libft.
PRINTF_SRC	= ft_conv_printf.c ft_printf.c ft_putchar.c ft_putnbr_b.c \
			  ft_putnbr.c ft_putptr.c ft_putstr.c
PRINTF		= $(addprefix src/ft_printf/, $(PRINTF_SRC))

# ------------------------- MODULO 3: get_next_line -------------------------- #
# Unica versione: quella che tiene uno stato per ogni file descriptor.
GNL			= src/get_next_line/get_next_line.c \
			  src/get_next_line/get_next_line_utils.c

# ---------------------- MODULO 4: collegamento moduli ----------------------- #
CORE		= mega_libft.c

BASE_SRCS	= $(LIBFT) $(PRINTF) $(GNL) $(CORE)
BONUS_SRCS	= $(BASE_SRCS) $(LIBFT_BONUS)

BASE_OBJS	= $(BASE_SRCS:%.c=$(OBJDIR)/%.o)
BONUS_OBJS	= $(BONUS_SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): .mode_base $(BASE_OBJS)
	$(AR) $(NAME) $(BASE_OBJS)

bonus: .mode_bonus $(BONUS_OBJS)
	$(AR) $(NAME) $(BONUS_OBJS)

# I due modi producono lo stesso archivio con contenuti diversi: il marcatore
# di modo forza la ricostruzione quando si passa da `all` a `bonus` e viceversa.
.mode_base:
	@rm -f .mode_bonus $(NAME)
	@touch .mode_base

.mode_bonus:
	@rm -f .mode_base $(NAME)
	@touch .mode_bonus

$(OBJDIR)/%.o: %.c mega_libft.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Allinea .c e single/ alla documentazione scritta in mega_libft.h.
sync:
	@python3 tools/sync.py

sync-check:
	@python3 tools/sync.py --check

# Usato da sync.py per leggere le liste di sorgenti senza duplicarle.
print-%:
	@echo $($*)

clean:
	rm -rf $(OBJDIR) .mode_base .mode_bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus sync sync-check clean fclean re
