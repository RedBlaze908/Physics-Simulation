#include "window/window.h"

int main() {
    std::unique_ptr<Window> wn = std::make_unique<Window>();
    
    wn->Run();
    
    return 0;
}