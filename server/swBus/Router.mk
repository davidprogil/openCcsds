#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
ROUTER_OBJ_NAME=Router
# component name
ROUTER_OBJ_PATH=$(PROJECT_PATH)/server/$(SWBUS_COMPONENT_NAME)
# include and source paths - no need to change
ROUTER_OBJ_INCLUDE_PATH=$(ROUTER_OBJ_PATH)/include
ROUTER_OBJ_SRC_PATH=$(ROUTER_OBJ_PATH)/src

# used includes
ROUTER_INCLUDES_PATHS=$(sort	-I$(ROUTER_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(ABSTRACTION_COMPONENT_INCLUDES_PATHS)\
									$(LIBRARY_COMPONENT_INCLUDES_PATHS))

ROUTER_INCLUDES=$(sort	$(ROUTER_OBJ_INCLUDE_PATH)/SBRO_$(ROUTER_OBJ_NAME).h \
									$(ROUTER_OBJ_PATH)/$(ROUTER_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(ABSTRACTION_COMPONENT_INCLUDES)\
									$(LIBRARY_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
ROUTER_SRC=$(ROUTER_OBJ_SRC_PATH)/$(ROUTER_OBJ_NAME).c
ROUTER_OUTPUT_FOLDER=$(ROUTER_OBJ_PATH)/bin
ROUTER_OBJ=$(ROUTER_OUTPUT_FOLDER)/$(ROUTER_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(ROUTER_OBJ): $(ROUTER_INCLUDES) $(ROUTER_SRC) $(SWBUS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(ROUTER_OBJ) $(ROUTER_INCLUDES_PATHS) $(ROUTER_SRC)
