#*******************************************************************************/
#* Copyright David Gil 1998-TODO                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
PROC1MAIN_OBJ_NAME=Proc1Main
# component name
PROC1MAIN_OBJ_PATH=$(PROJECT_PATH)/server/$(PROCESS1_COMPONENT_NAME)
# include and source paths - no need to change
PROC1MAIN_OBJ_INCLUDE_PATH=$(PROC1MAIN_OBJ_PATH)/include
PROC1MAIN_OBJ_SRC_PATH=$(PROC1MAIN_OBJ_PATH)/src

# used includes
PROC1MAIN_INCLUDES_PATHS=$(sort	-I$(PROC1MAIN_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(ABSTRACTION_COMPONENT_INCLUDES_PATHS))

PROC1MAIN_INCLUDES=$(sort	$(PROC1MAIN_OBJ_INCLUDE_PATH)/PRO1_$(PROC1MAIN_OBJ_NAME).h \
									$(PROC1MAIN_OBJ_PATH)/$(PROC1MAIN_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(ABSTRACTION_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
PROC1MAIN_SRC=$(PROC1MAIN_OBJ_SRC_PATH)/$(PROC1MAIN_OBJ_NAME).c
PROC1MAIN_OUTPUT_FOLDER=$(PROC1MAIN_OBJ_PATH)/bin
PROC1MAIN_OBJ=$(PROC1MAIN_OUTPUT_FOLDER)/$(PROC1MAIN_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(PROC1MAIN_OBJ): $(PROC1MAIN_INCLUDES) $(PROC1MAIN_SRC) $(PROCESS1_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(PROC1MAIN_OBJ) $(PROC1MAIN_INCLUDES_PATHS) $(PROC1MAIN_SRC)
