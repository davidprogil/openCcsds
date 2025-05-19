#*******************************************************************************/
#* Copyright David Gil 1998-TODO                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

ABSTRACTION_COMPONENT_NAME=abstraction
ABSTRACTION_COMPONENT_FOLDER=$(PROJECT_PATH)/server/$(ABSTRACTION_COMPONENT_NAME)
ABSTRACTION_COMPONENT_OUTPUT_FOLDER=$(ABSTRACTION_COMPONENT_FOLDER)/bin

$(ABSTRACTION_COMPONENT_OUTPUT_FOLDER):
	mkdir -p $@

#objects includes -----------------
include $(ABSTRACTION_COMPONENT_FOLDER)/Osal.mk

ABSTRACTION_COMPONENT_INCLUDES_PATHS= \
						$(OSAL_INCLUDES_PATHS) \


ABSTRACTION_COMPONENT_INCLUDES=	$(ABSTRACTION_COMPONENT_FOLDER)/$(ABSTRACTION_COMPONENT_NAME).mk \
						$(OSAL_INCLUDES) \


ABSTRACTION_COMPONENT_OBJ= \
						$(OSAL_OBJ) \

