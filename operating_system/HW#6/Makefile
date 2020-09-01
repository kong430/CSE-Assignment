TARGET = a b

all: $(TARGET)

a: a.c
	gcc -o a a.c -lpthread

b: b.c
	gcc -o b b.c -lpthread
clean:
	rm $(TARGET)
