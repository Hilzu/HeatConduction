IRS = src

CCFLAGS = -pedantic -Wall -Werror -Wextra -std=c99
CC      = gcc

CLIENT = bin/HeatConduction

all: $(CLIENT)

debug: CCFLAGS += -g
debug: all

prof: CCFLAGS += -pg
prof: all

obj1 = $(patsubst %.c,%.o, $(foreach dir,$(DIRS) + src,   $(wildcard $(dir)/*.c)))

dep = $(obj1:.o=.d)
dep += $(obj2:.o=.d)
dep := $(sort $(dep))

.PHONY: all clean

$(CLIENT): $(obj1)
	$(CC) $^ $(LDLIBS) -o $@

$(dep): %.d: %.c
	$(CC) -MT "$(@:.d=.o) $@" -MM $(CCFLAGS) $< > $@

clean:
	$(RM) $(CLIENT) $(obj1) $(obj2) $(dep)

ifneq ($(MAKECMDGOALS),clean)
  include $(dep)
endif

