BIN_FILES  = cliente servidor 

CC = gcc

CPPFLAGS = -I$(INSTALL_PATH)/include -Wall

LDFLAGS = -L$(INSTALL_PATH)/lib/
LDLIBS = -lpthread -lrt -static -lm

all: $(BIN_FILES)
.PHONY : all


cliente: cliente.o clave.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@ 

servidor: servidor.o servicios.o servicios_help.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ 

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	rm -f $(BIN_FILES) *.o

.SUFFIXES:
.PHONY : clean

