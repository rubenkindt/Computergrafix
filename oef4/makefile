#-*-makefile-*-

TARGETS = \
    staaf

all All: $(TARGETS)

################################################################################
INCPATH = -I/usr/local/include
LIBPATH = -L. -L/usr/local/lib/hpux32
LIBS = -lglut -lGLU -lGL -lGLw -lXt -lXext -lX11 -ljpeg -lm 
DEBUGFLAGS = +O3
CFLAGS = +DD32 $(DEBUGFLAGS) $(INCPATH)


SRCS = \
	cub.c

OBJS = $(SRCS:.c=.o)

.SUFFIXES:	.c

.c.o:	
	cc -c $< $(CFLAGS)


staaf:  clean $(OBJS)
	LDOPTS= \
	cc -o cub $(CFLAGS) $(OBJS) $(LIBPATH) $(LIBS) 

clean:
	rm -f cub $(OBJS) core

print:
	listing $(SRCS)
