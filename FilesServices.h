#include <iostream>
#include <filesystem>
#include <list>

class FilesServices {
    private:
        // DIR* path = nullptr;
    public:
        static std::list<std::filesystem::directory_entry> listDirContent(const char*);
};