#include <string>
#include <vector>
#include <stdarg.h>
#include <limits>
namespace usd{
    class Query{
        private:
            class QueryProperties{
                private:
                    QueryProperties(): distinct(false),
                                        greater_then_int(std::numeric_limits<int>::min()),
                                        smaller_then_int(std::numeric_limits<int>::min()){}
                    std::vector<std::string>  cols_to_select;
                    bool distinct;
                    int greater_then_int;
                    int smaller_then_int;
                    std::string greater_then_str;
                    std::string smaller_then_str;

                    friend class Query;
                    friend class QueryBuilder;                    
            };

        public:        
           class QueryBuilder{
               public:                                
                    QueryBuilder& setCol(std::string col);
                    QueryBuilder& setDistinct(bool isDistinct);
                    QueryBuilder& setGreaterThan(int base);
                    QueryBuilder& setGreaterThan(std::string base);
                    QueryBuilder& setSmallerThan(int base);
                    QueryBuilder& setSmallerThan(std::string base);
                    Query build();

                private:
                    QueryProperties q_prop;
           };
        private:
            Query(const QueryProperties& prop): properties(prop){}
            QueryProperties properties;           
    };
}