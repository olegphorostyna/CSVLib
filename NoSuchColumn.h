#include <exception>

class NoSuchColumn : public std::exception{
    const char* what() const noexcept{
        return "No column with such name. Please provide othr valid name";
    }
};