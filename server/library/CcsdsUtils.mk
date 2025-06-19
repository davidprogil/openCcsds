#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
CCSDSUTILS_OBJ_NAME=CcsdsUtils
# component name
CCSDSUTILS_OBJ_PATH=$(PROJECT_PATH)/server/$(LIBRARY_COMPONENT_NAME)
# include and source paths - no need to change
CCSDSUTILS_OBJ_INCLUDE_PATH=$(CCSDSUTILS_OBJ_PATH)/include
CCSDSUTILS_OBJ_SRC_PATH=$(CCSDSUTILS_OBJ_PATH)/src

# used includes
CCSDSUTILS_INCLUDES_PATHS=$(sort	-I$(CCSDSUTILS_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(ABSTRACTION_COMPONENT_INCLUDES_PATHS)\
									$(LIBRARY_COMPONENT_INCLUDES_PATHS))

CCSDSUTILS_INCLUDES=$(sort	$(CCSDSUTILS_OBJ_INCLUDE_PATH)/SBCC_$(CCSDSUTILS_OBJ_NAME).h \
									$(CCSDSUTILS_OBJ_PATH)/$(CCSDSUTILS_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(ABSTRACTION_COMPONENT_INCLUDES)\
									$(LIBRARY_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
CCSDSUTILS_SRC=$(CCSDSUTILS_OBJ_SRC_PATH)/$(CCSDSUTILS_OBJ_NAME).c
CCSDSUTILS_OUTPUT_FOLDER=$(CCSDSUTILS_OBJ_PATH)/bin
CCSDSUTILS_OBJ=$(CCSDSUTILS_OUTPUT_FOLDER)/$(CCSDSUTILS_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(CCSDSUTILS_OBJ): $(CCSDSUTILS_INCLUDES) $(CCSDSUTILS_SRC) $(SWBUS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(CCSDSUTILS_OBJ) $(CCSDSUTILS_INCLUDES_PATHS) $(CCSDSUTILS_SRC)
