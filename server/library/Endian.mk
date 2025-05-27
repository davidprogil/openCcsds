#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
ENDIAN_OBJ_NAME=Endian
# component name
ENDIAN_OBJ_PATH=$(PROJECT_PATH)/server/$(LIBRARY_COMPONENT_NAME)
# include and source paths - no need to change
ENDIAN_OBJ_INCLUDE_PATH=$(ENDIAN_OBJ_PATH)/include
ENDIAN_OBJ_SRC_PATH=$(ENDIAN_OBJ_PATH)/src

# used includes
ENDIAN_INCLUDES_PATHS=$(sort	-I$(ENDIAN_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(SOMETHING_INCLUDES_PATHS))

ENDIAN_INCLUDES=$(sort	$(ENDIAN_OBJ_INCLUDE_PATH)/LIB_$(ENDIAN_OBJ_NAME).h \
									$(ENDIAN_OBJ_PATH)/$(ENDIAN_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(SOMETHING_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
ENDIAN_SRC=$(ENDIAN_OBJ_SRC_PATH)/$(ENDIAN_OBJ_NAME).c
ENDIAN_OUTPUT_FOLDER=$(ENDIAN_OBJ_PATH)/bin
ENDIAN_OBJ=$(ENDIAN_OUTPUT_FOLDER)/$(ENDIAN_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(ENDIAN_OBJ): $(ENDIAN_INCLUDES) $(ENDIAN_SRC) 
	$(CC) $(CFLAGS) -o $(ENDIAN_OBJ) $(ENDIAN_INCLUDES_PATHS) $(ENDIAN_SRC)
