#*******************************************************************************/
#* Copyright David Gil 1998-TODO                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
MAESTRO_OBJ_NAME=Maestro
# component name
MAESTRO_OBJ_PATH=$(PROJECT_PATH)/server/$(CORE_COMPONENT_NAME)
# include and source paths - no need to change
MAESTRO_OBJ_INCLUDE_PATH=$(MAESTRO_OBJ_PATH)/include
MAESTRO_OBJ_SRC_PATH=$(MAESTRO_OBJ_PATH)/src

# used includes
MAESTRO_INCLUDES_PATHS=$(sort	-I$(MAESTRO_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(ABSTRACTION_COMPONENT_INCLUDES_PATHS) \
									$(PROCESS1_COMPONENT_INCLUDES_PATHS))

MAESTRO_INCLUDES=$(sort	$(MAESTRO_OBJ_INCLUDE_PATH)/CORE_$(MAESTRO_OBJ_NAME).h \
									$(MAESTRO_OBJ_PATH)/$(MAESTRO_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(ABSTRACTION_COMPONENT_INCLUDES)\
									$(PROCESS1_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
MAESTRO_SRC=$(MAESTRO_OBJ_SRC_PATH)/$(MAESTRO_OBJ_NAME).c
MAESTRO_OUTPUT_FOLDER=$(MAESTRO_OBJ_PATH)/bin
MAESTRO_OBJ=$(MAESTRO_OUTPUT_FOLDER)/$(MAESTRO_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(MAESTRO_OBJ): $(MAESTRO_INCLUDES) $(MAESTRO_SRC) $(CORE_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(MAESTRO_OBJ) $(MAESTRO_INCLUDES_PATHS) $(MAESTRO_SRC)
