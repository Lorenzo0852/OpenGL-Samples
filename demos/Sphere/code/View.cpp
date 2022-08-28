
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
        "uniform float t;     "          
		"uniform float radius;"
		""
        "layout (location = 0) in vec2 vertex_coordinates;"
        ""
        "out vec3 front_color;"
        ""
        "void main()"
        "{"
		"   vec4 euclidean_coords = vec4(radius * sin(vertex_coordinates.x) * cos(vertex_coordinates.y),"
		"							radius * sin(vertex_coordinates.x) * sin(vertex_coordinates.y),"
		"							radius * cos(vertex_coordinates.x), 1.0);"
        "   vec4 model_view_vertex = model_view_matrix * euclidean_coords;"
        "   front_color = vec3(1,1,1);"
        "   gl_Position = projection_matrix * model_view_vertex;"
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
        angle(0), time(0)
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
        time_id              = glGetUniformLocation(program_id,  "t");

		radius_id			 = glGetUniformLocation(program_id, "radius");

        resize (width, height);
    }

    void View::update ()
    {
        position += 0.01f;
        angle += 0.02f;
        time += 0.04f;
    }

    void View::render ()
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Se rota el cubo y se empuja hacia el fondo:

        glm::mat4 model_view_matrix(1);

        model_view_matrix = glm::translate (model_view_matrix, glm::vec3(0.f, 4.f, -25.f));
        model_view_matrix = glm::rotate    (model_view_matrix, angle, glm::vec3(1.f, 1.f, 1.f));

        glUniformMatrix4fv (model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));

        glUniform1f(time_id, time);
		glUniform1f(radius_id, plane.radius);

        // Se dibuja el plano:

        plane.render ();
    }

    void View::resize (int width, int height)
    {
        glm::mat4 projection_matrix = glm::perspective (20.f, GLfloat(width) / height, 1.f, 5000.f);

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
