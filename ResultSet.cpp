#include "ResultSet.h"
#include "CsvTable.h"

 usd::ResultSet::ResultSet(usd::CsvTable* tab):origin_table_(tab){}

void usd::ResultSet::insert(std::string col_name, int idx){
    ColsMap::iterator iter = cols_.find(col_name);    
    if(iter!=cols_.end()){
        iter->second.push_back(idx);
    }else{
         std::list<int> values;
         values.push_back(idx);         
         cols_.insert(std::make_pair(col_name,values));
         cols_sequence_.push_back(col_name);
    }   
}

void usd::ResultSet::printResultSet(){     
     for(int j=0;j<cols_sequence_.size();j++){         
         ColsMap::const_iterator col_iter = cols_.find(cols_sequence_.at(j));
         if(col_iter==cols_.end()) throw NoSuchColumn("No column "+cols_sequence_.at(j));
         std::list<int>::const_iterator val_iter = col_iter->second.begin();
        while(val_iter!=col_iter->second.end()){
            std::cout<<origin_table_->getCellValue(*val_iter,col_iter->first)<<std::endl;
            val_iter++;
        }
     } 
}

