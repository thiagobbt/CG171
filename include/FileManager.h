#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <unordered_map>
#include "Object.h"

class FileManager {
 public:
 	typedef struct {
        std::string name;
        std::vector<std::string> args;
    } command;

 	static void toObj(const std::string& filename, const std::unordered_map<std::string, Object*>& display_file);
 	static void fromObj(const std::string&);
 private:
 	static std::vector<command> parseCommands(const std::string&);
};

#endif /* FILE_MANAGER_H */
