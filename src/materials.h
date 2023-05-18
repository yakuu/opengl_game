// materials.h
#ifndef MATERIALS_H
#define MATERIALS_H

#include <GL/gl.h>

class Materials {
public:
    void applyDefaultMaterial() const {
        // Set the material properties
        GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        GLfloat specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat shininess = 0.0f;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    }
};

#endif  // MATERIALS_H