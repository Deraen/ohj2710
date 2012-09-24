LOCAL_PATH := $(call my-dir)

###########################
#
# Box2D shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := Box2D

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/Collision/*.cpp) \
	$(wildcard $(LOCAL_PATH)/Collision/Shapes/*.cpp) \
	$(wildcard $(LOCAL_PATH)/Common/*.cpp) \
	$(wildcard $(LOCAL_PATH)/Dynamics/*.cpp) \
	$(wildcard $(LOCAL_PATH)/Dynamics/Contacts/*.cpp) \
	$(wildcard $(LOCAL_PATH)/Dynamics/Joints/*.cpp) \
	$(wildcard $(LOCAL_PATH)/Rope/*.cpp))

LOCAL_CFLAGS += 
LOCAL_LDLIBS := 

include $(BUILD_SHARED_LIBRARY)
