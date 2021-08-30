#ifndef MEDIA_H
#define MEDIA_H
#include <iostream>

class Media {
    protected:
        int id;
        std::string title;
        double duration;
        int evaluation;
        std::string sinopsis;
        int year;
        std::string path;
        //FIXME FILE TYPE FOR file attribute or string path 
    
    public:
        Media();
        explicit Media(int, std::string, double, int, int, std::string);
        void setPath(std::string path);
};

#endif