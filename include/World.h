#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>
#include "Object.h"

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
    void update_obj(string);
    void update_all();
    void print_coords(std::ostream&);
    std::unordered_map<string, Object*> get_display_file();

 protected:
    World() {}
};

#endif /* WORLD_H */