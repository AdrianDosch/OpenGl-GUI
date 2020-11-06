#ifndef INCLUDES_H
#define INCLUDES_H

#if defined GUI_H || defined CHECKBOX_H || defined SLIDER_H || defined TEXT_H || defined INDEXBUFFER_H || defined RENDERING_H || defined SHADER_H || defined VERTEXARRAY_H || defined VERTEXBUFFER_H || defined WINDOW_H
#define GLFW3 "Dependencies\GLFW\include\GLFW\glfw3.h"
#define GLEW "Dependencies\GLEW\include\GL\glew.h"
#define GLM "Dependencies\GLM\include\glm.hpp"
#define MATRIX_TRANSFORM "Dependencies\GLM\include\gtc\matrix_transform.hpp"
#define STRING_CAST "Dependencies\GLM\include\gtx\string_cast.hpp"
#define FT2BUILD "Dependencies\FREETYPE\include\ft2build.h"
#define FREETYPE "Dependencies\FREETYPE\include\freetype\freetype.h"
#define TYPE_PTR "Dependencies\GLM\include\gtc\type_ptr.hpp"

#else
#define GLFW3 "GUI\Dependencies\GLFW\include\GLFW\glfw3.h"
#define GLEW "GUI\Dependencies\GLEW\include\GL\glew.h"
#define GLM "GUI\Dependencies\GLM\include\glm.hpp"
#define MATRIX_TRANSFORM "GUI\Dependencies\GLM\include\gtc\matrix_transform.hpp"
#define STRING_CAST "GUI\Dependencies\GLM\include\gtx\string_cast.hpp"
#define FT2BUILD "GUI\Dependencies\FREETYPE\include\ft2build.h"
#define FREETYPE "GUI\Dependencies\FREETYPE\include\freetype\freetype.h"
#define TYPE_PTR "GUI\Dependencies\GLM\include\gtc\type_ptr.hpp"

#endif // !GUI
#endif


//visual studio additional include directorys (not neaded because the libarys are linked staticly)
// $(ProjectDir)GUI\Dependencies\FREETYPE\include;$(ProjectDir)GUI\Dependencies\GLM\include;$(ProjectDir)GUI\Dependencies\STB;$(ProjectDir)GUI\Dependencies\GLEW\include;$(ProjectDir)GUI\Dependencies\GLFW\include;%(AdditionalIncludeDirectories)