BIN_FILES  = clave.o cliente servidor 

CC = gcc

CPPFLAGS = -I$(INSTALL_PATH)/include -Wall

LDFLAGS = -L$(INSTALL_PATH)/lib/
LDLIBS = -lpthread -lrt -static -lm

all: $(BIN_FILES)
.PHONY : all

cliente: cliente.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@ -lclave 

clave.o: clave.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ -fPIC
	$(CC) $(CPPFLAGS) $(CFLAGS) -shared $< -o libclave.so -fPIC

servidor: servidor.o servicios.o servicios_help.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ 

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	rm -f $(BIN_FILES) *.o *.so

.PHONY : clean
