BIN_FILES  = claves.o cliente servidor 

CC = gcc

CPPFLAGS = -I$(INSTALL_PATH)/include -Wall

LDFLAGS = -L.
LDLIBS = -lpthread -lrt -lm

all: $(BIN_FILES)
.PHONY : all

claves.o: claves.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ -fPIC
	$(CC) $(CPPFLAGS) $(CFLAGS) -shared $< -o libclaves.so -fPIC

cliente: cliente.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@ -lclaves 

servidor: servidor.o servicios.o servicios_help.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ 

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	rm -f $(BIN_FILES) *.o *.so

.PHONY : clean
