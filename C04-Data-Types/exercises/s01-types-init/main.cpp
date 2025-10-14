#include <iostream>
#include <string>
int& counter(){ static int n{0}; return ++n; }
int main(){
  const int i{42};
  constexpr double pi{3.141592653589793};
  bool ok{true};
  std::string s{"Ada"};
  std::cout<<i<<" "<<pi<<" "<<ok<<" "<<s<<"\n";
  std::cout<<counter()<<"\n";
}
