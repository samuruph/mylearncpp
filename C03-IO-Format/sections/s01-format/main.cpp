#include <iostream>
#include <string>
#include <format>
int main(){ std::string name; int age{}; std::cout<<"Name? "; std::getline(std::cin,name); std::cout<<"Age? "; std::cin>>age; std::cout<<std::format("Hi {}, age {}.\n",name,age); }
