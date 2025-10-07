#include <iostream>
struct S{ int x{7}; };
int main(){
  int v{10}; int* p{&v}; int& r{v};
  std::cout<<"&p = "<<&p<<"\n";
  std::cout<<"p  = "<<p<<"\n";
  std::cout<<"*p = "<<*p<<"\n";
  std::cout<<"r  = "<<r<<"\n";
  S s{}; S* ps=&s; std::cout<<"ps->x = "<<ps->x<<"\n"; // pointer member access
  p=nullptr;
}
