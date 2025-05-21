#------------------------------------------------------------------------------#
# Copyright David Gil 1998-TODO                                                #
# 								                                               #
# davidgil@dgadv.com 			                                               #
#------------------------------------------------------------------------------#
PROJECT_PATH=$(shell pwd)
SERVER_OUTPUT_FOLDER=$(PROJECT_PATH)/bin
SERVER_LIB_NAME=server.so
SERVER_LIB=$(SERVER_OUTPUT_FOLDER)/$(SERVER_LIB_NAME)
COMMON_INCLUDES_PATHS=-I$(PROJECT_PATH)/server/include
#COMMON_INCLUDES_PATHS=-I/usr/local/include/dgl

#--------------------------------------------------------------------------------
# project set-up
CC=gcc
CFLAGS=-Wall -c -fpic -fopenmp
LDFLAGS=-Wall 
AR=ar
TARGET=$(shell uname -m)
#--------------------------------------------------------------------------------
# project components
# IO 
# TODO include ./lib/nullRadio/nullRadio.mk
include ./server/abstraction/abstraction.mk
# library
include ./server/library/library.mk
# core
include ./server/core/core.mk
# mission
# TODO include ./lib/gndPackets/gndPackets.mk
# TODO include ./lib/fswPackets/fswPackets.mk
# application
include ./server/swBus/swBus.mk
include ./server/application1/application1.mk
# TODO include ./lib/serverEssentials/serverEssentials.mk
# TODO include ./lib/serverCommandsDefinitions/serverCommandsDefinitions.mk


#------------------------------------------------------------------------------#							
# compile

SERVER_COMPONENT_OBJ=	$(CORE_COMPONENT_OBJ) \
						$(ABSTRACTION_COMPONENT_OBJ)\
						$(APPLICATION1_COMPONENT_OBJ) \
						$(SWBUS_COMPONENT_OBJ) \
						$(LIBRARY_COMPONENT_OBJ)
						

SERVER_COMPONENT_INCLUDES=	$(CORE_COMPONENT_INCLUDES) \
							$(ABSTRACTION_COMPONENT_INCLUDES) \


$(SERVER_OUTPUT_FOLDER):
	mkdir -p $@
	
$(SERVER_LIB): $(SERVER_OUTPUT_FOLDER) $(SERVER_COMPONENT_OBJ)
	$(CC) $(LDFLAGS) -shared -o $@ $(SERVER_COMPONENT_OBJ)

#------------------------------------------------------------------------------#							
# executable	NO NEED TO CHANGE ANYTHING APART FROM SEARCH AND REPLACE
#--------------------------------------------------------------------------------
# includes and objects 
SERVER_MAIN_INCLUDES_PATHS=$(sort 	$(COMMON_INCLUDES_PATHS) \
							$(CORE_COMPONENT_INCLUDES_PATHS) \
							$(ABSTRACTION_COMPONENT_INCLUDES_PATHS))
							
	#--------------------------------------------------------------------------------
	# NO NEED TO CHANGE ANYTHING APART FROM SEARCH AND REPLACE AND LIBRARIES
							
SERVER_MAIN_INCLUDES=		$(sort 	$(COMMON_INCLUDES) \
							Makefile \
							$(SERVER_COMPONENT_INCLUDES)\
							$(SERVER_COMMANDSDEFINITIONS_COMPONENT_INCLUDES))

SERVER_MAIN_OBJECTS=		$(SERVER_COMPONENT_OBJ) \
					$(SERVER_COMMANDSDEFINITIONS_COMPONENT_OBJ)

SERVER_MAIN_OBJ_NAME=server
SERVER_MAIN_OBJ_PATH=$(PROJECT_PATH)
SERVER_MAIN_SRC=$(SERVER_MAIN_OBJ_PATH)/$(SERVER_MAIN_OBJ_NAME).c
SERVER_MAIN_OUTPUT_FOLDER=$(SERVER_MAIN_OBJ_PATH)/bin
SERVER_MAIN_OBJ=$(SERVER_MAIN_OUTPUT_FOLDER)/$(SERVER_MAIN_OBJ_NAME).o
SERVER_MAIN_EXE=$(SERVER_MAIN_OUTPUT_FOLDER)/$(SERVER_MAIN_OBJ_NAME).exe
SERVER_MAIN_LIBS=-lrt -lpthread -lm #-L/usr/local/lib/dgl -ldglGauges -ldglRenderWrapper -ldgUtils -lGL -lglut -lGLU  -lgomp 

$(SERVER_MAIN_OBJ): $(SERVER_MAIN_INCLUDES) $(SERVER_MAIN_SRC) | $(SERVER_MAIN_OUTPUT_FOLDER) $(SERVER_MAIN_OUTPUT_FOLDERS)
	$(CC) $(CFLAGS) -o $(SERVER_MAIN_OBJ) $(SERVER_MAIN_INCLUDES_PATHS) $(SERVER_MAIN_SRC)
	
$(SERVER_MAIN_EXE): $(SERVER_MAIN_OBJ) $(SERVER_MAIN_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(SERVER_MAIN_OBJ) $(SERVER_MAIN_OBJECTS) $(SERVER_MAIN_LIBS)


#TODO compile: $(SERVER_LIB) $(SERVER_MAIN_EXE)
compile: $(SERVER_MAIN_EXE)

run: compile
	$(SERVER_MAIN_EXE)

#export LD_LIBRARY_PATH=/usr/local/lib/dgl; $(SERVER_MAIN_EXE)
		
clean: 
	rm -rf $(SERVER_OUTPUT_FOLDER)
	rm -rf $(SERVER_COMMANDSDEFINITIONS_COMPONENT_OUTPUT_FOLDER)
	rm -rf $(SERVER_COMPONENT_OBJ)

all: compile


	
	