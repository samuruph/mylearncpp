#include <optional>
#include <charconv>
#include <string_view>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
std::optional<int> to_int(std::string_view s){ int x{}; auto [p,ec]=std::from_chars(s.data(),s.data()+s.size(),x); if(ec==std::errc{}) return x; return std::nullopt; }
std::vector<std::string> read_lines_throw(const std::string& path){
  std::ifstream ifs(path); if(!ifs) throw std::runtime_error("open failed");
  std::vector<std::string> out; for(std::string line; std::getline(ifs,line);) out.push_back(line); return out;
}
int main(){
  if(auto v=to_int("123")) std::cout<<*v<<"\n"; else std::cout<<"not a number\n";
  try{ auto lines=read_lines_throw("C12-Error-Handling/sections/s01-optional-throw/main.cpp"); std::cout<<"lines="<<lines.size()<<"\n"; }
  catch(const std::exception& e){ std::cerr<<"error: "<<e.what()<<"\n"; }
}
