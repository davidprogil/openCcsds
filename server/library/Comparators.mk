#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
COMPARATORS_OBJ_NAME=Comparators
# component name
COMPARATORS_OBJ_PATH=$(PROJECT_PATH)/server/$(LIBRARY_COMPONENT_NAME)
# include and source paths - no need to change
COMPARATORS_OBJ_INCLUDE_PATH=$(COMPARATORS_OBJ_PATH)/include
COMPARATORS_OBJ_SRC_PATH=$(COMPARATORS_OBJ_PATH)/src

# used includes
COMPARATORS_INCLUDES_PATHS=$(sort	-I$(COMPARATORS_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(SOMETHING_INCLUDES_PATHS))

COMPARATORS_INCLUDES=$(sort	$(COMPARATORS_OBJ_INCLUDE_PATH)/LIB_$(COMPARATORS_OBJ_NAME).h \
									$(COMPARATORS_OBJ_PATH)/$(COMPARATORS_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(SOMETHING_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
COMPARATORS_SRC=$(COMPARATORS_OBJ_SRC_PATH)/$(COMPARATORS_OBJ_NAME).c
COMPARATORS_OUTPUT_FOLDER=$(COMPARATORS_OBJ_PATH)/bin
COMPARATORS_OBJ=$(COMPARATORS_OUTPUT_FOLDER)/$(COMPARATORS_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(COMPARATORS_OBJ): $(COMPARATORS_INCLUDES) $(COMPARATORS_SRC) 
	$(CC) $(CFLAGS) -o $(COMPARATORS_OBJ) $(COMPARATORS_INCLUDES_PATHS) $(COMPARATORS_SRC)
