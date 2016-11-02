#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stack>
#include <vector>

#include "RPNParser.h"

#define WIDTH  640
#define HEIGHT 480


/**\brief Koordinátarendszert rajzol a képernyõre a megadott méretekkel, (0,0,0) középpontal.
 * \param width A kirajzolt koordinátarendszer szélessége, ennek a felével balra/jobbra az origótól fog befejezõdni.
 * \param height Mint a width, csak az y koordináta mentén.
 * \param res Az osztás nagysága
 */
static void koordinatarendszer(float width, float height, float res)
{
    glLineWidth(1);
    glBegin(GL_LINES);
    for(float fi = -0.5*width; fi < 0.5*width; fi += res)
    {
        if(std::abs(fi) < res)
        {
            glColor3f(0,0,0);
        }
        else
        {
            glColor3f(0.4,0.4,0.4);
        }
        glVertex3f(fi, 0.5*height, 0);
        glVertex3f(fi, -0.5*height, 0);

        glVertex3f(0.5*height, fi, 0);
        glVertex3f(-0.5*height, fi, 0);
    }
    glEnd();
}

float z = -10;

/**\brief Újrarajzolja az ablakot.
 * \param parser A kirajzolt függvény RPN leírását tartalmazó értelmezõ objektum pointere.
 *        Ezt kiértékelve fogja elõállítani a kirajzolt görbe pontjait.
 */
static void repaint(RPNParser* parser)
{

    /* Clear the color plane and the z-buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,10,
              0,0,0,
              0,1,0);

    /* Move the object away from the camera */
    glTranslatef(0.0f, 0.0f, z);

    koordinatarendszer(50,50,1);

    glColor3f(0.0f,0.1f,0.6f);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    for(float i = -20.0f; i <= 20.0f; i += 0.01)
    {
        float y0 = 0, y1 = 0;
        try {
            y0 = parser->evaluate(i-0.01);
            y1 = parser->evaluate(i);
        } catch(std::logic_error& e) {
            std::cout << e.what() << std::endl;
        }
        y0 = (std::isnan(y0) ? 0 : y0);
        y1 = (std::isnan(y1) ? 0 : y1);
        glVertex3f(i-0.01, y0 , 0);
        glVertex3f(i,  y1, 0);
    }
    glEnd();

    /* finally, swap the back and front buffers */
    SDL_GL_SwapBuffers();
}


static void setup_sdl()
{
    const SDL_VideoInfo* video;

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /* Quit SDL properly on exit */
    atexit(SDL_Quit);

    /* Get the current video information */
    video = SDL_GetVideoInfo( );
    if( video == NULL )
    {
        fprintf(stderr, "Couldn't get video information: %s\n", SDL_GetError());
        exit(1);
    }

    /* Set the minimum requirements for the OpenGL window */
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* Note the SDL_DOUBLEBUF flag is not required to enable double
     * buffering when setting an OpenGL video mode.
     * Double buffering is enabled or disabled using the
     * SDL_GL_DOUBLEBUFFER attribute.
     */
    if( SDL_SetVideoMode( WIDTH, HEIGHT, video->vfmt->BitsPerPixel, SDL_OPENGL ) == 0 )
    {
        fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
        exit(1);
    }
}


static void setup_opengl()
{
    float aspect = (float)WIDTH / (float)HEIGHT;

    /* Make the viewport cover the whole window */
    glViewport(0, 0, WIDTH, HEIGHT);

    /* Set the camera projection matrix:
     * field of view: 90 degrees
     * near clipping plane at 0.1
     * far clipping plane at 100.0
     */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, aspect, 0.1, 100.0);


    /* We're done with the camera, now matrix operations
     * will affect the modelview matrix
     * */
    glMatrixMode(GL_MODELVIEW);

    /* set the clear color to gray */
    glClearColor(0.5, 0.5 ,0.5, 0);

    /* We want z-buffer tests enabled*/
    glEnable(GL_DEPTH_TEST);

    /* Do draw back-facing polygons*/
    glDisable(GL_CULL_FACE);
}


static void main_loop(RPNParser *parser)
{
    SDL_Event event;

    while (1)
    {
        /* process pending events */
        while( SDL_PollEvent( &event ) )
        {
            switch( event.type )
            {
            case SDL_KEYDOWN:
                switch ( event.key.keysym.sym )
                {
                case SDLK_ESCAPE:
                    exit(0);
                    break;

                case SDLK_UP:
                    z -= 1;
                    break;

                case SDLK_DOWN:
                    z += 1;
                    break;

                default:
                    //no default key processing
                    //(stops compiler warnings for unhandled SDL keydefs
                    break;
                }
                break;

            case SDL_QUIT:
                exit (0);
                break;
            }
        }

        /* update the screen */
        repaint(parser);

        /* Wait 50ms to avoid using up all the CPU time */
        SDL_Delay( 50 );
    }
}


int main(int argc, char* argv[])
{
//    std::string expression = "2.71 0 1 - x * ^";
    std::string expression = "x sgn 3.5 x 5 / 2 ^ * sin abs 10 * *";

    RPNParser parser{expression};

    setup_sdl();

    setup_opengl();

    main_loop(&parser);

    return 0;
}
