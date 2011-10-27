DIRS = src

CXXFLAGS = -pedantic -Wall -Werror -Wextra -std=c99
CXX      = gcc

CLIENT = bin/HeatConduction

all: $(CLIENT)

debug: CXXFLAGS += -g
debug: all

prof: CXXFLAGS += -pg
prof: all

obj1 = $(patsubst %.c,%.o, $(foreach dir,$(DIRS) + src,   $(wildcard $(dir)/*.c)))

dep = $(obj1:.o=.d)
dep += $(obj2:.o=.d)
dep := $(sort $(dep))

.PHONY: all clean

$(CLIENT): $(obj1)
	$(CXX) $^ $(LDLIBS) -o $@

$(dep): %.d: %.c
	$(CXX) -MT "$(@:.d=.o) $@" -MM $(CXXFLAGS) $< > $@

clean:
	$(RM) $(CLIENT) $(obj1) $(obj2) $(dep)

ifneq ($(MAKECMDGOALS),clean)
  include $(dep)
endif

