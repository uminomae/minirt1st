NAME = miniRT
SRCDIR = ./src
OBJDIR = ./obj
INCDIR = -I./include -I./libft -I./minilibx
SRCS = $(shell find $(SRCDIR) -type f -name '*.c')
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DEPENDS = $(OBJS:.o=.d)
CC = cc
FLAG = -MMD -MP -Wall -Wextra -Werror
# FLAG = -MMD -MP -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=undefined
LIBFT = ./libft/libft.a
MLX_IMAC2017 = -framework OpenGL -framework AppKit -L./minilibx -lmlx -lm
MLX_MAC = -I./minilibx -L/usr/X11R6/lib -lmlx -lXext -lX11
MLX_M1_MAC =  -framework Metal -framework Metalkit -L./minilibx_mms_20200219 -lmlx -lm
MLX_LINUX = -I./minilibx -L./minilibx -lmlx -lXext -lX11

all: $(NAME)

linux:
	make LINUX=1

M1:
	make M1=1

s: 	
	make 
	./miniRT test/sample.rt
sm: 	
	make 
	./miniRT test/sample/sample_move.rt
sp:
	make 
	./miniRT test/sample/sample_picture.rt
o:
	make
	sh test/test_ok.sh
ocm:
	make
	sh test/test_ok_cm.sh
ocy:
	make
	sh test/test_ok_cy.sh
oo:
	make
	sh test/test_ok_other.sh
opl:
	make
	sh test/test_ok_pl.sh
osp:
	make
	sh test/test_ok_sp.sh
n:
	make
	sh test/test_ng.sh
t:
	make
	./miniRT test/ok/cy/test7.rt
h:
	make
	./miniRT test/hormon.rt

$(NAME): $(OBJS)
	make -C ./libft
	make -C ./minilibx

ifdef LINUX
	$(CC) $(FLAG) $(LIBFT) $(MLX_LINUX) -o $@ $^
else ifdef M1
	$(CC) $(FLAG) $(LIBFT) $(MLX_M1_MAC) -o $@ $^
else ifdef x11
	$(CC) $(FLAG) $(LIBFT) $(MLX_MAC) -o $@ $^
else 
	$(CC) $(FLAG) $(LIBFT) $(MLX_IMAC2017) -o $@ $^
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(FLAG) $(INCDIR) -o $@ -c $<

clean:
	make clean -C ./minilibx
	make fclean -C ./libft
	rm -rf $(OBJDIR) $(DEPENDS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

bonus:
	meke re

linuxre: fclean
	make LINUX=1

-include $(DEPENDS)

.PHONY: all clean fclean re
