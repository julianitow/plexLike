#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

#include <iostream>
#include <list>

#include "../Library/Library.h"

class MediaManager {
    private:
        std::list<Library> libraries;
    public:
       explicit MediaManager();
       void addLibrary(Library);
       std::list<Library> _libraries();

       //TODO scan all libs for files method 
};


#endif