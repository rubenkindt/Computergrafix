#-*-makefile-*-

TARGETS = \
    rad

all All: $(TARGETS)

################################################################################
INCPATH = -I/usr/local/include
LIBPATH = -L. -L/usr/local/lib/hpux32
LIBS = -lglut -lGLU -lGL -lGLw -lXt -lXext -lX11 -ljpeg -lm 
DEBUGFLAGS = +O3
CFLAGS = +DD32 $(DEBUGFLAGS) $(INCPATH)


SRCS = \
	rad.c

OBJS = $(SRCS:.c=.o)

.SUFFIXES:	.c

.c.o:	
	cc -c $< $(CFLAGS)


rad:  clean $(OBJS)
	LDOPTS= \
	cc -o rad $(CFLAGS) $(OBJS) ../../jpeg/InitJPG.o $(LIBPATH) $(LIBS) 

clean:
	#rm -f rad $(OBJS) core

print:
	listing $(SRCS)
