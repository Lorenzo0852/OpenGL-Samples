
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2014.05

#include "Cylindre.hpp"

namespace example
{

    const GLfloat Cylindre::coordinates[] =
    {
         0.f, 0.f,    1.f,            // 0
       0.65f, 0.f,  0.65f,            // 1
         1.f, 0.f,    0.f,            // 2
       0.65f, 0.f, -0.65f,            // 3
         0.f, 0.f,   -1.f,            // 4
      -0.65f, 0.f, -0.65f,            // 5
        -1.f, 0.f,    0.f,            // 6
      -0.65f, 0.f,  0.65f,            // 7

         0.f, 2.f,    1.f,            // 8
       0.65f, 2.f,  0.65f,            // 9
         1.f, 2.f,    0.f,            // 10
       0.65f, 2.f, -0.65f,            // 11
         0.f, 2.f,   -1.f,            // 12
      -0.65f, 2.f, -0.65f,            // 13
        -1.f, 2.f,    0.f,            // 14
      -0.65f, 2.f,  0.65f,            // 15
    };

    const GLfloat Cylindre::colors[] =
    {
        0, 0, 1,            // 0    Representa un cubo RGB
        1, 0, 1,            // 1
        1, 1, 1,            // 2
        0, 1, 1,            // 3
        0, 0, 0,            // 4
        1, 0, 0,            // 5
        1, 1, 0,            // 6
        0, 1, 0,            // 7

        0, 0, 1,            // 8 
        1, 0, 1,            // 9
        1, 1, 1,            // 10
        0, 1, 1,            // 11
        0, 0, 0,            // 12
        1, 0, 0,            // 13
        1, 1, 0,            // 14
        0, 1, 0,            // 15
    };

    const GLubyte Cylindre::indices[] =
    {
        1,   0,   2,            // Circle
        2,   0,   3,            // 
        3,   0,   4,            // 
        4,   0,   5,            // 
        5,   0,   6,            // 
        6,   0,   7,
        

        8,   9,  10,          // Circle
        8,  10,  11,          // 
        8,  11,  12,          // 
        8,  12,  13,          // 
        8,  13,  14,          // 
        8,  14,  15,
        
        0,   1,   8,
        8,   1,   9,
        1,   2,   9,
        9,   2,  10,
        2,   3,  10,
        10,  3,  11,
        3,   4,  11,
        11,  4,  12,
        4,   5,  12,
        12,  5,  13,
        5,   6,  13,
        13,  6,  14,
        6,   7,  14,
        14,  7,  15,
        7,   0,  15,
        15,  0,   8,
    };

    Cylindre::Cylindre()
    {
        // Se generan índices para los VBOs del cubo:

        glGenBuffers (VBO_COUNT, vbo_ids);
        glGenVertexArrays (1, &vao_id);

        // Se activa el VAO del cubo para configurarlo:

        glBindVertexArray (vao_id);

        // Se suben a un VBO los datos de coordenadas y se vinculan al VAO:

        glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData (GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);

        glEnableVertexAttribArray (0);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Se suben a un VBO los datos de color y se vinculan al VAO:

        glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        glBufferData (GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        glEnableVertexAttribArray (1);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Se suben a un EBO los datos de índices:

        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_EBO]);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray (0);
    }

    Cylindre::~Cylindre()
    {
        // Se liberan los VBOs y el VAO usados:

        glDeleteVertexArrays (1, &vao_id);
        glDeleteBuffers      (VBO_COUNT, vbo_ids);
    }

    void Cylindre::render ()
    {
        // Se selecciona el VAO que contiene los datos del objeto y se dibujan sus elementos:

        glBindVertexArray (vao_id);
        glDrawElements    (GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, 0);
        glBindVertexArray (0);
    }

}
