#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

CORE_COMPONENT_NAME=core
CORE_COMPONENT_FOLDER=$(PROJECT_PATH)/server/$(CORE_COMPONENT_NAME)
CORE_COMPONENT_OUTPUT_FOLDER=$(CORE_COMPONENT_FOLDER)/bin

$(CORE_COMPONENT_OUTPUT_FOLDER):
	mkdir -p $@

#objects includes -----------------
include $(CORE_COMPONENT_FOLDER)/Maestro.mk


CORE_COMPONENT_INCLUDES_PATHS= \
						$(MAESTRO_INCLUDES_PATHS) \



CORE_COMPONENT_INCLUDES=	$(CORE_COMPONENT_FOLDER)/$(CORE_COMPONENT_NAME).mk \
						$(MAESTRO_INCLUDES) \



CORE_COMPONENT_OBJ= \
						$(MAESTRO_OBJ) \


