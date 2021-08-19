src = $(wildcard *.c) #./src/add.c sub.c div1.c hello.c
obj = $(patsubst %.c, %, $(src)) #/obj/add.o sub.o div1.o hello.o
CFLAGS = -g
ALL:$(obj)

%:%.c
	gcc $< -o $@

clean:
	-rm -rf $(obj)
.PHONY:clean ALL
