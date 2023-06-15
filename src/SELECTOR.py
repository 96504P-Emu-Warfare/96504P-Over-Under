#THIS FILE IS SUPPOSED TO BE A WAY TO SELECT WHICH MAIN AND AUTONS YOU WANT TO RUN, INSTEAD OF HAVING TO COPY AND PASTE
#TO USE, PLACE THE PATH TO YOUR TEST FILE AND RUN

import os
import shutil

auton_to_test = r"C:\Users\theco\Github Codes\96504P-Over-Under\!Robot 1\Alpha and Before\TankAutons.preAlpha.0.0.1.cpp"

main_to_test = r"C:\Users\theco\Github Codes\96504P-Over-Under\!Robot 1\Alpha and Before\TankMain.preAlpha.0.0.1.cpp"

#######################################################################################
#EVERYTHING UNDER THIS LINE SHOULD NOT BE CHANGED                                     #
#######################################################################################

auton_destination_file = r"C:\Users\theco\Github Codes\96504P-Over-Under\src\autons.cpp"
main_destination_file = r"C:\Users\theco\Github Codes\96504P-Over-Under\src\main.cpp"

shutil.copyfile(auton_to_test, auton_destination_file)
shutil.copyfile(main_to_test, main_destination_file)




