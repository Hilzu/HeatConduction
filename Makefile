IRS = src

CCFLAGS = -pedantic -Wall -Werror -Wextra -std=c99
CC      = gcc

PROGRAM = bin/HeatConduction

all: $(PROGRAM)

debug: CCFLAGS += -g
debug: all

prof: CCFLAGS += -pg
prof: all

obj1 = $(patsubst %.c,%.o, $(foreach dir,$(DIRS) + src,   $(wildcard $(dir)/*.c)))

dep = $(obj1:.o=.d)
dep += $(obj2:.o=.d)
dep := $(sort $(dep))

.PHONY: all clean

$(PROGRAM): $(obj1)
	$(CC) $^ $(LDLIBS) -o $@

$(dep): %.d: %.c
	$(CC) -MT "$(@:.d=.o) $@" -MM $(CCFLAGS) $< > $@

clean:
	$(RM) $(PROGRAM) $(obj1) $(obj2) $(dep)

ifneq ($(MAKECMDGOALS),clean)
  include $(dep)
endif

