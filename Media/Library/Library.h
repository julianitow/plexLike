#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <list>
#include <filesystem>
#include <magic.h>
#include "../Media.h"

class Library {
    public:
        Library();
        Library(std::string);
        std::string _name();
        void addMedia(Media);
        void addPath(std::string);
        std::list<Media> listMedia();
        void scanForFiles();
        bool persistDb(); //TODO persists data to db
    private:
        std::string name;
        std::list<Media> contents;
        std::list<std::string> paths;
        std::list<std::string> videoFiles;
};

#endif