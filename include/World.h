/* copyright vfreitas & thiagobbt */

#ifndef WORLD_H
#define WORLD_H

#include "Object.h"
#include <unordered_map>

using std::string;

class World {
 private:
    std::unordered_map<string, Object*> display_file;

 public:
    World() {}
    ~World();
    bool add_obj(string, Object*);
    void delete_obj(string);
    void clear();    
    void redraw();
};

#endif /* WORLD_H */