#ifndef MASTER_RECORD_NOT_FOUND
#define MASTER_RECORD_NOT_FOUND

#include <exception>

class  MasterRecordNotDefined : public std::exception{
    const char* what() const noexcept{
        return "Master record not defined! Please set master record first";
    }

};

#endif