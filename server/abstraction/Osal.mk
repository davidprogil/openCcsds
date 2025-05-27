#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
OSAL_OBJ_NAME=Osal
# component name
OSAL_OBJ_PATH=$(PROJECT_PATH)/server/$(ABSTRACTION_COMPONENT_NAME)
# include and source paths - no need to change
OSAL_OBJ_INCLUDE_PATH=$(OSAL_OBJ_PATH)/include
OSAL_OBJ_SRC_PATH=$(OSAL_OBJ_PATH)/src

# used includes
OSAL_INCLUDES_PATHS=$(sort	-I$(OSAL_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(SOMETHING_INCLUDES_PATHS))

OSAL_INCLUDES=$(sort	$(OSAL_OBJ_INCLUDE_PATH)/ABOS_$(OSAL_OBJ_NAME).h \
									$(OSAL_OBJ_PATH)/$(OSAL_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(SOMETHING_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
OSAL_SRC=$(OSAL_OBJ_SRC_PATH)/$(OSAL_OBJ_NAME).c
OSAL_OUTPUT_FOLDER=$(OSAL_OBJ_PATH)/bin
OSAL_OBJ=$(OSAL_OUTPUT_FOLDER)/$(OSAL_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(OSAL_OBJ): $(OSAL_INCLUDES) $(OSAL_SRC) $(ABSTRACTION_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(OSAL_OBJ) $(OSAL_INCLUDES_PATHS) $(OSAL_SRC)
