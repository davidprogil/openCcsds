#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
APPXMAIN_OBJ_NAME=AppXMain
# component name
APPXMAIN_OBJ_PATH=$(PROJECT_PATH)/server/$(APPLICATIONX_COMPONENT_NAME)
# include and source paths - no need to change
APPXMAIN_OBJ_INCLUDE_PATH=$(APPXMAIN_OBJ_PATH)/include
APPXMAIN_OBJ_SRC_PATH=$(APPXMAIN_OBJ_PATH)/src

# used includes
APPXMAIN_INCLUDES_PATHS=$(sort	-I$(APPXMAIN_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(ABSTRACTION_COMPONENT_INCLUDES_PATHS) \
									$(SWBUS_COMPONENT_INCLUDES_PATHS))

APPXMAIN_INCLUDES=$(sort	$(APPXMAIN_OBJ_INCLUDE_PATH)/APPX_$(APPXMAIN_OBJ_NAME).h \
									$(APPXMAIN_OBJ_PATH)/$(APPXMAIN_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(ABSTRACTION_COMPONENT_INCLUDES)\
									$(SWBUS_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
APPXMAIN_SRC=$(APPXMAIN_OBJ_SRC_PATH)/$(APPXMAIN_OBJ_NAME).c
APPXMAIN_OUTPUT_FOLDER=$(APPXMAIN_OBJ_PATH)/bin
APPXMAIN_OBJ=$(APPXMAIN_OUTPUT_FOLDER)/$(APPXMAIN_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(APPXMAIN_OBJ): $(APPXMAIN_INCLUDES) $(APPXMAIN_SRC) $(APPXMAIN_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(APPXMAIN_OBJ) $(APPXMAIN_INCLUDES_PATHS) $(APPXMAIN_SRC)
