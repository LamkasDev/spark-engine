CC=gcc
CC_PREFLAGS=-I./libs/include
CC_POSTFLAGS=

CC_FILE=
BUILD_COMMAND=
CLEAN_COMMAND=

ifeq ($(OS),Windows_NT)
	BUILD_COMMAND=if not exist "build" mkdir build & if not exist "build\bin" mkdir build\bin
	CLEAN_COMMAND=rd build /S /Q
	CC_FILE=./src/platforms/windows/index.c
	CC_POSTFLAGS=-L./libs/lib -lgdi32 -lopengl32 -lglfw3 -lcglm -lfreetype
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		BUILD_COMMAND=mkdir -p build/bin
		CLEAN_COMMAND=rm -rf build
		CC_FILE=./src/platforms/linux/index.c
		CC_POSTFLAGS=-L./libs/lib -lm -lz -lbz2 -ldl -lpng16 -lX11 -lGL -lglfw3 -lcglm -lfreetype -pthread
	endif
endif

spark: $(CC_FILE)
	$(BUILD_COMMAND)
	$(CC) $(CC_PREFLAGS) -c $(CC_FILE) -o ./build/spark.o
	$(CC) ./build/spark.o -o ./build/bin/spark $(CC_POSTFLAGS)
		
debug:
	$(BUILD_COMMAND)
	$(CC) $(CC_PREFLAGS) -ggdb -c $(CC_FILE) -o ./build/spark.o
	$(CC) ./build/spark.o -o ./build/bin/spark $(CC_POSTFLAGS)

clean:
	$(CLEAN_COMMAND)