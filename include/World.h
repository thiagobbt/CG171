/* copyright vfreitas & thiagobbt */

#ifndef WORLD_H
#define WORLD_H

#include "Object.h"
#include "Window.h"

class World {
 private:
    std::list<const Object&> display_file;
    Window& window;

 public:
    World(const World&);
    World(Window&);

};

#endif /* WORLD_H */