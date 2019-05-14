#ifndef NO_SUCH_COLUMN
#define NO_SUCH_COLUMN

#include <exception>
#include <string>

class NoSuchColumn : public std::exception{
    
   
    
    public:
    NoSuchColumn(std::string col_name): col_name_(col_name){

    }     
    std::string col_name_; 
    const char* what() const noexcept{ 
        return col_name_.c_str();
    }
};

#endif