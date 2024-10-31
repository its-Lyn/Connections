CC=clang
EMCC=emcc

INCLUDE=-Iinclude
DEBUG=-fsanitize=address,undefined -g3
LIBS=-lraylib -lm

OPTIONS=-Wall -Wextra -Werror -Wno-unused-parameter
OPTIONS_WEB=-I$(RAYLIB_SRC) -L$(RAYLIB_SRC) -sUSE_GLFW=3 -sGL_ENABLE_GET_PROC_ADDRESS -DPLATFORM_WEB --preload-file assets

SOURCES := $(shell find src -name '*.c')

SHELL_FILE=shell.html

TARGET ?= desktop

OUT_DEBUG=out/$(TARGET)/debug
OUT_RELEASE=out/$(TARGET)/release
BINARY=connections

debug:
	# deleting output directory if it already exists
	if test -d $(OUT_DEBUG); then\
		rm -r $(OUT_DEBUG);\
	fi

	mkdir -p $(OUT_DEBUG)


ifeq ($(TARGET), desktop)
	cp -r assets $(OUT_DEBUG)/assets
	$(CC) $(OPTIONS) $(DEBUG) $(SOURCES) $(LIBS) $(INCLUDE) -o $(OUT_DEBUG)/$(BINARY)
else ifeq ($(TARGET), web)
	$(EMCC) $(OPTIONS) $(OPTIONS_WEB) $(DEBUG) $(SOURCES) $(LIBS) $(INCLUDE) -o $(OUT_DEBUG)/index.html
else
	@echo Invalid platform!
endif


release:
	# deleting output directory if it already exists
	if test -d $(OUT_RELEASE); then\
		rm -r $(OUT_RELEASE);\
	fi

	mkdir -p $(OUT_RELEASE)

ifeq ($(TARGET), desktop)
	cp -r assets $(OUT_RELEASE)/assets
	$(CC) $(OPTIONS) $(SOURCES) $(LIBS) $(INCLUDE) -o $(OUT_RELEASE)/$(BINARY)
else ifeq ($(TARGET), web)
	$(EMCC) $(OPTIONS) $(OPTIONS_WEB) $(SOURCES) $(LIBS) $(INCLUDE) -o $(OUT_RELEASE)/index.html --shell-file $(SHELL_FILE)
else
	@echo Invalid platform!
endif


clean:
	rm -rf out

