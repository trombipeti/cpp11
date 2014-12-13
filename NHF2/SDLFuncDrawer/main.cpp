#include <cstdlib>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <cmath>

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // program main loop
    bool done = false;
    float d = 0.5f;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
            case SDL_QUIT:
                done = true;
                break;

            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    if(event.key.keysym.sym == SDLK_UP) {
                        d += 0.5f;
                    } else if(event.key.keysym.sym == SDLK_DOWN) {
                        d -= 0.5f;
                    }
                    break;
                }
            } // end switch
        } // end of message processing



        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        for(int x = 1;x<=640;++x) {
            aalineColor(screen,x-1,sin((x-1)/d)*100 * sin((x-1)/2*d) + 200,x,sin(x/d)*100 * sin(x/2*d) + 200,0xFFFFFF);
        }


        SDL_Flip(screen);
    } // end main loop


    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
