#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <list>
#include <filesystem>
#include "../Media.h"

class Library {
    public:
        Library();
        void addMedia(Media);
        void addPath(std::string);
        std::list<Media> listMedia();
        void scanForFiles();
        bool persistDb(); //TODO persists data to db
    private:
        std::string title;
        std::list<Media> contents;
        std::list<std::string> paths;
};

#endif