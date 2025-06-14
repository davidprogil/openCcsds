#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

APPLICATIONX_COMPONENT_NAME=applicationX
APPLICATIONX_COMPONENT_FOLDER=$(PROJECT_PATH)/server/$(APPLICATIONX_COMPONENT_NAME)
APPLICATIONX_COMPONENT_OUTPUT_FOLDER=$(APPLICATIONX_COMPONENT_FOLDER)/bin

$(APPLICATIONX_COMPONENT_OUTPUT_FOLDER):
	mkdir -p $@

#objects includes -----------------
include $(APPLICATIONX_COMPONENT_FOLDER)/AppXMain.mk

APPLICATIONX_COMPONENT_INCLUDES_PATHS= \
						$(APPXMAIN_INCLUDES_PATHS) \


APPLICATIONX_COMPONENT_INCLUDES=	$(APPLICATIONX_COMPONENT_FOLDER)/$(APPLICATIONX_COMPONENT_NAME).mk \
						$(APPXMAIN_INCLUDES) \


APPLICATIONX_COMPONENT_OBJ= \
						$(APPXMAIN_OBJ) \

