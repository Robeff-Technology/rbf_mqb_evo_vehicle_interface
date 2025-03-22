builtin_interfaces/Time stamp

uint8 battery_voltage # battery voltage of the vehicle
uint8 battery_soc # battery soc of the vehicle
uint8 blinker # blinker status of the vehicle (0: off, 1: left, 2: right 3: hazard)
uint8 headlight # Headlight status. Beam off ->0 1->Highbeam on 2->lowbeam on
uint8 gear # Gear status. P-R-N-D (1-2-3-4)
uint8 mode # current robione mode .0-> none 1->remote 2-> autonomous 3->internet
uint8 handbrake # Handbrake status. 0-> released, 1-> pressed