#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>

#include "Media.h"

class Movie : public Media {
    public:
        Movie(int, std::string, double, int, int, std::string);
        std::string _title();
};

#endif