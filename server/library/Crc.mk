#*******************************************************************************/
#* Copyright David Gil 1998-TODO                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
CRC_OBJ_NAME=Crc
# component name
CRC_OBJ_PATH=$(PROJECT_PATH)/server/$(LIBRARY_COMPONENT_NAME)
# include and source paths - no need to change
CRC_OBJ_INCLUDE_PATH=$(CRC_OBJ_PATH)/include
CRC_OBJ_SRC_PATH=$(CRC_OBJ_PATH)/src

# used includes
CRC_INCLUDES_PATHS=$(sort	-I$(CRC_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(SOMETHING_INCLUDES_PATHS))

CRC_INCLUDES=$(sort	$(CRC_OBJ_INCLUDE_PATH)/LIB_$(CRC_OBJ_NAME).h \
									$(CRC_OBJ_PATH)/$(CRC_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(SOMETHING_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
CRC_SRC=$(CRC_OBJ_SRC_PATH)/$(CRC_OBJ_NAME).c
CRC_OUTPUT_FOLDER=$(CRC_OBJ_PATH)/bin
CRC_OBJ=$(CRC_OUTPUT_FOLDER)/$(CRC_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(CRC_OBJ): $(CRC_INCLUDES) $(CRC_SRC) 
	$(CC) $(CFLAGS) -o $(CRC_OBJ) $(CRC_INCLUDES_PATHS) $(CRC_SRC)
