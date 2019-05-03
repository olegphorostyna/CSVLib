#include <exception>

class  MasterRecordNotDefined : public std::exception{
    const char* what() const noexcept{
        return "Master record not defined! Please set master record first";
    }

};