NAME_SERVER = Server
NAME_CLIENT = EletroChat


CC = gcc
CFLAGS = -Wall -Wextra -g
# Put libs; LIBS =

SRCS_SERVER = server/src/auxfuncs.c server/src/main.c server/src/threadfuncs.c
OBJ_SERVER =  server/obj/auxfuncs.o server/obj/main.o server/obj/threadfuncs.o
HDRS_SERVER = server/hdr/auxfuncs.h server/hdr/threadfuncs.h

SRCS_CLI = 
OBJ_CLI = 
HDRS_CLI = 

compile_server: $(NAME_SERVER)
	$(CC) $(OBJ_SERVER) -o $(NAME_SERVER)

compile_client: $(NAME_CLIENT)
	$(CC) $(OBJ_CLI) -o $(NAME_CLIENT)

run_server:
	source .env && ./Server

run_client:
	./EletroChat

clean_server:
	rm -f server/obj/*.o Server

clean_client:
	rm -f client/obj/*.o EletroChat


.PHONY: compile_client compile_server run_client run_server clean_client clean_server 