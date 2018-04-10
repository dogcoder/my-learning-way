SOURCES:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,${SOURCES})
server:${OBJS}
	gcc $^ -o $@ -lpthread -g
	rm $^

clean:
	rm server 
