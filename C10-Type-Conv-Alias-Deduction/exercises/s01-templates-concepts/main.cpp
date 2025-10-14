#include <concepts>
#include <iostream>
template <typename T> T add(T a,T b){return a+b;}
template <std::integral I> I inc(I x){return x+1;}
int main(){ std::cout<<add(2,3)<<"\n"<<inc(41)<<"\n"; }
