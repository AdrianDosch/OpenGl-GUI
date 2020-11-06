# OpenGl-GUI
A project where I try to create a GUI with OpenGl to use it in other OpenGl projects.

current features:
- creating a checkbox to control a bool
- creating a slider to control a float
- nameing all the controls
- changeing the color and dimentions of the GUI-window
- changeing the position of the GUI-window useing the mouse


external libarys I use:
- GLM
- GLEW
- GLFW
- Freetype

How to use this libary:

SETUP
1. copy the folder "GUI" which you can find under "OpenGl-GUI/openGl GUI" and paste it into the folder which contains the project file of your OpenGL program:

2. link to all .lib files of the external libarys mentioned (Freetype, GLFW, GLEW). For every libary there are two .lib files. (one win32 and one x64)
   if you have put the GUI folder in the recommended directory the linker setup should be as follows:
   Visual Studio:
   Additional Libary Directories:
   win32:
     $(ProjectDir)GUI\Dependencies\FREETYPE\lib\win32;$(ProjectDir)GUI\Dependencies\GLEW\lib\Release\Win32;$(ProjectDir)GUI\Dependencies\GLFW\lib-vc2019
   x64:
     $(ProjectDir)GUI\Dependencies\FREETYPE\lib\x64;$(ProjectDir)GUI\Dependencies\GLEW\lib\Release\x64;$(ProjectDir)GUI\Dependencies\GLFW\lib-vc2019-64
   Additional Dependencies:
     All Platforms:
     freetype.lib;glew32s.lib;glfw3.lib;opengl32.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib
  
3. Link to the .dll files of freetype. You can find these in the directory "GUI\Dependencies\dlls\". Visual studio gives you the option to link to dll files useing environment variables. If you have put the GUI folder in the recommended directory the Environment setup should be as follows:
   win32:
     PATH=%PATH%;$(ProjectDir)GUI\Dependencies\dlls\win32
   x64:
     PATH=%PATH%;$(ProjectDir)GUI\Dependencies\dlls\x64
 
 4. (optional) This step is only neaded if you want to execute youre program outside of your IDE. Copy the .dll files fo freetype to the corresponding outpute directory of your OpenGl Project. You can find these in the directory "GUI\Dependencies\dlls\". Visual studio gives you the option to automate this process by useing a post build event. If you have put the GUI folder in the recommended directory the Post-Build Event setup should be as follows:
    win32:
       xcopy /d /y "$(ProjectDir)GUI\Dependencies\dlls\win32\*.*" "$(OutDir)"
    x64:
       xcopy /d /y "$(ProjectDir)GUI\Dependencies\dlls\x64\*.*" "$(OutDir)"

IMPLEMENTATION
1. Include the GUI libary. You have to include the Includes.h file first. It does not matter if you include include glew.h and glfw3. bevore or after the GUI libary:
   #include "GUI\Includes.h"
   #include "GUI/GUI.h"
   
2. Create a window useing the Window class:
   Window window("Gui test", 800, 800);   // the size is optional
 
3. OpenGl things you have to enable after createing a Window:
    glEnable(GL_BLEND);                                 //
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //important!
    
4. create a GUI-Window useing the GUI class:
   GUI gui(&window, "GUI-window name"); //the first parameter is the Window object createt in step 2, the name is optional
   
5. (optional) create the sliders and checkboxes that the GUI-Window should contain. The order of the creation determines the order. You nead to pass in the variables which you want to be changed by the sliders/chackboxes:
   float float1 = 0.f;
   bool bool1 = false;
   CheckBox checkBox1 (&gui, &bool1);
   Slider slider1(&gui, &float1, 0.f, 1.f); // the min value of the variable float1 is 0 and the max value is 1 
   
6. Update the input every frame:
   gui.updateInput(); // gui is the object we created in step 4
   
7. Draw the GUI-Window every frame after calling glClear(). You should call this function after drawing all of your other OpenGl stuff so the GUI-Window isn't drawn behind other objects:
   //all your OpenGl draw calls
   gui.draw();
   
