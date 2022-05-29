# top level project rules for the mi8937 project
#
LOCAL_DIR := $(GET_LOCAL_DIR)

include $(LOCAL_DIR)/msm8952-secondary.mk

BOARD_NAME := mi8937-secondary

# Mi8937 Kernel support
DEFINES += MI8937_KERNEL=1
