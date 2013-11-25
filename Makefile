LDFLAGS = -L/usr/local/lib -lallegro -lallegro_main -lm
IFLAGS = -I/usr/local/include
SRC = src/%.c 
_OBJS = main.o screen.o rasterizer.o bitmap.o types.o matrix.o transformations.o scene_file.o scene.o matrix_stack.o viewTransformations.o
OBJS = $(patsubst %,build/%,$(_OBJS))

all: $(OBJS) 
	gcc -g -o build/main $(OBJS) $(LDFLAGS) 
	

build/scene.o: src/scene/scene.c
	gcc -c -g -o $@ $< $(IFLAGS)

build/scene_file.o: src/scene/scene_file.c
	gcc -c -g -o $@ $< $(IFLAGS)

build/rasterizer.o: src/rasterizer/rasterizer.c
	gcc -c -g -o $@ $< $(IFLAGS)
		
build/matrix_stack.o: src/matrix/matrix_stack.c
	gcc -c -g -o $@ $< $(IFLAGS)

build/matrix.o: src/matrix/matrix.c
	gcc -c -g -o $@ $< $(IFLAGS)

build/viewTransformations.o: src/transformations/viewTransformations.c
	gcc -c -g -o $@ $< $(IFLAGS)


build/transformations.o: src/transformations/transformations.c
	gcc -c -g -o $@ $< $(IFLAGS)

build/%.o: $(SRC)
	gcc -c -g -o $@ $< $(IFLAGS)

clean:
	rm -f build/*.o
