#include "UserImplementationTets.h"

usd::UserImplementationTets::UserImplementationTets(int i, 
    std::string n, std::string s, std::string a, std::string p): id(i), 
                                                                name(n), 
                                                                surrname(s), 
                                                                address(a),
                                                                phone_number(p) { }


std::vector<std::string> usd::UserImplementationTets::toCSV(){
    std::vector<std::string> csv_row;
    csv_row.push_back(std::to_string(id));
    csv_row.push_back(name);
    csv_row.push_back(surrname);
    csv_row.push_back(address);
    csv_row.push_back(phone_number);
    return csv_row;
    
}

