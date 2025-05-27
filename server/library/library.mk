#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

LIBRARY_COMPONENT_NAME=library
LIBRARY_COMPONENT_FOLDER=$(PROJECT_PATH)/server/$(LIBRARY_COMPONENT_NAME)
LIBRARY_COMPONENT_OUTPUT_FOLDER=$(LIBRARY_COMPONENT_FOLDER)/bin

$(LIBRARY_COMPONENT_OUTPUT_FOLDER):
	mkdir -p $@

#objects includes -----------------
include $(LIBRARY_COMPONENT_FOLDER)/Queue.mk
include $(LIBRARY_COMPONENT_FOLDER)/Crc.mk
include $(LIBRARY_COMPONENT_FOLDER)/Endian.mk
include $(LIBRARY_COMPONENT_FOLDER)/Comparators.mk


LIBRARY_COMPONENT_INCLUDES_PATHS= \
						$(QUEUE_INCLUDES_PATHS) \
						$(CRC_INCLUDES_PATHS) \
						$(ENDIAN_INCLUDES_PATHS) \
						$(COMPARATORS_INCLUDES_PATHS) \

LIBRARY_COMPONENT_INCLUDES=	$(LIBRARY_COMPONENT_FOLDER)/$(LIBRARY_COMPONENT_NAME).mk \
						$(QUEUE_INCLUDES) \
						$(CRC_INCLUDES) \
						$(ENDIAN_INCLUDES) \
						$(COMPARATORS_INCLUDES) \

LIBRARY_COMPONENT_OBJ= \
						$(QUEUE_OBJ) \
						$(CRC_OBJ) \
						$(ENDIAN_OBJ) \
						$(COMPARATORS_OBJ) \


