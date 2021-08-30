#include "MediaManager.h"

MediaManager::MediaManager() {}

void MediaManager::addLibrary(Library lib) {
    this->libraries.push_back(lib);
}

std::list<Library> MediaManager::_libraries() {
    return this->libraries;
}