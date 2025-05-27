#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

COMPONENTNAME_COMPONENT_NAME=componentName
COMPONENTNAME_COMPONENT_FOLDER=$(PROJECT_PATH)/lib/$(COMPONENTNAME_COMPONENT_NAME)
COMPONENTNAME_COMPONENT_OUTPUT_FOLDER=$(COMPONENTNAME_COMPONENT_FOLDER)/bin

$(COMPONENTNAME_COMPONENT_OUTPUT_FOLDER):
	mkdir -p $@

#objects includes -----------------
include $(COMPONENTNAME_COMPONENT_FOLDER)/Template.mk

COMPONENTNAME_COMPONENT_INCLUDES_PATHS= \
						$(TEMPLATE_INCLUDES_PATHS) \


COMPONENTNAME_COMPONENT_INCLUDES=	$(COMPONENTNAME_COMPONENT_FOLDER)/$(COMPONENTNAME_COMPONENT_NAME).mk \
						$(TEMPLATE_INCLUDES) \


COMPONENTNAME_COMPONENT_OBJ= \
						$(TEMPLATE_OBJ) \

