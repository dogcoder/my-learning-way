SOURCES:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,${SOURCES})
server:${OBJS}
	gcc $^ -o $@ -lpthread -g -I /usr/include/mysql/ -lmysqlclient
	rm $^

clean:
	rm server 
