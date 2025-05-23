#*******************************************************************************/
#* Copyright David Gil 1998-TODO                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
DATALINK_OBJ_NAME=DataLink
# component name
DATALINK_OBJ_PATH=$(PROJECT_PATH)/server/$(ABSTRACTION_COMPONENT_NAME)
# include and source paths - no need to change
DATALINK_OBJ_INCLUDE_PATH=$(DATALINK_OBJ_PATH)/include
DATALINK_OBJ_SRC_PATH=$(DATALINK_OBJ_PATH)/src

# used includes
DATALINK_INCLUDES_PATHS=$(sort	-I$(DATALINK_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(LIBRARY_COMPONENT_INCLUDES_PATHS))

DATALINK_INCLUDES=$(sort	$(DATALINK_OBJ_INCLUDE_PATH)/ABDL_$(DATALINK_OBJ_NAME).h \
									$(DATALINK_OBJ_PATH)/$(DATALINK_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(LIBRARY_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
DATALINK_SRC=$(DATALINK_OBJ_SRC_PATH)/$(DATALINK_OBJ_NAME).c
DATALINK_OUTPUT_FOLDER=$(DATALINK_OBJ_PATH)/bin
DATALINK_OBJ=$(DATALINK_OUTPUT_FOLDER)/$(DATALINK_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(DATALINK_OBJ): $(DATALINK_INCLUDES) $(DATALINK_SRC) $(COMPONENTNAME_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(DATALINK_OBJ) $(DATALINK_INCLUDES_PATHS) $(DATALINK_SRC)
