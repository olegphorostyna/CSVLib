#include<string>
#include<vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include "NoSuchColumn.h"
#include <cstring>
namespace usd{
    //Represent one record in a table
    class Record{  
        public:
            ~Record();       
       
        enum Type{
            STRING,
            INT
        };
        private:
            struct Cell{                
                Cell(std::string n, Record::Type t):
                                                name(n),
                                                type(t){};
                
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
                    //std::cout<<"string returned"<<std::endl;
                    if(data._str ==nullptr){
                        return "";
                    }                 
                    return std::string(data._str);
                }

                std::string getName(){
                    //std::cout<<"returning name: "<<name;
                    return name;
                }

                int getInt(){
                    return data._int;
                }

                void setString(std::string in_str){
                   // std::cout<<"Trying to set string val"<<std::endl;
                    data._str = std::strcpy(new char[in_str.length()+1], in_str.c_str()); 
                   // std::cout<<"Value seted"<<std::endl;                          
                }

                void setInt(int in_int){
                    data._int=in_int;
                }
            };

            std::vector<std::unique_ptr<usd::Record::Cell>> row_;
            
        public:
            Record& addColumn(std::string name, Record::Type type);
            Record& setValue(std::string col_name, std::string val);
            Record& setValue(std::string col_name, int val);
            void printCellNames();
            void printRecord();
    };
}