#include "partials/solidPrinciples.h"
#include "partials/pointersRecal.h"
#include "partials/runMVC.h"

#ifdef _WIN32
#include "console/loader.h"
#include "console/consoleArtRunner.h"
#endif

int main()
{
    // uncomment to run the sample

    // How are the pointers work
    //pointersRecall();

    // Some words about patterns and solid principles
    //solidPrinciples();

    // An MVC pattern
    runMVC();

    // simple async loader
    //auto loaderAsync = runLoaderAsync();
    //loaderAsync.get();

    // run console animation for shapes
#ifdef _WIN32
    runConsoleArt();
#endif
}