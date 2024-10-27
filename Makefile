CC=clang

INCLUDE=-Iinclude
DEBUG=-fsanitize=address,undefined -g3
LIBS=-lraylib

OPTIONS=-Wall -Wextra -Werror -Wno-unused-parameter
OPTIONS_WEB=-I$(RAYLIB_SRC) -L$(RAYLIB_SRC) -sUSE_GLFW=3 -sGL_ENABLE_GET_PROC_ADDRESS -DPLATFORM_WEB 

SOURCES := $(shell find src -name '*.c')

OUT_DEBUG=out/debug
OUT_RELEASE=out/release
BINARY=connections

# TODO: Web (hi lily)

debug:
	mkdir -p $(OUT_DEBUG)
	cp -r assets $(OUT_DEBUG)/assets

	$(CC) $(INCLUDE) $(OPTIONS) $(LIBS) $(DEBUG) $(SOURCES) -o $(OUT_DEBUG)/$(BINARY)


release:	
	mkdir -p $(OUT_RELEASE)
	cp -r assets $(OUT_RELEASE)/assets

	$(CC) $(INCLUDE) $(OPTIONS) $(LIBS) $(SOURCES) -o $(OUT_RELEASE)/$(BINARY)


clean:
	rm -rf out