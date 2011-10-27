DIRS = src

CXXFLAGS = -pedantic -Wall -Werror -Wextra -O3
CXX      = gcc

CLIENT = bin/HeatConduction

all: $(CLIENT)

debug: CXXFLAGS += -O3 -g
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
	$(RM) $(CLIENT) $(SERVER) $(EDITOR) $(obj1) $(obj2) $(obj4) $(dep)

ifneq ($(MAKECMDGOALS),clean)
  include $(dep)
endif

