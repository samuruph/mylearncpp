#include <string>
#include <vector>
#include <iostream>
std::string make_big(){ return std::string(200000,'x'); }
int main(){ std::vector<std::string> v; v.push_back(make_big()); std::cout<<v.back().size()<<"\n"; }
