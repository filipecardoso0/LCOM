# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/drivers/graphic/src
.PATH: ${.CURDIR}/drivers/kbd/src
.PATH: ${.CURDIR}/drivers/timer/src
.PATH: ${.CURDIR}/lib/model/src
.PATH: ${.CURDIR}/lib/controller/src
.PATH: ${.CURDIR}/lib/view/src
.PATH: ${.CURDIR}/lib/state/src
.PATH: ${.CURDIR}/utils/src

# source code files to be compiled
SRCS = proj.c graphic.c kbd.c timer.c snake_model.c position.c xpm.c utils.c board_model.c wall_model.c board_view.c snake_view.c wall_view.c
IPATHS = -I./drivers/graphic/include -I./drivers/kbd/include -I./drivers/timer/include -I./lib/model/src -I./drivers/utils/src -I./lib/view/src

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic ${IPATHS}

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
