CC=gcc
CC_FILE=
PRE_CC_FLAGS=-I./libs/include
POST_CC_FLAGS=

PRE_BUILD_COMMAND=
POST_BUILD_COMMAND=
CLEAN_COMMAND=

ifeq ($(OS),Windows_NT)
	CC_FILE=./src/platforms/windows/index.c
	POST_CC_FLAGS=-L./libs/lib -lglfw3 -lgdi32 -lopengl32 -lcglm -lfreetype -lyaml

	PRE_BUILD_COMMAND=if not exist "build" mkdir build & mkdir build\bin & mkdir build\objs > NUL
	POST_BUILD_COMMAND=xcopy /E /I /Y src_data build\bin\data > NUL
	CLEAN_COMMAND=rd build /S > NUL
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CC_FILE=./src/platforms/linux/index.c
		POST_CC_FLAGS=-L./libs/lib -lm -lz -lbz2 -ldl -lpng16 -lX11 -lGL -lglfw3 -lcglm -lfreetype -lyaml -pthread

		PRE_BUILD_COMMAND=mkdir -p build/bin & mkdir -p build/objs > dev/null
		POST_BUILD_COMMAND=cp -R src_data build/bin/data > dev/null
		CLEAN_COMMAND=rm -rf build > dev/null
	endif
endif

all: build/objs/spark.o
	@echo ==========
	@echo Creating directories...
	@$(PRE_BUILD_COMMAND)
	@echo Finished!
	@echo ==========
	@echo Building...
	$(CC) $(PRE_CC_FLAGS) -o ./build/objs/spark.o -c $(CC_FILE)
	$(CC) -o ./build/bin/spark ./build/objs/spark.o $(POST_CC_FLAGS)
	@echo ==========
	@echo Copying data...
	@$(POST_BUILD_COMMAND)
	@echo Finished!
	@echo ==========

debug: PRE_CC_FLAGS+=-ggdb
debug: | all

clean:
	$(CLEAN_COMMAND)