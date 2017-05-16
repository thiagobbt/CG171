#include "FileManager.h"
#include "Window.h"
#include "Controller.h"
#include <fstream>
#include <sstream>
#include <string>

void FileManager::toObj(const std::string& filename, const std::unordered_map<std::string, Object*>& display_file) {
	std::ofstream out(filename, std::ofstream::trunc);
	std::cout << filename << std::endl;
    int n_coords = 0;

    for (auto obj : display_file) {
        n_coords += obj.second->num_coords();
        out << "# " << obj.first << std::endl;
        out << *(obj.second);
    }

    out << "# window" << std::endl;
    Window::instance().print_coords(out);

    // out << "mtllib materials.mtl" << std::endl;
    out << "o window" << std::endl;
    out << "w " << n_coords + 1 << " " << n_coords + 2 << std::endl;

    int coord_counter = 1;

    for (auto obj : display_file) {
        int obj_n_coords = obj.second->num_coords();
        out << "o " << obj.first << std::endl;
        out << (obj_n_coords == 1? "p" : "l");

        for (int i = coord_counter; i < coord_counter + obj_n_coords; i++) {
            out << " " << i;
        }

        if (obj_n_coords > 2) out << " " << coord_counter;

        coord_counter += obj_n_coords;

        out << std::endl;
    }

    out.close();
};

void FileManager::fromObj(const std::string& filename) {
	auto commands = parseCommands(filename);
    std::vector<Coordinate> vertices;
	std::string name;
    std::vector<Coordinate> wireframe_vertices;
    for (auto& cmd : commands) {
        if (cmd.name == "v") {
            vertices.emplace_back(stod(cmd.args[0]), stod(cmd.args[1]), stod(cmd.args[2]));
        } else if (cmd.name == "o") {
            if (wireframe_vertices.size() > 0) {
                Controller::add_polygon(name, wireframe_vertices, {0, 0, 0}, false);
                wireframe_vertices.clear();
            }
            name = cmd.args[0];
        } else if (cmd.name == "p") {
            Controller::add_point(name, vertices[stoi(cmd.args[0]) - 1], {0, 0, 0});
        } else if (cmd.name == "l") {
            if (cmd.args.size() == 2) {
                Controller::add_line(name, vertices[stoi(cmd.args[0]) - 1], vertices[stoi(cmd.args[1]) - 1], {0, 0, 0});
            } else {
                std::vector<Coordinate> polygon_vertices;
                for (auto index : cmd.args) {
                    polygon_vertices.push_back(stoi(index) - 1);
                }
                Controller::add_polygon(name, polygon_vertices, {0, 0, 0}, false);
            }
        } else if (cmd.name == "f") {
            for (auto index : cmd.args) {
                wireframe_vertices.push_back(vertices[stoi(index) - 1]);
            }
        }
    }
};

std::vector<FileManager::command> FileManager::parseCommands(const std::string& filename) {
    std::ifstream input(filename);
    std::string line;
    std::vector<FileManager::command> commandList;
    while (std::getline(input, line)) {
        if (line.size() == 0 || line[0] == '#') {
            continue;
        }

        std::istringstream stream(line);
        std::string command;
        std::vector<std::string> args;
        std::string arg;

        stream >> command;
        while (stream >> arg) {
            args.push_back(arg);
        }
        commandList.push_back({command, args});
    }

    return commandList;
};
