#include "../SCValizable.h"
#include <string>
#include <vector>
namespace usd{
    class UserImplementationTets : public usd::SCValizable{
        private:        
            int id;
            std::string name;
            std::string surrname;
            std::string address;
            std::string phone_number;
        public:
            UserImplementationTets(int id, 
                                    std::string name,
                                    std::string surrname,
                                    std::string address,
                                    std::string phone_number);
            
            
            std::vector<std::string> toCSV();

                    

    };
}