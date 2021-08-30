#include "Media.h"

Media::Media() {}

Media::Media(int id, std::string title, double duration, int evaluation, int year, std::string sinopsis) {
    this->id = id;
    this->title = title;
    this->duration = duration;
    this->evaluation = evaluation;
    this->year = year;
    this->sinopsis = sinopsis;
}

void Media::setPath(std::string path) {
    this->path = path;
}