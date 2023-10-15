DEBUG = 1

CC = gcc

CFLAGS = -isystem ./include  -Wall -Wextra -Wpedantic -Wcast-qual -Wshadow -Wpointer-arith
LFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

ifeq ($(DEBUG), 1)
	CFLAGS += -O0 -g

# Profiling
#	CFLAGS += -pg -fprofile-arcs -ftest-coverage
else
	CFLAGS += -DNDEBUG -O3 -march=native -mtune=native
endif

objects = $(patsubst %.c, %.o, $(wildcard ./src/*.c))

flappybirds: $(objects)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

./src/glad.o: ./src/glad.c ./include/glad/glad.h
	$(CC) -I ./include -O3 -march=native -mtune=native -c $< -o $@

run: flappybirds
	./flappybirds

.PHONY: clean
clean:
	$(RM) flappybirds $(objects)
