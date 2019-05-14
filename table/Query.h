#ifndef QUERY
#define QUERY

#include <string>
#include <vector>
#include <stdarg.h>
#include <limits>
#include "predicate/Functor.h"
namespace usd{
    class Query{       
        private:
            //one of the basic CRUD querie              
            enum class QueryType{ 
                INSERT,
                SELECT,
                UPDATE,
                DELETE
            }; 
            class QueryProperties{
                private:
                    QueryProperties();             
                    QueryType type;
                    std::vector<std::string>  cols_to_select;                    
                    std::string where_col_name;
                    std::string where_value;
                    usd::LogicPredicate* where_predicate;
                    bool distinct;
                    bool select_all_;
                    int greater_then_int;
                    int smaller_then_int;
                    std::string greater_then_str;
                    std::string smaller_then_str;
                    friend class Query;
                    friend class QueryBuilder;   
                
                public:
                    std::vector<std::string>& get_desired_cols();                    
                    bool isSelectAll();
                    bool isWhere();
                    std::string getWhereColName();
                    std::string getWhererValue();
                    usd::LogicPredicate* getPredicate();                  
            };
            
        Query(const QueryProperties& prop): properties_(prop){}
            
        public:        
        class QueryBuilder{
            public:                                
                    QueryBuilder& setCol(std::string col);                                      
                    QueryBuilder& setDistinct(bool isDistinct);
                    QueryBuilder& where(std::string, std::string, LogicPredicate*);
                    QueryBuilder& setGreaterThan(int base);
                    QueryBuilder& setGreaterThan(std::string base);
                    QueryBuilder& setSmallerThan(int base);
                    QueryBuilder& setSmallerThan(std::string base);
                    Query build();
                private:
                    QueryProperties q_prop;
        }; 

            QueryProperties properties_;
    };
}

#endif
