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
            //TODO check if file is video 
            magic_t myt = magic_open(MAGIC_CONTINUE | MAGIC_ERROR | MAGIC_DEBUG | MAGIC_MIME);
            magic_load(myt, NULL);
            auto file = magic_file(myt, NULL);
            if (file == nullptr) {
                std::cerr << magic_error(myt) << std::endl;
            } else {
                std::cout << file << ' ' << file << std::endl;
            }
            std::cout << filePath << ": " << file << std::endl;
            magic_close(myt);
        }
    }
}