#ifndef LOAD_TEXTURE_H
#define LOAD_TEXTURE_H

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <tchar.h>


GLuint loadTexture(const char* filename) {
    GLuint tex = 0;
    unsigned char* texture;
    int width, height;
    FILE* file;
    TCHAR spritePath[MAX_PATH];

    // Construct the full path to the file
    _stprintf_s(spritePath, MAX_PATH, _T("src/data/sprite/%s"), filename);
    file = _tfopen(spritePath, _T("rb"));
    if (file != NULL) {
        width = 256;
        height = 256;
        texture = (unsigned char*)malloc(width * height * 3);
        fread(texture, width * height * 3, 1, file);
        fclose(file);

        // Create and bind a new texture
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
        free(texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
    return tex;
}

#endif // LOAD_TEXTURE_H

GLuint* textureList = NULL;
int textureCount = 0;

GLuint tex;

// Function to load all the textures in the "src/data/sprite/" directory
void loadTextures() {
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    TCHAR spriteDir[MAX_PATH] = _T("src/data/sprite/*.*");
    TCHAR spritePath[MAX_PATH];
    unsigned char* texture;
    int width, height;
    int numTextures = 0;
    GLuint* textures = (GLuint*)malloc(sizeof(GLuint));

    // Load the player texture
    FILE* playerFile;
    playerFile = fopen("src/data/sprite/player.raw", "rb");
    if (playerFile != NULL) {
        width = 256;
        height = 256;
        texture = (unsigned char*)malloc(width * height * 3);
        fread(texture, width * height * 3, 1, playerFile);
        fclose(playerFile);

        // Create and bind a new texture
        GLuint playerTex;
        glGenTextures(1, &playerTex);
        glBindTexture(GL_TEXTURE_2D, playerTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
        free(texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        numTextures++;
        textures = (GLuint*)realloc(textures, sizeof(GLuint) * numTextures);
        textures[numTextures-1] = playerTex;
    }

    // Find all the files in the directory
    hFind = FindFirstFile(spriteDir, &FindFileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            // Check if the file is a .raw file
            if (_tcsstr(FindFileData.cFileName, _T(".raw")) != NULL) {
                // Construct the full path to the file
                _stprintf_s(spritePath, MAX_PATH, _T("src/data/sprite/%s"), FindFileData.cFileName);
                FILE* file;
                file = _tfopen(spritePath, _T("rb"));
                if (file != NULL) {
                    width = 256;
                    height = 256;
                    texture = (unsigned char*)malloc(width * height * 3);
                    fread(texture, width * height * 3, 1, file);
                    fclose(file);

                    // Create and bind a new texture
                    GLuint tex;
                    glGenTextures(1, &tex);
                    glBindTexture(GL_TEXTURE_2D, tex);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
                    free(texture);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

                    numTextures++;
                    textures = (GLuint*)realloc(textures, sizeof(GLuint) * numTextures);
                    textures[numTextures-1] = tex;
                }
            }
        } while (FindNextFile(hFind, &FindFileData));
        FindClose(hFind);
    }

    // Save the loaded textures to a global variable
    textureCount = numTextures;
    textureList = textures;
}

// Function to load the current texture
void loadTexture() {
    for (int i = 0; i < textureCount; i++) {
        if (strstr((char*)glGetString(GL_VERSION), "1.1") == NULL) { // If OpenGL version is 1.1 or later
            glEnable(GL_TEXTURE_2D);
        }
        tex = textureList[i];
        if (i == textureCount-1) { // Use the player texture for the last rectangle
            tex = textureList[i];
        }
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            printf("Error loading texture %d: %s\n", i, gluErrorString(error));
        }
    }
}
