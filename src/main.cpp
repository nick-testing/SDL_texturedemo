#include "ButtonDemo.h"
#include "SDLAnimationDemo.h"
#include "SDLRenderDemo.h"

int main(int argc, char* argv[]) {
    ButtonDemo r;
    SDLAnimationDemo a;
    SDLRenderDemo d;
    
    r.Run();
    a.Run();
    d.Run();
    return 0;
}