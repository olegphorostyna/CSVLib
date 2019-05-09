#ifndef CSVALIZABLE
#define CSVALIZABLE

#include <vector>
#include <string>
namespace usd{
    class SCValizable{
        public:
            virtual std::vector<std::string> toCSV() = 0;
    };
}

#endif