#*******************************************************************************/
#* Copyright David Gil 1998-TODO                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
QUEUE_OBJ_NAME=Queue
# component name
QUEUE_OBJ_PATH=$(PROJECT_PATH)/server/$(LIBRARY_COMPONENT_NAME)
# include and source paths - no need to change
QUEUE_OBJ_INCLUDE_PATH=$(QUEUE_OBJ_PATH)/include
QUEUE_OBJ_SRC_PATH=$(QUEUE_OBJ_PATH)/src

# used includes
QUEUE_INCLUDES_PATHS=$(sort	-I$(QUEUE_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(SOMETHING_INCLUDES_PATHS))

QUEUE_INCLUDES=$(sort	$(QUEUE_OBJ_INCLUDE_PATH)/LIB_$(QUEUE_OBJ_NAME).h \
									$(QUEUE_OBJ_PATH)/$(QUEUE_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(SOMETHING_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
QUEUE_SRC=$(QUEUE_OBJ_SRC_PATH)/$(QUEUE_OBJ_NAME).c
QUEUE_OUTPUT_FOLDER=$(QUEUE_OBJ_PATH)/bin
QUEUE_OBJ=$(QUEUE_OUTPUT_FOLDER)/$(QUEUE_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(QUEUE_OBJ): $(QUEUE_INCLUDES) $(QUEUE_SRC) $(LIBRARY_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(QUEUE_OBJ) $(QUEUE_INCLUDES_PATHS) $(QUEUE_SRC)
