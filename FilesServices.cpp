#include "FilesServices.h"

std::list<std::filesystem::directory_entry> FilesServices::listDirContent(const char* path) {
    std::list<std::filesystem::directory_entry> files = std::list<std::filesystem::directory_entry>();
    for (const auto &file : std::filesystem::directory_iterator(path)) {
        files.push_back(file);
    }
    return files;
}