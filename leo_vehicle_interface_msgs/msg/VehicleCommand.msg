builtin_interfaces/Time stamp
# Gear states
uint8 GEAR_P = 1
uint8 GEAR_R = 2
uint8 GEAR_N = 3
uint8 GEAR_D = 4

# Blinker states
uint8 BLINKER_OFF = 0
uint8 BLINKER_LEFT = 1
uint8 BLINKER_RIGHT = 2
uint8 BLINKER_HAZARD = 3

# Mode states
uint8 AUTONOMOUS_OFF = 0
uint8 AUTONOMOUS_ON = 1

uint8 set_autonomous
uint8 blinker
uint8 headlight
uint8 gear
uint8 handbrake # not implemented yet
uint8 emergency
