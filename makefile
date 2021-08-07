CC=gcc
CC_DEBUG_PREFLAGS=-I./libs/include
CC_PREFLAGS=-I./libs/include
CC_POSTFLAGS=-L./libs/lib -lglfw3 -lgdi32 -lopengl32 -lcglm
CC_FILE=./src/platforms/windows/index.c

BUILD_COMMAND=if not exist "build" mkdir build & if not exist "build\bin" mkdir build\bin
CLEAN_COMMAND=rd build /S /Q

spark: $(CC_FILE)
	$(BUILD_COMMAND)
	$(CC) $(CC_PREFLAGS) -c $(CC_FILE) -o ./build/spark.o
	$(CC) ./build/spark.o -o ./build/bin/spark $(CC_POSTFLAGS)
		
debug:
	$(BUILD_COMMAND)
	$(CC) $(CC_DEBUG_PREFLAGS) -ggdb -c $(CC_FILE) -o ./build/spark.o
	$(CC) ./build/spark.o -o ./build/bin/spark $(CC_POSTFLAGS)

clean:
	$(CLEAN_COMMAND)