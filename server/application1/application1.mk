#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

APPLICATION1_COMPONENT_NAME=application1
APPLICATION1_COMPONENT_FOLDER=$(PROJECT_PATH)/server/$(APPLICATION1_COMPONENT_NAME)
APPLICATION1_COMPONENT_OUTPUT_FOLDER=$(APPLICATION1_COMPONENT_FOLDER)/bin

$(APPLICATION1_COMPONENT_OUTPUT_FOLDER):
	mkdir -p $@

#objects includes -----------------
include $(APPLICATION1_COMPONENT_FOLDER)/App1Main.mk

APPLICATION1_COMPONENT_INCLUDES_PATHS= \
						$(APP1MAIN_INCLUDES_PATHS) \


APPLICATION1_COMPONENT_INCLUDES=	$(APPLICATION1_COMPONENT_FOLDER)/$(APPLICATION1_COMPONENT_NAME).mk \
						$(APP1MAIN_INCLUDES) \


APPLICATION1_COMPONENT_OBJ= \
						$(APP1MAIN_OBJ) \

