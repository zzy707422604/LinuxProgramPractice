src = $(wildcard *.c)
target = $(patsubst %.c, % ,$(src))

ALL:$(target)

%:%.c
	gcc $< -o $@ -pthread

clean:
	-rm -rf $(target)

.PHONY: clean ALL
