#*******************************************************************************/
#* Copyright David Gil 1998-TODO                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

PROCESS1_COMPONENT_NAME=process1
PROCESS1_COMPONENT_FOLDER=$(PROJECT_PATH)/server/$(PROCESS1_COMPONENT_NAME)
PROCESS1_COMPONENT_OUTPUT_FOLDER=$(PROCESS1_COMPONENT_FOLDER)/bin

$(PROCESS1_COMPONENT_OUTPUT_FOLDER):
	mkdir -p $@

#objects includes -----------------
include $(PROCESS1_COMPONENT_FOLDER)/Proc1Main.mk

PROCESS1_COMPONENT_INCLUDES_PATHS= \
						$(PROC1MAIN_INCLUDES_PATHS) \


PROCESS1_COMPONENT_INCLUDES=	$(PROCESS1_COMPONENT_FOLDER)/$(PROCESS1_COMPONENT_NAME).mk \
						$(PROC1MAIN_INCLUDES) \


PROCESS1_COMPONENT_OBJ= \
						$(PROC1MAIN_OBJ) \

