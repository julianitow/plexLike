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
    for(std::string& path : this->paths) {        
        for(auto& fileSys : std::filesystem::recursive_directory_iterator(path)){
            // if(fileSys.is_directory()) continue;
            magic_t myt = magic_open(MAGIC_CONTINUE | MAGIC_ERROR | MAGIC_MIME);
            magic_load(myt, NULL);
            const char* file = magic_file(myt, fileSys.path().c_str());
            if (file == nullptr) {
                std::cerr << magic_error(myt) << std::endl;
            } else {
                std::string fileStr = std::string(file); 
                if(fileStr.find("video") != std::string::npos) {
                    this->videoFiles.push_back(fileSys.path());
                }
            }
            magic_close(myt);
        }
    }

    for(auto path : this->videoFiles) {
        std::cout << path << std::endl;
    }
}