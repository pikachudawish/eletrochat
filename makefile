SERVER = Server
CLIENT = EletroChat


CC = gcc
CFLAGS_S = -Wall -Wextra -Iserver/hdr -g
CFLAGS_C = -Wall -Wextra -Iclient/hdr -g
LIBS_S = -lmysqlclient
LIBS_C = 

SRC_SERVER = \
	server/src/globalvar.c \
	server/src/dbfuncs.c \
	server/src/main.c \
	server/src/serverfuncs.c \
	server/src/cli_linkedlist_funcs.c \
	server/src/threads/dbthread.c \
	server/src/threads/sendpkgthread.c \
	server/src/threads/serverthread.c

OBJ_SERVER = \
	server/obj/globalvar.o \
	server/obj/dbfuncs.o \
	server/obj/main.o \
	server/obj/serverfuncs.o \
	server/obj/cli_linkedlist_funcs.o \
	server/obj/threads/dbthread.o \
	server/obj/threads/sendpkgthread.o \
	server/obj/threads/serverthread.o

#SRCS_CLI = 
#OBJ_CLI = 

all: compile_server compile_client

compile_server: $(SERVER)
	
$(SERVER): $(OBJ_SERVER)	
	$(CC) $(OBJ_SERVER) $(LIBS_S) -o $(SERVER)

server/obj:
	mkdir -p server/obj

server/obj/threads:
	mkdir -p server/obj/threads

server/obj/%.o: server/src/%.c | server/obj
	$(CC) $(CFLAGS_S) -c $< -o $@

server/obj/threads/%.o: server/src/threads/%.c | server/obj/threads
	$(CC) $(CFLAGS_S) -c $< -o $@

compile_client: $(CLIENT)

$(CLIENT): $(OBJ_CLI)	
	$(CC) $(OBJ_CLI) -o $(CLIENT)

client/obj:
	mkdir -p client/obj

client/obj/%.o: client/src/%.c | client/obj
	$(CC) $(CFLAGS_C) -c $< -o $@

run_server:
	/bin/sh -c 'source ./.env && ./Server'

run_client:
	./$(CLIENT)

clean: clean_client clean_server

clean_server:
	rm -rf server/obj/threads/*.o
	rmdir server/obj/threads
	rm -rf server/obj/*.o 
	rmdir server/obj
	rm -f $(SERVER)

clean_client:
	rm -rf client/obj/*.o 
	rmdir -f client/obj
	rm -f $(CLIENT) 

.PHONY: all clean compile_client compile_server run_client run_server clean_client clean_server