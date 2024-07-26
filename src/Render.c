//
// Created by Theatre-Simon on 7/22/2024.
//

#include "Render.h"

float Vertices[] = { // Vertex | UV
    -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 0.0f
};

uint32_t Indices[] = {
    0, 1, 2,
    2, 3, 1
};


struct render_t APV_Create_Render(const char *Vertex, const char *Fragment) {
    struct render_t render;

    glGenVertexArrays(1, &render.VAO);
    glGenBuffers(1, &render.VBO);
    glGenBuffers(1, &render.EBO);

    glBindVertexArray(render.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, render.VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render.EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), &Vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), &Indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    render.ShaderProgram = glCreateProgram();

    FILE *VertexFile= fopen(Vertex, "rb");
    fseek(VertexFile, 0, SEEK_END);
    uint32_t VFileSize = ftell(VertexFile);
    fseek(VertexFile, 0, SEEK_SET);
    char *VertexData = malloc(VFileSize+1);
    fread(VertexData, 1, VFileSize, VertexFile);
    VertexData[VFileSize] = '\0';
    glShaderSource(VertexShader, 1, &VertexData, NULL);
    glCompileShader(VertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
        printf("Vertex error: %s\n", infoLog);
    }

    fclose(VertexFile);
    free(VertexData);

    FILE *FragmentFile= fopen(Fragment, "rb");
    fseek(FragmentFile, 0, SEEK_END);
    uint32_t FFileSize = ftell(FragmentFile);
    fseek(FragmentFile, 0, SEEK_SET);
    char *FragmentData = malloc(FFileSize+1);
    fread(FragmentData, 1, FFileSize, FragmentFile);
    FragmentData[FFileSize] = '\0';
    glShaderSource(FragmentShader, 1, &FragmentData, NULL);
    glCompileShader(FragmentShader);
      success;
     infoLog[512];
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
        printf("Fragment error: %s\n", infoLog);
    }
    fclose(FragmentFile);
    free(FragmentData);

    glAttachShader(render.ShaderProgram, VertexShader);
    glAttachShader(render.ShaderProgram, FragmentShader);
    glLinkProgram(render.ShaderProgram);

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);


    glGenTextures(1, &render.Texture);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, render.Texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return render;
}

void APV_Render_Quad(struct render_t render) {
    glUseProgram(render.ShaderProgram);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, render.Texture);
    glUniform1i(glGetUniformLocation(render.ShaderProgram, "text"), 0);
    glBindVertexArray(render.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void APV_Update_Texture(struct render_t render, int width, int height, void *Data) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, render.Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
    glGenerateMipmap(GL_TEXTURE_2D);
}


void APV_Start_Render() {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
