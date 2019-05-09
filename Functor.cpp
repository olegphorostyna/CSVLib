#include "Functor.h" 

bool usd::EqualTo::operator()(std::string left, std::string right){
        return left==right;
}

bool usd::LessThat::operator()(std::string left, std::string right){
        return left<right;
}

bool usd::GreaterThan::operator()(std::string left, std::string right){
        return left>right;
}



