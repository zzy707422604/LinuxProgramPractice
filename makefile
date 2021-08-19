src = $(wildcard *.c)
target = $(patsubst %.c, % ,$(src))

ALL:$(target)

%:%.c
	gcc -D_GNU_SOURCE -lpthread $< -o $@

clean:
	-rm -rf $(target)

.PHONY: clean ALL
