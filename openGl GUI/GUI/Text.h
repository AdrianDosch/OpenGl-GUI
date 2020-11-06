#ifndef TEXT_H
#define TEXT_H

#include "Includes.h"

#include GLEW
#include GLFW3

#include FT2BUILD
#include FREETYPE
#include <map>
#include GLM
#include MATRIX_TRANSFORM

#include "Shader.h"
#include "Window.h"

class Text
{
private:
    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    /// Holds all state information relevant to a character as loaded using FreeType
    struct Character {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2   Size;      // Size of glyph
        glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Horizontal offset to advance to next glyph
    };

    std::map<GLchar, Character> Characters;
    unsigned int VAO, VBO;

public:
	Text(Window* window);
	~Text();

    unsigned int RenderText(Shader& shader, std::string text, float x, float y, float scaleX, float scaleY, glm::vec3 color);
    unsigned int getAdvancment(std::string);
    unsigned int getMaxHight(std::string text);
};


#endif