PROG = regilo
SOURCES = ${PROG}.cpp mongoose.c

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

${PROG}: ${PROG}.cpp
	${CC} ${CFLAGS} -o ${PROG} ${SOURCES} ${LIBS}

clean:
	rm ${PROG}
