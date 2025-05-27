#------------------------------------------------------------------------------#
# Copyright David Gil 1998-2025                                                #
# 								                                               #
# davidgil@dgadv.com 			                                               #
#------------------------------------------------------------------------------#
PROJECT_PATH=$(shell pwd)
FECMAIN_OUTPUT_FOLDER=$(PROJECT_PATH)/bin
FECMAIN_LIB_NAME=fec.so
FECMAIN_LIB=$(FECMAIN_OUTPUT_FOLDER)/$(FECMAIN_LIB_NAME)
COMMON_INCLUDES_PATHS=-I$(PROJECT_PATH)/include
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
include ./lib/nullRadio/nullRadio.mk
# library
include ./lib/library/library.mk
# missson
include ./lib/gndPackets/gndPackets.mk
include ./lib/fswPackets/fswPackets.mk
# application
include ./lib/fecEssentials/fecEssentials.mk
include ./lib/fecCommandsDefinitions/fecCommandsDefinitions.mk


#------------------------------------------------------------------------------#							
# compile

FECMAIN_COMPONENT_OBJ=	$(FECESSENTIALS_COMPONENT_OBJ) \
						$(NULLRADIO_COMPONENT_OBJ) \
						$(FSWPACKETS_COMPONENT_OBJ) \
						$(GNDPACKETS_COMPONENT_OBJ) \
						$(LIBRARY_COMPONENT_OBJ)

FECMAIN_COMPONENT_INCLUDES= 	$(sort $(FECESSENTIALS_COMPONENT_INCLUDES))


$(FECMAIN_OUTPUT_FOLDER):
	mkdir -p $@
	
$(FECMAIN_LIB): $(FECMAIN_OUTPUT_FOLDER) $(FECMAIN_COMPONENT_OBJ)
	$(CC) $(LDFLAGS) -shared -o $@ $(FECMAIN_COMPONENT_OBJ)

#------------------------------------------------------------------------------#							
# executable	NO NEED TO CHANGE ANYTHING APART FROM SEARCH AND REPLACE
#--------------------------------------------------------------------------------
# includes and objects 
MAIN_INCLUDES_PATHS=$(sort 	$(COMMON_INCLUDES_PATHS) \
							$(FECESSENTIALS_COMPONENT_INCLUDES_PATHS)\
							$(FECCOMMANDSDEFINITIONS_COMPONENT_INCLUDES_PATHS))
							
	#--------------------------------------------------------------------------------
	# NO NEED TO CHANGE ANYTHING APART FROM SEARCH AND REPLACE AND LIBRARIES
							
MAIN_INCLUDES=		$(sort 	$(COMMON_INCLUDES) \
							Makefile \
							$(FECMAIN_COMPONENT_INCLUDES)\
							$(FECCOMMANDSDEFINITIONS_COMPONENT_INCLUDES))

MAIN_OBJECTS=		$(FECMAIN_COMPONENT_OBJ) \
					$(FECCOMMANDSDEFINITIONS_COMPONENT_OBJ)

MAIN_OBJ_NAME=main
MAIN_OBJ_PATH=$(PROJECT_PATH)
MAIN_SRC=$(MAIN_OBJ_PATH)/$(MAIN_OBJ_NAME).c
MAIN_OUTPUT_FOLDER=$(MAIN_OBJ_PATH)/bin
MAIN_OBJ=$(MAIN_OUTPUT_FOLDER)/$(MAIN_OBJ_NAME).o
MAIN_EXE=$(MAIN_OUTPUT_FOLDER)/$(MAIN_OBJ_NAME).exe
MAIN_LIBS=-lrt -lpthread -lm -lmysqlclient#-L/usr/local/lib/dgl -ldglGauges -ldglRenderWrapper -ldgUtils -lGL -lglut -lGLU  -lgomp 

$(MAIN_OBJ): $(MAIN_INCLUDES) $(MAIN_SRC) | $(MAIN_OUTPUT_FOLDER) $(MAIN_OUTPUT_FOLDERS)
	$(CC) $(CFLAGS) -o $(MAIN_OBJ) $(MAIN_INCLUDES_PATHS) $(MAIN_SRC)
	
$(MAIN_EXE): $(MAIN_OBJ) $(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(MAIN_OBJ) $(MAIN_OBJECTS) $(MAIN_LIBS)

removeSurrogates:
	rm -rf ./lib/fswPackets
	rm -rf ./lib/library
	rm -rf ./lib/nullRadio
	
copySurrogates: removeSurrogates
	cp -R ../onboard/lib/fswPackets ./lib/
	cp -R ../onboard/lib/library ./lib/
	cp -R ../simulators/nullRadio ./lib/
	
cleanSurrogates:
	rm -rf $(NULLRADIO_COMPONENT_OBJ)
	rm -rf $(LIBRARY_COMPONENT_OBJ)
	rm -rf $(FSWPACKETS_COMPONENT_OBJ)

compile: copySurrogates cleanSurrogates $(FECMAIN_LIB) $(MAIN_EXE)

run: compile
	$(MAIN_EXE)

#export LD_LIBRARY_PATH=/usr/local/lib/dgl; $(MAIN_EXE)
		
clean: copySurrogates
	rm -rf $(FECMAIN_OUTPUT_FOLDER)
	rm -rf $(FECCOMMANDSDEFINITIONS_COMPONENT_OUTPUT_FOLDER)
	rm -rf $(FECMAIN_COMPONENT_OBJ)

all: compile


	
	