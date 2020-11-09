CFLAGS ?= -g -O2 -std=c11 -Wall -Wextra -Wvla -Wconversion -Wfloat-conversion -Wbad-function-cast
LDLIBS := -lm

# Usar POSIX.2008-1 como default.
CPPFLAGS := -D_POSIX_C_SOURCE=200809L

cachesim: cachesim.o

clean:
	rm -f cachesim *.o core

.PHONY: clean