#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>   // for system()

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <project_name>\n";
        return 1;
    }

    std::string folder = argv[1];
    fs::path project(folder);

    if (fs::exists(project)) {
        std::cerr << "Folder already exists!\n";
        return 1;
    }

    // Create folders
    fs::create_directories(project / "src");
    fs::create_directories(project / "build");

    // Write CMakeLists.txt
    std::ofstream cmake(project / "CMakeLists.txt");
    cmake << "cmake_minimum_required(VERSION 3.10)\n";
    cmake << "project(" << folder << " LANGUAGES CXX)\n";
    cmake << "set(CMAKE_CXX_STANDARD 11)\n\n";
    cmake << "add_executable(" << folder << " src/main.cpp)\n";
    cmake.close();

    // Write main.cpp
    std::ofstream main(project / "src/main.cpp");
    main << "#include <iostream>\n\n";
    main << "int main() {\n";
    main << "    std::cout << \"Hello World\" << std::endl;\n";
    main << "    return 0;\n";
    main << "}\n";
    main.close();

    // Initialize git repo
    std::string git_cmd = "git init " + folder;
    system(git_cmd.c_str());

    std::cout << "Project " << folder << " created successfully with Git initialized!\n";
}

