#include "Query.h"

usd::Query::QueryProperties::QueryProperties():select_all_(true),
                                            where_predicate(nullptr), 
                                            distinct(false),
                                            greater_then_int(std::numeric_limits<int>::min()),
                                            smaller_then_int(std::numeric_limits<int>::min()){}   

std::vector<std::string>&  usd::Query::QueryProperties::get_desired_cols(){
    return cols_to_select;
}

bool usd::Query::QueryProperties::isSelectAll(){
    return select_all_;
}
//are "where" clause was used in a select statement
 bool usd::Query::QueryProperties::isWhere(){
     return where_predicate!=nullptr;
 } 

std::string usd::Query::QueryProperties::getWhereColName(){
    return where_col_name;
}
std::string usd::Query::QueryProperties::getWhererValue(){
    return where_value;
}
usd::LogicPredicate* usd::Query::QueryProperties::getPredicate(){
    return where_predicate;
}     

usd::Query::QueryBuilder& usd::Query::QueryBuilder::where(std::string col_name, std::string val_name, usd::LogicPredicate* predicate){
    q_prop.where_predicate = predicate;
    q_prop.where_col_name = col_name;
    q_prop.where_value = val_name;
    return *this;
}

usd::Query::QueryBuilder& usd::Query::QueryBuilder::setCol(std::string col){
     q_prop.select_all_=false;    
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
