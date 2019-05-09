#ifndef CSV_TABLE
#define CSV_TABLE

#include "Record.h"
#include "Query.h"
#include "ResultSet.h"
#include "MasterRecordRedefenition.h"
#include "MasterRecordNotDefined.h"
#include <fstream>
#include <stdexcept>

namespace usd {
class ResultSet;
class CsvTable{
    private:
        std::string table_name_;
        std::vector<usd::Record> table_;
        std::vector<int> result_set_buffer;
    public:
        CsvTable();
        CsvTable(std::string);
        enum class CSVState {
            UnqoutedField,
            QuotedField,
            QuotedQuote
        };      
        void loadTable(std::string);
        void createTable(std::string);
        void setMasterRecord(usd::Record&);
        int  getMasterRecordSize();
        int  getTableSize();
        std::vector<std::string> getCol(std::string);
        Record& getMasterRecord();
        std::string getCellValue(int,std::string);
        std::string getMasterRecordCol(int);
        void addRecord(usd::Record&);                
        void printTable();
        ResultSet runQuery(Query&);
    private:        
        void readCSV(std::istream&);
        void readCSVRow(const std::string&, usd::Record&, bool);

};
}
#endif