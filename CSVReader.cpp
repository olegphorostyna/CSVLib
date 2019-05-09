
#include "CsvTable.h"

int main(int argc, char *argv[]){
    
    usd::CsvTable table("test.csv");
    std::cout<<"Origin tbale"<<std::endl;
    table.printTable();
/*
    usd::Query test_get_cols = usd::Query::QueryBuilder().setCol("Name").setCol("Surname").build();
    usd::ResultSet result = table.runQuery(test_get_cols);
    std::cout<<"Result set"<<std::endl;
    result.printResultSet();

    std::cout<<std::endl<<std::endl<<std::endl;
    usd::Query test_get_all_cols = usd::Query::QueryBuilder().build();
    result = table.runQuery(test_get_all_cols);    
    std::cout<<"Result set"<<std::endl;
    result.printResultSet();
*/
    std::cout<<std::endl<<std::endl<<std::endl;
    usd::EqualTo predicate = usd::EqualTo();
    usd::Query test_where = usd::Query::QueryBuilder().where("Name","Illon",&predicate).build();
    usd::ResultSet result = table.runQuery(test_where);    
    std::cout<<"Result set"<<std::endl;
    result.printResultSet();
    
    return 0;
}