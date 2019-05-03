#include "Query.h"



usd::Query::QueryBuilder& usd::Query::QueryBuilder::setCol(std::string col){    
     q_prop.cols_to_select.push_back(col);
     return *this;
}
 usd::Query::QueryBuilder& usd::Query::QueryBuilder::setDistinct(bool isDistinct){
     q_prop.distinct=isDistinct;
}
usd::Query::QueryBuilder& usd::Query::QueryBuilder::setGreaterThan(int base){
    q_prop.greater_then_int =base;
}
usd::Query::QueryBuilder& usd::Query::QueryBuilder::setGreaterThan(std::string base){
    q_prop.greater_then_str=base;
}
usd::Query::QueryBuilder& usd::Query::QueryBuilder::setSmallerThan(int base){
    q_prop.smaller_then_int=base;
}
usd::Query::QueryBuilder& usd::Query::QueryBuilder::setSmallerThan(std::string base){
    q_prop.smaller_then_str=base;         
}
usd::Query usd::Query::QueryBuilder::build(){
    return Query(q_prop);   
}