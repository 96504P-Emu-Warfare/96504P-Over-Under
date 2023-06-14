#THIS FILE IS SUPPOSED TO BE A WAY TO SELECT WHICH MAIN AND AUTONS YOU WANT TO RUN, INSTEAD OF HAVING TO COPY AND PASTE

import os
import shutil
import time

auton_to_test = "96504P-Over-Under\!Robot 1\Alpha and Before\TankAutons.preAlpha.0.0.1.cpp"
auton_destination_file = "96504P-Over-Under\src\main.cpp"

main_to_test = "96504P-Over-Under\!Robot 1\Alpha and Before\TankMain.preAlpha.0.0.1.cpp"
main_destination_file = "96504P-Over-Under\src\main.cpp"

#######################################################################################
#EVERYTHING UNDER THIS LINE SHOULD NOT BE CHANGED                                     #
#######################################################################################


def monitor_directory():
    while True:
        shutil.copy_file(auton_to_test, auton_destination_file)
        shutil.copy_file(main_to_test, main_destination_file)
    time.sleep(1)  


monitor_directory()


