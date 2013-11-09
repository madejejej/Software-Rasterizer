LDFLAGS = -L/usr/local/lib -lallegro -lallegro_main 
IFLAGS = -I/usr/local/include
_OBJS = main.o screen.o
OBJS = $(patsubst %,build/%,$(_OBJS))

all: $(OBJS) 
	gcc -g -o build/main $(OBJS) $(LDFLAGS) 
	
build/%.o: src/%.c
	gcc -c -g -o $@ $< $(IFLAGS)

clean:
	rm -f build/*.o
