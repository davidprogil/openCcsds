#*******************************************************************************/
#* Copyright David Gil 1998-TODO                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
TEMPLATE_OBJ_NAME=Template
# component name
TEMPLATE_OBJ_PATH=$(PROJECT_PATH)/lib/$(COMPONENTNAME_COMPONENT_NAME)
# include and source paths - no need to change
TEMPLATE_OBJ_INCLUDE_PATH=$(TEMPLATE_OBJ_PATH)/include
TEMPLATE_OBJ_SRC_PATH=$(TEMPLATE_OBJ_PATH)/src

# used includes
TEMPLATE_INCLUDES_PATHS=$(sort	-I$(TEMPLATE_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(SOMETHING_INCLUDES_PATHS))

TEMPLATE_INCLUDES=$(sort	$(TEMPLATE_OBJ_INCLUDE_PATH)/CMPN_$(TEMPLATE_OBJ_NAME).h \
									$(TEMPLATE_OBJ_PATH)/$(TEMPLATE_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(SOMETHING_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
TEMPLATE_SRC=$(TEMPLATE_OBJ_SRC_PATH)/$(TEMPLATE_OBJ_NAME).c
TEMPLATE_OUTPUT_FOLDER=$(TEMPLATE_OBJ_PATH)/bin
TEMPLATE_OBJ=$(TEMPLATE_OUTPUT_FOLDER)/$(TEMPLATE_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(TEMPLATE_OBJ): $(TEMPLATE_INCLUDES) $(TEMPLATE_SRC) $(COMPONENTNAME_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(TEMPLATE_OBJ) $(TEMPLATE_INCLUDES_PATHS) $(TEMPLATE_SRC)
