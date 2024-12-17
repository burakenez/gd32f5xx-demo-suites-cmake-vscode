project(GD32F5xx_standard_peripheral LANGUAGES C CXX ASM)

# Comment-out unused source files.
add_library(GD32F5xx_standard_peripheral OBJECT
	${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_adc.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_can.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_cau.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_cau_aes.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_cau_des.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_cau_tdes.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_crc.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_ctc.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_dac.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_dbg.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_dci.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_dma.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_enet.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_exmc.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_exti.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_fmc.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_fwdgt.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_gpio.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_hau.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_hau_sha_md5.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_i2c.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_i2c_add.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_ipa.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_iref.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_misc.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_pkcau.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_pmu.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_rcu.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_rtc.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_sai.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_sdio.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_spi.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_syscfg.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_timer.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_tli.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_trng.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_usart.c
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Source/gd32f5xx_wwdgt.c
    )

target_include_directories(GD32F5xx_standard_peripheral PUBLIC
    ${DRIVERS_DIR}/GD32F5xx_standard_peripheral/Include
    )

# CMSIS header only library is linked.
target_link_libraries(GD32F5xx_standard_peripheral PUBLIC CMSIS)
