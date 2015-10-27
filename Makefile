##
## Makefile for LemIPC in /home/la-val_c/rendu/PSU/lemipc
##
## Made by Cyril La Valle
## Login <la-val_c@epitech.eu>
##
## Started on  Thu Feb 26 00:03:56 2015 Cyril La Valle
## Last update Sun Mar  8 02:11:33 2015 Paul Carensac
##

NAME      := lemipc
DISPLAYER := lemipc_aff

INCDIR    := inc
SRCDIR    := src
OBJDIR    := objs
DISPDIR   := aff

CC        := gcc
CFLAGS    := -W -Wall -Wextra -O1 -DNDEBUG
CFLAGS    += -I $(INCDIR)
LDFLAGS   := -lSDL -lSDL_image

RM        := rm -f
RMDIR     := rm -rf
MKDIR     := mkdir -p
LN        := ln -fs
CAT       := cat
GREP      := grep
ECHO      := echo
CMDLOG    := @printf "  %-7s %s\n"

SOURCES   :=                \
	main.c              \
	check_parsing.c     \
	create_ipcs.c       \
	epur_str.c          \
	get_next_line.c     \
	init.c              \
	init_player.c       \
	my_getnbr.c         \
	parsing.c           \
	player_play.c       \
	pp.c                \
	pp_die.c            \
	pp_map.c            \
	pp_msq.c            \
	pp_check_target.c   \
	pp_move.c           \
	xy.c                \

OBJECTS   := $(patsubst %.c, $(OBJDIR)/%.o, $(SOURCES))
SOURCES   := $(patsubst %.c, $(SRCDIR)/%.c, $(SOURCES))

DISP_SOURCES :=        \
	aff_main.c \
	aff_pause.c \

DISP_OBJECTS := $(patsubst %.c, $(OBJDIR)/$(DISPDIR)/%.o, $(DISP_SOURCES))
DISP_SOURCES := $(patsubst %.c, $(SRCDIR)/$(DISPDIR)/%.c, $(DISP_SOURCES))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CMDLOG) 'CC' $(@:$(OBJDIR)/%=%)
	@$(GREP) -Eni '(TODO|NOTE|FIXME|XXX)' $< 2>/dev/null ; true
	@$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME) $(DISPLAYER)

$(OBJDIR):
	$(CMDLOG) 'MKDIR' $@
	@$(MKDIR) $@
	$(CMDLOG) 'MKDIR' $@/$(DISPDIR)
	@$(MKDIR) $@/$(DISPDIR)

$(NAME): $(OBJDIR) $(OBJECTS)
	$(CMDLOG) 'LINK' $(NAME)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME)

$(DISPLAYER): $(OBJDIR) $(DISP_OBJECTS)
	$(CMDLOG) 'LINK' $(DISPLAYER)
	@$(CC) $(CFLAGS) $(DISP_OBJECTS) $(LDFLAGS) -o $(DISPLAYER)

debug: CFLAGS := -W -Wall -Wextra -g3 -rdynamic -DDEBUG -I $(INCDIR)
debug: all
debug-re: fclean debug

llvm: CC := clang
llvm: all
llvm-re: fclean llvm

clean:
	$(CMDLOG) 'RM' $(OBJDIR)
	@$(RMDIR) $(OBJDIR)

fclean: clean
	$(CMDLOG) 'RM' $(NAME)
	@$(RM) $(NAME)
	$(CMDLOG) 'RM' $(DISPLAYER)
	@$(RM) $(DISPLAYER)

re: fclean all

test: debug-re
	./test.sh ./$(NAME) ./$(DISPLAYER) $(P)

test-vgd: debug-re
	./test.sh 'valgrind ./$(NAME)' ./$(DISPLAYER) $(P)

PHONY := all
PHONY += debug debug-re
PHONY += llvm llvm-re
PHONY += clean fclean re
PHONY += test test-vgd

.PHONY: $(PHONY)
