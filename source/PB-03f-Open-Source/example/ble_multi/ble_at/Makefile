APP_NAME = ble_at

# Define the linker script location and chip architecture
LD_SCRIPT = scatter_load.sct
MCU_SPEC = cortex-m0

# Toolchain definitions (ARM bare metal defaults)
TOOLCHAIN = /data/toolchain/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi
#TOOLCHAIN = /data/toolchain/gcc-arm-none-eabi-10.3-2021.10
CC = $(TOOLCHAIN)/bin/arm-none-eabi-gcc
AS = $(TOOLCHAIN)/bin/arm-none-eabi-as
LD = $(TOOLCHAIN)/bin/arm-none-eabi-ld
OC = $(TOOLCHAIN)/bin/arm-none-eabi-objcopy
OD = $(TOOLCHAIN)/bin/arm-none-eabi-objdump
OS = $(TOOLCHAIN)/bin/arm-none-eabi-size

# Assembly directives
ASFLAGS += -c -O0 -mcpu=$(MCU_SPEC) -mthumb -Wall
# (Set error messages to appear on a single line.)
ASFLAGS += -fmessage-length=0

# C compilation directives
CFLAGS += -mcpu=$(MCU_SPEC) -mthumb -Wall
# (Set error messages to appear on a single line.)
CFLAGS += -fmessage-length=0
# (Set system to ignore semihosted junk)
CFLAGS += --specs=nosys.specs
# Macros
CFLAGS += -DADV_NCONN_CFG=0x01 -DADV_CONN_CFG=0x02 -DSCAN_CFG=0x04 -DINIT_CFG=0x08 -DBROADCASTER_CFG=0x01 \
          -DOBSERVER_CFG=0x02 -DPERIPHERAL_CFG=0x04 -DCENTRAL_CFG=0x08 -DHOST_CONFIG=0xc
CFLAGS += -DOSALMEM_METRICS=0 -DDBG_ROM_MAIN=0 -DMTU_SIZE=247 -DDEBUG_INFO=3 -D_BUILD_FOR_DTM_=0 \
			-DENABLE_LOG_ROM_=0 -DHOST_CONFIG=0xC -DHCI_TL_NONE=1 -DOSAL_CBTIMER_NUM_TASKS=1 \
			-DCFG_CP -DPHY_MCU_TYPE=MCU_BUMBEE_M0 -DCFG_SLEEP_MODE=PWR_MODE_SLEEP -DMULTI_DEBUG \
			-DMAX_NUM_LL_CONN=2 -DGATT_MAX_NUM_CONN=MAX_NUM_LL_CONN+1 -DBLE_AT_ENABLE -DOSAL_SNV_UINT16_ID \
			-DCFG_HCLK_DYNAMIC_CHANGE=0
CFLAGS += -DMAX_NUM_LL_CONN=1
CFLAGS += -DGATT_MAX_NUM_CONN=MAX_NUM_LL_CONN+1
CFLAGS += -DCFG_MTU_23=0
CFLAGS += -DCFG_FLASH=512
CFLAGS += -DCFG_OTA_BANK_MODE=OTA_SINGLE_BANK
CFLAGS += -DUSE_FCT=0
CFLAGS += -DON_SLB_BOOTLOADER=1
CFLAGS += -DCFG_OTA_MESH

# Directories
SRC_DIRS += ../../../components/arch/cm0 \
			../../../components/ble/controller \
			../../../components/ble/hci \
			../../../components/ble/host \
			../../../components/ble/include \
			../../../components/driver/adc \
			../../../components/driver/clock \
			../../../components/driver/flash \
			../../../components/driver/gpio \
			../../../components/driver/i2c \
			../../../components/driver/i2s \
			../../../components/driver/kscan \
			../../../components/driver/kscan \
			../../../components/driver/log \
			../../../components/driver/pwrmgr \
			../../../components/driver/spi \
			../../../components/driver/timer \
			../../../components/driver/uart \
			../../../components/driver/uart \
			../../../components/driver/watchdog \
			../../../components/inc \
			../../../components/libraries/cli \
			../../../components/libraries/crc16 \
			../../../components/libraries/fs \
			../../../components/osal/include \
			../../../components/profiles/DevInfo \
			../../../components/profiles/multiRole \
			../../../components/profiles/ota \
			../../../components/profiles/ota_app \
			../../../components/profiles/Roles \
			../../../components/profiles/SimpleProfile \
			../../../lib \
			../../../misc \
			./source/at_multi_role \

# Includes
INCLUDES  = $(patsubst %,-I%,$(SRC_DIRS))
INCLUDES += -I../../../components/gcc/CMSIS/include \
			-I../../../components/osal/include 

# Sources & objects
SRCS  = $(foreach sdir,$(SRC_DIRS),$(wildcard $(sdir)/*.c))
OBJS  = $(SRCS:.c=.o)
TARGET = $(APP_NAME)

# Linker directives
LSCRIPT = ./$(LD_SCRIPT)
LFLAGS += -mcpu=$(MCU_SPEC) -mthumb --specs=nosys.specs -nostdlib -T$(LSCRIPT)

.PHONY: all
all: $(TARGET).bin

%.o: %.S
	$(CC) -x assembler-with-cpp $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(TARGET).bin: $(TARGET).elf
	$(OC) -S -O binary $< $@
	$(OS) $<

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(TARGET).elf $(TARGET).bin
