#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

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

