#include "Record.h"

usd::Record& usd::Record::addColumn(std::string col_name, usd::Record::Type type){ 

   std::unique_ptr<usd::Record::Cell> cell( new Cell(col_name, type));  
   usd::Record::row_.push_back(std::move(cell));
   return *this;
}


void usd::Record::printCellNames(){  
    for(int i=0; i< usd::Record::row_.size();i++){
        std::string type = usd::Record::row_.at(i)->type?"INT":"STR";
        std::cout<<usd::Record::row_.at(i)->name<<"("<<type<<")"<<"\t";
    }
    std::cout<<'\n';
}

void usd::Record::printRecord(){    
    for(int i=0;i<usd::Record::row_.size();i++){    
       usd::Record::Type type = usd::Record::row_.at(i)->type;      
       if(type==usd::Record::Type::INT){
            std::cout<<usd::Record::row_.at(i)->getInt()<<"\t\t";
       }else{
           std::cout<<usd::Record::row_.at(i)->getString()<<"\t\t";
       } 
    }
    std::cout<<'\n';
}

usd::Record& usd::Record::setValue(std::string col_name, std::string val){    
    for(int i = 0;i<usd::Record::row_.size();i++){
        if(usd::Record::row_.at(i)->getName()==col_name){                  
            usd::Record::row_.at(i)->setString(val);            
            return *this;
        }
    }
    throw NoSuchColumn();

}

usd::Record& usd::Record::setValue(std::string col_name, int val){    
    for(int i = 0;i<usd::Record::row_.size();i++){
        if(usd::Record::row_.at(i)->getName()==col_name){             
            usd::Record::row_.at(i)->setInt(val);
            return *this;
        }        
    }
    throw NoSuchColumn();
}

usd::Record::~Record(){
    
}

