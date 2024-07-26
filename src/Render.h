//
// Created by Theatre-Simon on 7/22/2024.
//

#ifndef RENDER_H
#define RENDER_H
#include <gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <Processing.NDI.Lib.h>

struct render_t {
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    GLuint ShaderProgram;

    GLuint Texture;
};


struct render_t APV_Create_Render(const char *Vertex, const char *Fragment);

void APV_Render_Quad(struct render_t render);

void APV_Update_Texture(struct render_t render, int width, int height, void *Data);

void APV_Start_Render();

#endif //RENDER_H
