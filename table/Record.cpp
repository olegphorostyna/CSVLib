#include "Record.h"

usd::Record& usd::Record::addColumn(std::string col_name, usd::Record::Type type){ 
   std::unique_ptr<Cell> cell( new Cell(col_name, type));  
   row_.push_back(std::move(cell));   
   return *this;
}


void usd::Record::printCellNames(){  
    for(int i=0; i< row_.size();i++){
        std::string type = row_.at(i)->type?"INT":"STR";
        std::cout<<row_.at(i)->name<<"("<<type<<")"<<"\t";
    }
    std::cout<<'\n';
}

void usd::Record::printRecord(){    
    for(int i=0;i<row_.size();i++){    
       Type type = row_.at(i)->type;      
       if(type==Type::INT){
            std::cout<<row_.at(i)->getInt()<<"\t\t";
       }else{           
           std::cout<<row_.at(i)->getString()<<"\t\t";
       } 
    }
    std::cout<<'\n';
}

usd::Record& usd::Record::setValue(std::string col_name, std::string val){     
    for(int i = 0;i<row_.size();i++){
        if(row_.at(i)->getName()==col_name){                  
            row_.at(i)->setString(val);            
            return *this;
        }
    }
    throw NoSuchColumn(col_name);

}

usd::Record& usd::Record::setValue(std::string col_name, int val){    
    for(int i = 0;i<row_.size();i++){
        if(row_.at(i)->getName()==col_name){             
            row_.at(i)->setInt(val);
            return *this;
        }        
    }
    throw NoSuchColumn(col_name);
}
std::string usd::Record::getCellName(int i){
    return row_.at(i)->getName();
}

std::string usd::Record::getValue(std::string col_name){
    
    for(int i = 0;i<row_.size();i++){           
         if(row_.at(i)->getName().compare(col_name)==0){            
            return row_.at(i)->getString();
        }
    }
    throw NoSuchColumn(col_name);    
}

int usd::Record::getCellCount(){
    return row_.size();
}

void usd::Record::setAsMasterRecord(bool is_master_record){
    is_master_record_=is_master_record;
}
bool usd::Record::isMasterRecord(){
    return is_master_record_;    
}
//return true if record contain specifeid value
bool usd::Record::contains(std::string search_val){
     for(int i = 0;i<row_.size();i++){           
         if(row_.at(i)->getString().compare(search_val)==0){            
            return true;
        }
    }
    return false;
}
std::vector<std::string> usd::Record::toStrVector(){
    std::vector<std::string> to_ret;
    if(is_master_record_){       
        for(int i=0;i<row_.size();i++){
            to_ret.push_back(row_.at(i)->getName()); 
        } 
    }else{
        for(int i=0;i<row_.size();i++){
            to_ret.push_back(row_.at(i)->getString()); 
        } 
    }    
    return to_ret;
}

 

