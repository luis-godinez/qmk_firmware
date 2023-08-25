<<<<<<< HEAD
=======
# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = qmk-dfu

>>>>>>> 87058047959d7859c2375042935b9b0c602d60b8
# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
MIDI_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
ENCODER_ENABLE = yes
RGB_MATRIX_ENABLE = yes
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
LTO_ENABLE = yes
TAP_DANCE_ENABLE = yes
VIA_ENABLE = yes

SRC += analog.c
