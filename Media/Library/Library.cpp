#include "Library.h"

Library::Library(){
    this->contents = std::list<Media>();
}

void Library::addMedia(Media media) {
    this->contents.push_back(media);
}

std::list<Media> Library::listMedia() {
    return this->contents;
}

void Library::addPath(std::string path) {
    this->paths.push_back(path);
}

void Library::scanForFiles() {
    //TODO filesystem scan
    for(std::string& path : this->paths) {
        for(auto& filePath : std::filesystem::directory_iterator(path)){
            std::cout << filePath << std::endl;
        }
    }
}