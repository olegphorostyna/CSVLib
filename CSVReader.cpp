#include <istream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "test_impl/UserImplementationTets.h"
#include "Query.h"
#include "Record.h"

using type = usd::Record::Type;

enum class CSVState {
    UnqoutedField,
    QuotedField,
    QuotedQuote
};

std::vector<std::string> readCSVRow(const std::string &row) {
    CSVState state = CSVState::UnqoutedField;
    std::vector<std::string> fields {""};
    size_t i = 0; // index of the current field
    for (char c : row) {
        switch (state) {
            case CSVState::UnqoutedField:
                switch (c) {
                    case ',': // end of field
                              fields.push_back(""); i++;
                              break;
                    case '"': state = CSVState::QuotedField;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedField:
                switch (c) {
                    case '"': state = CSVState::QuotedQuote;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedQuote:
                switch (c) {
                    case ',': // , after closing quote
                              fields.push_back(""); i++;
                              state = CSVState::UnqoutedField;
                              break;
                    case '"': // "" -> "
                              fields[i].push_back('"');
                              state = CSVState::QuotedField;
                              break;
                    default:  // end of quote
                              state = CSVState::UnqoutedField;
                              break; }
                break;
        }
    }
    return fields;
}


std::vector<std::vector<std::string>> readCSV(std::istream &in) {
    std::vector<std::vector<std::string>> table;
    std::string row;
    while (!in.eof()) {
        std::getline(in, row);
        if (in.bad() || in.fail()) {
            break;
        }
        auto fields = readCSVRow(row);
        table.push_back(fields);
    }
    return table;
}

void writeCSV(std::string file_name, usd::SCValizable& to_csv ){
    std::ofstream file_to_write;
    file_to_write.open(file_name, std::fstream::app);
    std::vector<std::string> row = to_csv.toCSV(); 
    for(int i=0;i<row.size();i++){
         file_to_write<<"\""<<row.at(i)<<"\"";
         if(i!=(row.size()-1)){
              file_to_write<<",";
         }
    }  
    file_to_write<<std::endl;
    file_to_write.close();
}

int main(int argc, char *argv[]){
    std::ifstream file_to_parse(argv[argc-1]);
    if(argc!=2) {
        std::cout<<"PLease provide file to parse"<<std::endl;
        return 0;
    }
    for(auto const&  row: readCSV(file_to_parse)){
        for(auto const& value: row) {
            std::cout<< value<<"    ";
        }
        std::cout<<std::endl;
    }
    file_to_parse.close();

    usd::UserImplementationTets new_user(1,"Jhon","Wick","Lviv,Stryiska,52","0878367278");
    usd::UserImplementationTets new_user2(2,"Semuele","Ketlo","Some","08783423478");
    usd::UserImplementationTets new_user3(3,"Willkoks","Pert","Think","0678798578");
    
    writeCSV("newFile", new_user);   
    writeCSV("newFile", new_user2);  
    writeCSV("newFile", new_user3);   

    usd::Query simpleQuerry  = usd::Query::QueryBuilder().
                                            setCol("Name").
                                            setCol("Ammount").
                                            setDistinct(true).
                                            setSmallerThan(1000).build();
    
    usd::Record record;   
    record.addColumn("Index", type::INT);
    record.addColumn("Age",type::INT);
    record.addColumn("Name",type::STRING);
     record.addColumn("Surname",type::STRING); 

    record.printCellNames();
    //record.setValue("Index",1).setValue("Name","Oleg").setValue("Age", 26);
    record.setValue("Index",1).setValue("Age",20).setValue("Name","Andrew").setValue("Surname","Jhony"); 
    //record.setValue("Index",1).setValue("Age",20).setValue("Name","Andrew"); //segmentation fault

    record.printRecord();

    
    return 0;
}