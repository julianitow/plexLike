#include "Movie.h"

Movie::Movie(int id, std::string title, double duration, int evaluation, int year, std::string sinopsis) {
    Media(id, title, duration, evaluation, year, sinopsis);
}

std::string Movie::_title() {
    return this->title;
}