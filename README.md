# Joystick_and_Human_Eye_controlled_Robotic_Eyes
Here we controlled Robotics eyes displayed over MAX7219 Dot LED matrix using Joystick and Human Eyes movements by using image processing with python.

Components Required:
1. Arduino Uno/Nano
2. Joystick
3. MAX7219 Dot matrix display

Source code Download:
1. Arduino code from [Robotic_eyes](https://github.com/hakseengineer/Joystick_and_Human_Eye_controlled_Robotic_Eyes/tree/main/Robotic_eyes)
2. Python script from https://github.com/antoinelame/GazeTracking
3. updated requirement.txt [Eye_tracker/requirements.txt](https://github.com/hakseengineer/Joystick_and_Human_Eye_controlled_Robotic_Eyes/blob/main/Eye_tracker/requirements.txt)

Note: Replace the default "Requirement.txt" from gaze tracking folder downloaded in step 2 with the updated file downloaded in step 3.

Steps to configure will be as follows:
1. Install Arduino IDE.
2. Open "Robotic_eyes.ino" from attached code.
3. You can enable or disable Jostick/Eye_controlled mode, using macros "JOYSTICK" and "EYE_CONTROLLED" defined in the code at the starting, You can enable both altogether but for testing we suggest to enable one of them and then try with another.
4. Install MAX72XX library for LED display.
5. After sucesfull compile upload the code to arduino board.
6. Now Your setup is ready to play with Joystick.
7. For EYE_Controlled mode, you need to run attached python script "Eye_tracking.py" from "Eye_tracker" folder, but before that you need to install "Visual Syudio C/C++" and other dependancies mention in the requirement.txt file.
8. After Installing "Visual Studio C/C++" use "pip install -r requirement.txt" to install dependencies.
9. Now last step is to check arduino board com port and modify it in the "Eye_tracking.py" and save it.
10. Now Run python script using "py Eye_tracking.py" command.


Additionally you can checkoutn corresponding video on our channel "Hak_Se Engineer" for complete detail.

Enjoy!!
