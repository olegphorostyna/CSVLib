#include "Record.h"
#include "MasterRecordRedefenition.h"
#include "MasterRecordNotDefined.h"
namespace usd {
class Table{
    private:
        std::vector<usd::Record> table_;
    public:
        void setMasterRecord(usd::Record);
        void addRecord(usd::Record);
        void printTable();
};
}