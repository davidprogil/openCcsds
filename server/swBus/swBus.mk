#*******************************************************************************/
#* Copyright David Gil 1998-TODO                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

SWBUS_COMPONENT_NAME=swBus
SWBUS_COMPONENT_FOLDER=$(PROJECT_PATH)/server/$(SWBUS_COMPONENT_NAME)
SWBUS_COMPONENT_OUTPUT_FOLDER=$(SWBUS_COMPONENT_FOLDER)/bin

$(SWBUS_COMPONENT_OUTPUT_FOLDER):
	mkdir -p $@

#objects includes -----------------
include $(SWBUS_COMPONENT_FOLDER)/Router.mk

SWBUS_COMPONENT_INCLUDES_PATHS= \
						$(ROUTER_INCLUDES_PATHS) \


SWBUS_COMPONENT_INCLUDES=	$(SWBUS_COMPONENT_FOLDER)/$(SWBUS_COMPONENT_NAME).mk \
						$(ROUTER_INCLUDES) \


SWBUS_COMPONENT_OBJ= \
						$(ROUTER_OBJ) \

