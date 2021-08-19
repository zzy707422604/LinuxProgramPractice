src = $(wildcard *.c) #./src/add.c sub.c div1.c hello.c
obj = $(patsubst %.c, %, $(src)) #/obj/add.o sub.o div1.o hello.o
CFLAGS = -g
ALL:$(target)

%:%.c
	gcc $< -o $@

clean:
	-rm -rf $(target)
.PHONY:clean ALL
