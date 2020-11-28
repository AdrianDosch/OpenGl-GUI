# OpenGl-GUI
This libary can be used to display and change variables useing the mouse.

![Image of GUI-Window](https://github.com/AdrianD873/OpenGl-GUI/blob/master/GUI-src/sceenshot.PNG)

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

SETUP

0. Use the C++ 17 compiler!

1. Copy the folder "include" which you can find under and paste it into the include dirdctory of your project.

2. Link to all the include pahts of the external libarys. (GLFW, GLM, GLEW). You can find these in the "GUI-src/external" directory. If you are already useing these libarys you don't have to link to them again.

3. Link to all .lib files of the external libarys mentioned (Freetype, GLFW, GLEW) and the GUI.lib file. For every libary there are two .lib files. (one win32 and one x64)
 
4. Link to the .dll files of freetype. You can find these in the directory "GUI-src/external/FREETYPE/dlls/".

IMPLEMENTATION

1. Include the GUI libary. You have to include the Includes.h file first. It does not matter if you include include glew.h and glfw3. bevore or after the GUI libary:
   #include "GUI/GUI.h"
 
2. OpenGl things you have to enable after createing a Window:
    glEnable(GL_BLEND);                                 //
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //important!
    
3. create a GUI-Window useing the GUI class:
   GUI gui(windowID, "GUI-window name"); //the first parameter is the WindowID pointer from GLFW, the name is optional
   
5. Create the sliders and checkboxes that the GUI-Window should contain. The order of the creation determines the order. You nead to pass in the variables which you want to be changed by the sliders/chackboxes. You can create as many Sliders/Checkboxes as you want:
   float float1 = 0.f;
   bool bool1 = false;
   CheckBox checkBox1 (&gui, &bool1);
   Slider slider1(&gui, &float1, 0.f, 1.f); // the min value of the variable float1 is 0 and the max value is 1 
   
6. Update the input every frame:
   gui.updateInput(); // gui is the object we created in step 3
   
7. Draw the GUI-Window every frame after calling glClear(). You should call this function after drawing all of your other OpenGl stuff so the GUI-Window isn't drawn behind other objects:
   //all your OpenGl draw calls
   gui.draw();
   
   
   
CUSTOMISATION

It is possible to change almost every property of the GUI-Window and its components. 
GUI:
   setColor(glm::fvec4 color)
   setPosition(glm::fvec2 position)
   setWidth(float width)
   setHight(float hight)
   setTitle(std::string title)
   setTitleColor(glm::fvec3 color)
   FixPosition(bool state)

CheckBox:
   setText(std::string text)
   void setTextColor(float r = 1.f, float g = 1.f, float b = 1.f)
   
Slider:
   setText(std::string text)
   void setTextColor(float r = 1.f, float g = 1.f, float b = 1.f)
	void setPositionBar(float leftEnd = 0.5f, float rightEnd = (19.f/20.f))
	void setWidthSlider(float width = (1.f/20.f))
	void setColorBar(float r = 0.8f, float g = 0.6f, float b = 0.1f, float a = 1.f)
	void setColorSlider(float r = 0.9f, float g = 0.6f, float b = 0.1f, float a = 1.f)



TIPPS AND TRICKS

The overall hight of the GUI-Window in percent of the whole window is calculatet as follows:
   gui.getHight() * gui.getMemberCount();

You can set the Text of a slider every frame to display the exact value of the variable:
   slider1.setText("float1: " + std::to_string(float1));

you can set the most important properties right at the creation of the objects. e.g.:
                   //title,       position,              color,                           width, hight
   GUI gui(&window, "nice title", glm::vec2(0.2f, 0.8f), glm::vec4(0.1f, 0.8f, 0.4f, 1.f), 0.7f, 0.15f);
   
