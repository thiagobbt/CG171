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
    bool add_object(string, Object*);
    void delete_object(string);
    void clear();    
};

#endif /* WORLD_H */