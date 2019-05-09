#include<string>
namespace usd{

class LogicPredicate{
    public:
    LogicPredicate(){};
    virtual bool operator()(std::string left, std::string right) = 0;
};

class EqualTo: public LogicPredicate{
    public:
    virtual bool operator()(std::string, std::string);
};

class LessThat: public LogicPredicate{
    public:
    virtual bool operator()(std::string, std::string);
};
class GreaterThan: public LogicPredicate{
    public:
    virtual bool operator()(std::string, std::string);
};

}