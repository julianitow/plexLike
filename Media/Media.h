#ifndef MEDIA_H
#define MEDIA_H
#include <iostream>
#include <filesystem>

class Media {
    protected:
        int id;
        std::string title;
        double duration;
        int evaluation;
        std::string sinopsis;
        int year;
        std::filesystem::directory_entry file;
        //FIXME FILE TYPE FOR file attribute or string path 
    
    public:
        Media();
        Media(std::filesystem::directory_entry);
        explicit Media(int, std::string, double, int, int, std::string);
        void setPath(std::filesystem::directory_entry);
        std::filesystem::directory_entry _file();
};

#endif