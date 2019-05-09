#ifndef MASTER_RECORD_REDEFENITION
#define MASTER_RECORD_REDEFENITION

#include <exception>

class  MasterRecordRedefenition : public std::exception{
    const char* what() const noexcept{
        return "Master record of a table is allready defined!";
    }

};

#endif