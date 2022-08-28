
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2014.05

#ifndef CUBE_HEADER
#define CUBE_HEADER

    #include <glad/glad.h>
	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>  

    namespace example
    {

        class Cube
        {
        private:

            // Índices para indexar el array vbo_ids:

            enum
            {
                COORDINATES_VBO,
                COLORS_VBO,
                INDICES_EBO,
                VBO_COUNT
            };

            // Arrays de datos del cubo base:

            static const GLfloat coordinates[];
            static const GLfloat colors     [];
            static const GLubyte indices    [];

        private:

            GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
            GLuint vao_id;                  // Id del VAO del cubo

        public:

            Cube();
           ~Cube();

			void setup_cube(glm::vec3 translation);
            void render ();

        };

    }

#endif
