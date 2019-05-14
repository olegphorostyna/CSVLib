#include "CsvTable.h"
usd::CsvTable::CsvTable(){    
}

usd::CsvTable::CsvTable(std::string file_name ):table_name_(file_name){
    loadTable(file_name);
}

void usd::CsvTable::loadTable(std::string file_name){
     std::ifstream file_to_parse(file_name);
     readCSV(file_to_parse);
     file_to_parse.close();
}

void usd::CsvTable::readCSV(std::istream &in) {    
    std::string row;    
    int line_count=0;    
    while (!in.eof()) {
        std::getline(in, row);
        if (in.bad() || in.fail()) {
            break;
        }
        Record record;
        if(line_count==0){
            readCSVRow(row,record,true);
            setMasterRecord(record);
        }else{
            readCSVRow(row,record,false);
            addRecord(record);  
        }
        line_count++;        
       
    }   
}

void usd::CsvTable::readCSVRow(const std::string &row, usd::Record& record, bool isMasterRecord) {
    usd::CsvTable::CSVState state = usd::CsvTable::CSVState::UnqoutedField;    
    std::string cell;
    size_t i = 0; // index of the current collumn
    for (char c : row) {
        switch (state) {
            case usd::CsvTable::CSVState::UnqoutedField:
                switch (c) {
                    case ',': {// end of field                             
                              if(isMasterRecord){
                                record.addColumn(cell, usd::Record::Type::STRING);
                              }else{
                                record.addColumn(getMasterRecordCol(i), usd::Record::Type::STRING);
                                record.setValue(getMasterRecordCol(i++),cell);
                              } 
                              cell.clear(); 
                              break;
                             }
                    case '"': state = usd::CsvTable::CSVState::QuotedField;
                              break;
                    default: cell.push_back(c);
                              break; }
                break;
            case usd::CsvTable::CSVState::QuotedField:
                switch (c) {
                    case '"': state = usd::CsvTable::CSVState::QuotedQuote;
                              break;
                    default:  cell.push_back(c);
                              break; }
                break;
            case usd::CsvTable::CSVState::QuotedQuote:
                switch (c) {
                    case ',': // , after closing quote                              
                              if(isMasterRecord){
                                record.addColumn(cell, usd::Record::Type::STRING);
                              }else{
                                record.addColumn(getMasterRecordCol(i), usd::Record::Type::STRING);
                                record.setValue(getMasterRecordCol(i++),cell);
                              } 
                              cell.clear(); 
                              state = usd::CsvTable::CSVState::UnqoutedField;
                              break;
                    case '"': // "" -> "
                              cell.push_back('"');
                              state = usd::CsvTable::CSVState::QuotedField;
                              break;
                    default:  // end of quote
                              state = usd::CsvTable::CSVState::UnqoutedField;
                              break; }
                break;
        }
    }    
}

std::string usd::CsvTable::getMasterRecordCol(int i){
    return table_.at(0).getCellName(i);
}

//returns number of columns
int  usd::CsvTable::getMasterRecordSize(){
    return table_.at(0).getCellCount();
}
//return number of rows
int  usd::CsvTable::getTableSize(){
    return table_.size();
}

void usd::CsvTable::setMasterRecord(usd::Record& m_record){
    if(table_.size()==0){
        m_record.setAsMasterRecord(true);
        table_.push_back(std::move(m_record));
    } else{
        throw MasterRecordRedefenition();
    }
}
void usd::CsvTable::addRecord(usd::Record& record){
    if(table_.size()!=0){
        table_.push_back(std::move(record));
    }else{
        throw MasterRecordNotDefined();
    }
}        
void usd::CsvTable::printTable(){    
    for(int i=0; i<table_.size(); i++){
        if(i==0) table_.at(i).printCellNames();
        table_.at(i).printRecord();
    }
}

usd::Record& usd::CsvTable::getMasterRecord(){
    return table_.at(0);
}
//get column values (without master record) 
std::vector<std::string> usd::CsvTable::getCol(std::string col_name){
    std::vector<std::string> to_ret;
    for(int i=1;i<this->getTableSize();i++){ 
        to_ret.push_back(table_.at(i).getValue(col_name));
    }
    return to_ret;
}
//get value from table by row index and column name
std::string usd::CsvTable::getCellValue(int row_idx, std::string col_name){    
    return table_.at(row_idx).getValue(col_name);
}

 usd::ResultSet usd::CsvTable::runQuery(Query& query){ 
    std::vector<std::string> target_cols;  
    usd::ResultSet result_set(this);
    if(query.properties_.isSelectAll()){
       target_cols=getMasterRecord().toStrVector();
    }else{
        target_cols=query.properties_.get_desired_cols();
   }    
    for(auto col :  target_cols){
        result_set.insert(col,0); // add master record in any case
        for(int i=1;i<this->getTableSize();i++){
            if(result_set_buffer.size()!=0){ //buffer was filed in where stage 
                for(int k=0;k<result_set_buffer.size();k++){
                    result_set.insert(col,result_set_buffer.at(k));
                }
                break;
            }
            if(query.properties_.isWhere()){ //where stage
                std::vector<std::string> to_compare = getCol(query.properties_.getWhereColName());
                 usd::LogicPredicate* predicate= query.properties_.getPredicate();
                for(int j=0;j<to_compare.size();j++){
                   if((*predicate)(to_compare.at(j), query.properties_.getWhererValue())){
                       result_set_buffer.push_back(j+1); //+1 compensate for master record
                   }      
                }
                if(result_set_buffer.size()!=0){ //buffer was filed in where stage 
                    for(int k=0;k<result_set_buffer.size();k++){
                        result_set.insert(col,result_set_buffer.at(k));
                    }
                break;
                }
            }
            
            result_set.insert(col,i); //add all
        }        
    }
    
   
    return result_set;  
   
    
    
}