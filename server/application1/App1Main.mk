#*******************************************************************************/
#* Copyright David Gil 1998-TODO                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
APP1MAIN_OBJ_NAME=App1Main
# component name
APP1MAIN_OBJ_PATH=$(PROJECT_PATH)/server/$(APPLICATION1_COMPONENT_NAME)
# include and source paths - no need to change
APP1MAIN_OBJ_INCLUDE_PATH=$(APP1MAIN_OBJ_PATH)/include
APP1MAIN_OBJ_SRC_PATH=$(APP1MAIN_OBJ_PATH)/src

# used includes
APP1MAIN_INCLUDES_PATHS=$(sort	-I$(APP1MAIN_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(ABSTRACTION_COMPONENT_INCLUDES_PATHS) \
									$(SWBUS_COMPONENT_INCLUDES_PATHS))

APP1MAIN_INCLUDES=$(sort	$(APP1MAIN_OBJ_INCLUDE_PATH)/APP1_$(APP1MAIN_OBJ_NAME).h \
									$(APP1MAIN_OBJ_PATH)/$(APP1MAIN_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(ABSTRACTION_COMPONENT_INCLUDES)\
									$(SWBUS_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
APP1MAIN_SRC=$(APP1MAIN_OBJ_SRC_PATH)/$(APP1MAIN_OBJ_NAME).c
APP1MAIN_OUTPUT_FOLDER=$(APP1MAIN_OBJ_PATH)/bin
APP1MAIN_OBJ=$(APP1MAIN_OUTPUT_FOLDER)/$(APP1MAIN_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(APP1MAIN_OBJ): $(APP1MAIN_INCLUDES) $(APP1MAIN_SRC) $(PROCESS1_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(APP1MAIN_OBJ) $(APP1MAIN_INCLUDES_PATHS) $(APP1MAIN_SRC)
