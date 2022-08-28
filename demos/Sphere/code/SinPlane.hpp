
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2014.05

#ifndef SINPLANE_HEADER
#define SINPLANE_HEADER

    #include <glm/glm.hpp>
    #include <glm/gtc/random.hpp>
    #include <glad/glad.h>
	#include <glm/gtx/polar_coordinates.hpp>
    #include <vector>

    namespace example
    {

        class SinPlane
        {
		public:
			const float radius = 7.f;

        private:

            std::vector<GLfloat> vertex_coordinates;
            //std::vector<GLfloat> vertex_colors;

			//2pi makes a full 360 degree circunference
			const float circunference = 3.1415926535 * 2;

			const size_t long_steps = 30;
			const size_t lat_steps = 30;

            const float general_altitude = -1.f;

            // Índices para indexar el array vbo_ids:

            enum
            {
                COORDINATES_VBO,
                RADIUS_VBO,
                VBO_COUNT
            };

        private:

            GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
            GLuint vao_id;                  // Id del VAO del cubo

        public:

            SinPlane();
           ~SinPlane();

            void render ();

        };

    }

#endif
