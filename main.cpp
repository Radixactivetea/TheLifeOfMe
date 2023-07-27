#include "Animation.h"

int main()
{
    Animation animation("OPENGL_3D", 1000, 800, 4, 4, false);

    //Main loop
    while (!animation.getWindowShouldClose())
    {
        animation.update();
        animation.render();
    } 
    
    return 0;
}