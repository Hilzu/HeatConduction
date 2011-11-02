DIRS := src
PROGRAM_DIRS := $(DIRS)

INCLUDE_DIRS := -I src
WARNINGS := -pedantic -Wall -Werror -Wextra
CC      := gcc
CCFLAGS := $(WARNINGS) -std=c99  $(INCLUDE_DIRS)
LIBS := -lpthread

PROGRAM = bin/HeatConduction

SRC := src
OBJ := obj
BIN := bin

all: dirs $(PROGRAM)

debug: CCFLAGS += -O0 -g
debug: LDLIBS += -g
debug: all

prof: CCFLAGS += -pg
prof: LDLIBS += -pg
prof: all

SRC_PROGRAM := $(foreach dir, $(PROGRAM_DIRS), $(wildcard $(dir)/*.c))

OBJ_PROGRAM := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRC_PROGRAM))

DEPFILES := $(OBJ_PROGRAM:.o=.d)
DEPFILES := $(sort $(DEPFILES))

.PHONY: all clean dirs echo

all: dirs $(PROGRAM)

$(PROGRAM): $(OBJ_PROGRAM)

$(BIN)/%:
	@echo LINK $@
	@$(CC) $^ -o $@ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c
	@echo CC $@
	@$(CC) $(CCFLAGS) -c $< -o $@
	@$(CC) $(CCFLAGS) -MM -MT "$(@:.d=.o) $@" $< > $(@:.o=.d)

clean:
	@$(RM) -rf $(PROGRAM) $(OBJ)

dirs:
	@mkdir -p $(OBJ)
	@mkdir -p $(patsubst $(SRC)/%, $(OBJ)/%, $(shell find $(PROGRAM_DIRS) -type d))

ifneq ($(MAKECMDGOALS),clean)
  -include $(DEPFILES)
endif

