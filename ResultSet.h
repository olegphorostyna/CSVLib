#ifndef RESULT_SET_H
#define RESULT_SET_H

#include <unordered_map>
#include <list>
#include <string>
#include <vector>
#include "NoSuchColumn.h"


using  ColsMap = std::unordered_map<std::string, std::list<int>>;
namespace usd{
    class CsvTable;
class ResultSet{
    private:
        ColsMap cols_;
        usd::CsvTable* origin_table_;
        std::vector<std::string> cols_sequence_;        
    public:
        ResultSet(usd::CsvTable*);       
        void insert(std::string, int);
        void printResultSet();
};
}

#endif