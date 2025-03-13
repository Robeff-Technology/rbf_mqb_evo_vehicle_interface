builtin_interfaces/Time stamp

uint8 fuel # fuel level of the vehicle (liter)
uint8 blinker # blinker status of the vehicle (0: off, 1: left, 2: right 3: hazard)
uint8 gear # gear status of the vehicle (4: neutral, 3: drive, 2: reverse, 1: park)
uint8 target_gear_level # target gear level of the vehicle (1. 2. 3. 4. 5. 6. and 7. Gear 8 reverse)
uint8 handbrake # handbrake status of the vehicle (0: released, 1: engaged 3:releasing) IMPORTANT: User can start to autonomous driving when handbrake released
uint8 mode # mode status of the vehicle (0: manual, 1: joystick 2: autonomous)
