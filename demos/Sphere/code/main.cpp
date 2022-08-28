
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2014.05

#include <cassert>
#include <glad/glad.h>
#include <SFML/Window.hpp>
#include "View.hpp"

using namespace sf;
using namespace example;

int main ()
{
    // Se crea la ventana de SFML, que es donde se creará el contexto de OpenGL:

    Window window(VideoMode(800, 600), "Sin Plane", Style::Default, ContextSettings(0, 0, 0, 3, 3, ContextSettings::Core));
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(120);

    // Una vez se ha creado el contexto de OpenGL ya se puede inicializar GLAD:

    GLenum glad_initialization =  gladLoadGL ();

    assert(glad_initialization != 0);

    // GLAD se inicializa antes de crear view porque view ya usa extensiones de OpenGL:

    View view(800, 600);

    window.setVerticalSyncEnabled (true);

    bool running = true;

    do
    {
        Event event;

        while (window.pollEvent (event))
        {
            switch (event.type)
            {
                case Event::Closed:
                {
                    running = false;
                    break;
                }

                case Event::Resized:
                {
                    Vector2u window_size = window.getSize ();

                    view.resize (window_size.x, window_size.y);

                    break;
                }
            }
        }

        view.update ();
        view.render ();

        window.display ();
    }
    while (running);

    return EXIT_SUCCESS;
}
