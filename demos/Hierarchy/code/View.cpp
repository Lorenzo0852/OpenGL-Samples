
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2014.05

#include "View.hpp"
#include <iostream>
#include <cassert>

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

namespace example
{

    using namespace std;

    const string View::vertex_shader_code =

        "#version 330\n"
        ""
        "uniform mat4 model_view_matrix;"
        "uniform mat4 projection_matrix;"
        ""
        "layout (location = 0) in vec3 vertex_coordinates;"
        "layout (location = 1) in vec3 vertex_color;"
        ""
        "out vec3 front_color;"
        ""
        "void main()"
        "{"
        "   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);"
        "   front_color = vertex_color;"
        "}";

    const string View::fragment_shader_code =

        "#version 330\n"
        ""
        "in  vec3    front_color;"
        "out vec4 fragment_color;"
        ""
        "void main()"
        "{"
        "    fragment_color = vec4(front_color, 1.0);"
        "}";

    View::View(int width, int height)
    :
        spawn_angle(0),
		rotation_by_time(0)
    {
        // Se establece la configuración básica:

        glEnable     (GL_CULL_FACE);
        glEnable     (GL_DEPTH_TEST);
        glClearColor (.1f, .1f, .1f, 1.f);

        // Se compilan y se activan los shaders:

        GLuint program_id = compile_shaders ();

        glUseProgram (program_id);

        model_view_matrix_id = glGetUniformLocation (program_id, "model_view_matrix");
        projection_matrix_id = glGetUniformLocation (program_id, "projection_matrix");

        resize (width, height);
    }

    void View::update ()
    {
        //angle += 0.01f;
		rotation_by_time += 0.01f;
    }

    void View::render ()
    {
		spawn_angle = 3.14159 / 4;

		glm::mat4 main_modelview = glm::mat4(1);

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//MAIN CUBE (BIGGEST)
		main_modelview = glm::translate(main_modelview, glm::vec3(0.f, 0.f, 0.f));
		main_modelview = glm::rotate(main_modelview, rotation_by_time, glm::vec3(0.f, 1.f, 0.f));
		main_modelview = glm::rotate(main_modelview, spawn_angle, glm::vec3(0.f, 0.f, 1.f));

		//RIGHT
        glm::mat4 model_view_matrix(1);

		model_view_matrix = glm::scale(model_view_matrix, glm::vec3(0.75f));
		model_view_matrix = glm::translate(model_view_matrix, glm::vec3(2.2f, -2.2f, -2.f));
		model_view_matrix = glm::rotate(model_view_matrix, rotation_by_time, glm::vec3(0.f, 1.f, 0.f));
		model_view_matrix = main_modelview * model_view_matrix;

		glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));

		big_cube.render();

		//LEFT
		model_view_matrix = glm::mat4(1);
		model_view_matrix = glm::translate(model_view_matrix, glm::vec3(-2.f, 2.2f, -2.f));
		model_view_matrix = glm::rotate(model_view_matrix, rotation_by_time, glm::vec3(0.f, 1.f, 0.f));
		model_view_matrix = glm::scale(model_view_matrix, glm::vec3(0.75f));
		model_view_matrix = main_modelview * model_view_matrix;

		glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));

		big_cube.render();

		//TOP
		model_view_matrix = glm::mat4(1);
		model_view_matrix = glm::translate(model_view_matrix, glm::vec3(2.f, 2.f, -2.f));
		model_view_matrix = glm::rotate(model_view_matrix, rotation_by_time, glm::vec3(0.f, 1.f, 0.f));
		model_view_matrix = glm::scale(model_view_matrix, glm::vec3(0.75f));
		model_view_matrix = main_modelview * model_view_matrix;

		glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));

		big_cube.render();

		//BOTTOM
		model_view_matrix = glm::mat4(1);
		model_view_matrix = glm::translate(model_view_matrix, glm::vec3(-2.f, -2.f, -2.f));
		model_view_matrix = glm::rotate(model_view_matrix, rotation_by_time, glm::vec3(0.f, 1.f, 0.f));
		model_view_matrix = glm::scale(model_view_matrix, glm::vec3(0.75f));
		model_view_matrix = main_modelview * model_view_matrix;

		glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));

		big_cube.render();

		glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(main_modelview));

		// Se dibuja el cubo:

		big_cube.render();
    }

    void View::resize (int width, int height)
    {
        glm::mat4 projection_matrix = glm::perspective (20.f, GLfloat(width) / height, 1.f, 5000.f);
		//Echamos hacia atrás la cámara porque el ejercicio pide que el cubo sea el que está en 0,0...

		projection_matrix = glm::translate(projection_matrix, {0,0,-5});

        glUniformMatrix4fv (projection_matrix_id, 1, GL_FALSE, glm::value_ptr(projection_matrix));

        glViewport (0, 0, width, height);
    }

    GLuint View::compile_shaders ()
    {
        GLint succeeded = GL_FALSE;

        // Se crean objetos para los shaders:

        GLuint   vertex_shader_id = glCreateShader (GL_VERTEX_SHADER  );
        GLuint fragment_shader_id = glCreateShader (GL_FRAGMENT_SHADER);

        // Se carga el código de los shaders:

        const char *   vertex_shaders_code[] = {          vertex_shader_code.c_str () };
        const char * fragment_shaders_code[] = {        fragment_shader_code.c_str () };
        const GLint    vertex_shaders_size[] = { (GLint)  vertex_shader_code.size  () };
        const GLint  fragment_shaders_size[] = { (GLint)fragment_shader_code.size  () };

        glShaderSource  (  vertex_shader_id, 1,   vertex_shaders_code,   vertex_shaders_size);
        glShaderSource  (fragment_shader_id, 1, fragment_shaders_code, fragment_shaders_size);

        // Se compilan los shaders:

        glCompileShader (  vertex_shader_id);
        glCompileShader (fragment_shader_id);

        // Se comprueba que si la compilación ha tenido éxito:

        glGetShaderiv   (  vertex_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) show_compilation_error (  vertex_shader_id);

        glGetShaderiv   (fragment_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) show_compilation_error (fragment_shader_id);

        // Se crea un objeto para un programa:

        GLuint program_id = glCreateProgram ();

        // Se cargan los shaders compilados en el programa:

        glAttachShader  (program_id,   vertex_shader_id);
        glAttachShader  (program_id, fragment_shader_id);

        // Se linkan los shaders:

        glLinkProgram   (program_id);

        // Se comprueba si el linkage ha tenido éxito:

        glGetProgramiv  (program_id, GL_LINK_STATUS, &succeeded);
        if (!succeeded) show_linkage_error (program_id);

        // Se liberan los shaders compilados una vez se han linkado:

        glDeleteShader (  vertex_shader_id);
        glDeleteShader (fragment_shader_id);

        return (program_id);
    }

    void View::show_compilation_error (GLuint shader_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetShaderInfoLog (shader_id, info_log_length, NULL, &info_log.front ());

        cerr << info_log.c_str () << endl;

        #ifdef _MSC_VER
            //OutputDebugStringA (info_log.c_str ());
        #endif

        assert(false);
    }

    void View::show_linkage_error (GLuint program_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetProgramiv (program_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetProgramInfoLog (program_id, info_log_length, NULL, &info_log.front ());

        cerr << info_log.c_str () << endl;

        #ifdef _MSC_VER
            //OutputDebugStringA (info_log.c_str ());
        #endif

        assert(false);
    }

}
