//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();

bool loadMedia();

void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gXOut = NULL;

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        // Create a window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    gXOut = SDL_LoadBMP("./x.bmp");
    if(gXOut == NULL)
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

void close()
{
    // Deallocate surface
    SDL_FreeSurface(gXOut);
    gXOut = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsytems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    if(!init())
    {
        printf("Failed to initialize!\n");
    } else {
        //Load Media
        if(!loadMedia())
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit )
            {
                 //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //Show the event type
                    printf("Pressed %u\n", e.type);

                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }

                //Apply the image
                SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}