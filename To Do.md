* Doxygen comment for semester 2  

#################################################################

* QT/VTK objectives
  - Need a measuring tool
  - Ability to select cells
  - Display statistics of Model and individual cells
  - Fix the following bugs:
    * Open and save should be renamed to Open Model and Save Model : Jed : Fixed (4/20/2020)
    * Console?  : Jed : What does this mean??
    * When camera is reset the vertical and horizontal shift number do not reset to 0 : Jed : Fixed (4/20/2020)
    * What is BOX check box? : Jed : removed (4/20/2020)
    * Fullscreen check box is redundant : Jed : agreed
    * Color to Colour : Jed : This is American spelling but yes I will fix it. 
    * object color to Model Colour : Jed : Fixed (4/20/2020)
    * back ground color to Background Colour : Jed : Fixed (4/20/2020)

			I have just changed the text displayed of color to Colour. I did not change it in code

    * Colour of material not being applied to the model : Jed : Did you try for MOD or TXT files. It works for me on MOD and TXT files but not for stl files.
    * Move filters to the object view box instead of new window : Jed : I have this in a new window so that is seperates the code into different files. Theoretical this allows for quick updates to code as filters applied will be added and contained within this file and the mainwindow file should be left alone. MainWindow is already a huge file.
    * X Y Z rotation dial not function correctly, values for all? maybe allow for values to be entered?
		: Jed : This reason I used a dial here is to demonstrate that we can use different widgets since spin boxes are used else where. The mark sheet says to use several different QT widgets. But I agree that a double spin box would be better used here. How do you see that they do not function correctly? 
    * Shrinker and clipper not function correctly : Jed : filters only work on stl files for now. What errors do you see. It seems to work properly for me

* Clean up code and make sure all indented nicely and commented

#################################################################

* Windows installer                                             
* MacOS installer                                                 
* A way of transferring .dlls over (and example_models?)
* icon and desktop shortcut