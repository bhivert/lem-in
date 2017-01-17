# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/01 16:50:57 by bhivert           #+#    #+#              #
#    Updated: 2015/01/01 16:50:57 by bhivert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
.PHONY: all, clean, fclean, re, _make, _make_clean, _make_fclean
.SUFFIXES:

NAME		=	lem-in

DEBUG		=	0
ifeq ($(DEBUG), 0)
	CC	=	gcc
	CFLAGS	=	-Wall -Wextra -Werror $(INCS_FLAGS) -O3
else
	CC	=	clang
	CFLAGS	=	-Wall -Wextra $(INCS_FLAGS) -g3
endif

DEPENDS		=	

LIBS_DIR	=	-Llibft \

LIBS		=	-lft \

INCS_FLAGS	=	-Iincludes \
			-Ilibft/includes \

SUB_MAKE	=	libft \

SRCS_DIR	=	srcs
SRCS_SRCS	=	$(SRCS_DIR)/checkhill.c \
			$(SRCS_DIR)/gethill.c \
			$(SRCS_DIR)/getways.c \
			$(SRCS_DIR)/main.c \
			$(SRCS_DIR)/print_hill.c \
			$(SRCS_DIR)/stable_research.c \

SRCS_STREAM_DIR	=	srcs/stream
SRCS_STREAM_SRCS	=	$(SRCS_STREAM_DIR)/stream_delete.c \
			$(SRCS_STREAM_DIR)/stream_flush.c \
			$(SRCS_STREAM_DIR)/stream_getline.c \
			$(SRCS_STREAM_DIR)/stream_new.c \
			$(SRCS_STREAM_DIR)/stream_out.c \
			$(SRCS_STREAM_DIR)/stream_state.c \

SRCS_BITSET_DIR	=	srcs/bitset
SRCS_BITSET_SRCS	=	$(SRCS_BITSET_DIR)/bitset.c \

SRCS		=	$(SRCS_SRCS) \
			$(SRCS_STREAM_SRCS) \
			$(SRCS_BITSET_SRCS) \

OBJS		=	$(SRCS:.c=.o)


all		:	_make $(NAME)

$(NAME)		:	$(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS_DIR) $(LIBS) -o $@

%.o	:	%.c $(DEPENDS)
	$(CC) $(CFLAGS) -c $< -o $@

clean		:	_make_clean
	rm -rf $(OBJS)

fclean		:	_make_fclean clean
	rm -rf $(NAME)

re			:	fclean all

_make		:
ifeq ($(DEBUG), 2)
	$(foreach MAKE, $(SUB_MAKE),make -C $(MAKE) DEBUG=$(DEBUG);)
else
	$(foreach MAKE, $(SUB_MAKE),make -C $(MAKE);)
endif

_make_clean		:
	$(foreach MAKE, $(SUB_MAKE),make -C $(MAKE) clean;)

_make_fclean		:
	$(foreach MAKE, $(SUB_MAKE),make -C $(MAKE) fclean;)
