#include "Table.h"



void usd::Table::setMasterRecord(usd::Record m_record){
    if(table_.size()==0){
        table_.push_back(m_record);
    } else{
        throw MasterRecordRedefenition();
    }
}
void usd::Table::addRecord(usd::Record record){
    if(table_.size()!=0){
        table_.push_back(record);
    }else{
        throw MasterRecordNotDefined();
    }
}        
void usd::Table::printTable(){
    for(int i; i<table_.size();i++){
        
    }
}
