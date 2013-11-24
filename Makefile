LDFLAGS = -L/usr/local/lib -lallegro -lallegro_main -lm
IFLAGS = -I/usr/local/include
SRC = src/%.c 
_OBJS = main.o screen.o rasterizer.o bitmap.o types.o
OBJS = $(patsubst %,build/%,$(_OBJS))

all: $(OBJS) 
	gcc -g -o build/main $(OBJS) $(LDFLAGS) 
	

build/rasterizer.o: src/rasterizer/rasterizer.c
	gcc -c -g -o $@ $< $(IFLAGS)

build/%.o: $(SRC)
	gcc -c -g -o $@ $< $(IFLAGS)


clean:
	rm -f build/*.o
