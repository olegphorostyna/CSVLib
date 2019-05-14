#ifndef RECORD
#define RECORD

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include "exceptions/NoSuchColumn.h"
#include <cstring>
namespace usd{
    //Represent one record in a table
    class Record{  
        public:    
            Record(){}       
            ~Record() = default; 
            Record (const Record& r) = delete;
            Record& operator=(const Record& r)=delete;
            Record(Record&& r):row_(std::move(r.row_)),is_master_record_(r.is_master_record_){ }     
       
        enum Type{
            STRING,
            INT
        };
        private:
            struct Cell{                
                Cell(std::string n, Record::Type t):
                                                name(n),
                                                type(t){                                          
                                                };
                
              
                Cell(Cell&& c): name(c.name),
                                type(c.type),
                                data(c.data){
                    if(c.type == Record::Type::STRING){
                        c.data._str=nullptr;                       
                    }                               
                }
                
                ~Cell(){
                    if(type == Record::Type::STRING){
                        delete [] data._str;
                    }                    
                }

                std::string name;
                Record::Type type; 
                                             
                union {
                    int _int;
                    char* _str;
                } data;
                
                std::string getString(){                      
                    if(data._str ==nullptr){
                        return "";
                    }                 
                    return std::string(data._str);                     
                }

                std::string getName(){                    
                    return name;
                }

                int getInt(){
                    return data._int;
                }

                void setString(std::string in_str){                   
                    data._str = std::strcpy(new char[in_str.length()+1], in_str.c_str());                                           
                }

                void setInt(int in_int){
                    data._int=in_int;
                }
            };

            std::vector<std::unique_ptr<usd::Record::Cell>> row_;
            bool is_master_record_;
            
        public:
            Record& addColumn(std::string name, Record::Type type);
            Record& setValue(std::string col_name, std::string val);
            Record& setValue(std::string col_name, int val);            
            std::string getValue(std::string col_name);
            std::string getCellName(int);
            std::vector<std::string> toStrVector();
            int getCellCount();
            void printCellNames();
            void printRecord();
            void setAsMasterRecord(bool);
            bool isMasterRecord();
            bool contains(std::string);
    };
}

#endif
