LOCAL_DIR := $(GET_LOCAL_DIR)

ifeq ($(PROJECT), msm8916-secondary)
DTBS += \
	$(LOCAL_DIR)/msm8916-longcheer-l8150.dtb \
	$(LOCAL_DIR)/msm8916-samsung.dtb
endif
ifeq ($(PROJECT), msm8953-secondary)
DTBS += \
	$(LOCAL_DIR)/sdm450-samsung-r04.dtb \
	$(LOCAL_DIR)/msm8953-xiaomi-common.dtb \
	$(LOCAL_DIR)/sdm632-fairphone-fp3.dtb \
	$(LOCAL_DIR)/sdm632-motorola-ocean.dtb \
	$(LOCAL_DIR)/msm8953-xiaomi-daisy.dtb \
	$(LOCAL_DIR)/msm8953-xiaomi-vince.dtb \
	$(LOCAL_DIR)/msm8953-meizu-m1721.dtb \
	$(LOCAL_DIR)/msm8953-motorola-potter.dtb
endif
ifeq ($(PROJECT), msm8917-secondary)
DTBS += \
	$(LOCAL_DIR)/msm8917-samsung-r06.dtb \
	$(LOCAL_DIR)/msm8917-lenovo-tbx304.dtb
endif
ifeq ($(PROJECT), msm8937-secondary)
DTBS += \
	$(LOCAL_DIR)/msm8937-nokia-nd1.dtb
endif

ifeq ($(PROJECT), mi8937-secondary)
DTBS += \
	$(LOCAL_DIR)/msm8917-xiaomi-common.dtb \
	$(LOCAL_DIR)/msm8917-xiaomi-riva.dtb \
	$(LOCAL_DIR)/msm8917-xiaomi-ugglite.dtb \
	$(LOCAL_DIR)/msm8937-xiaomi-land.dtb \
	$(LOCAL_DIR)/msm8937-xiaomi-prada.dtb \
	$(LOCAL_DIR)/msm8940-xiaomi-santoni.dtb \
	$(LOCAL_DIR)/msm8940-xiaomi-ugg.dtb
endif
