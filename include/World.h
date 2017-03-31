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
 	static World& instance();
    ~World();
    bool add_obj(string, Object*);
    void delete_obj(string);
    void move_obj(string, utils::Matrix&);
    void scale_obj(string, utils::Matrix&);
    void rotate_obj(string, utils::Matrix&, Coordinate&, bool);
    void clear();    
    void redraw();
    const Object& obj(const string&);
    void update_obj(string, const utils::Matrix&);
    void update_all(const utils::Matrix&);

 protected:
    World() {}

};

#endif /* WORLD_H */