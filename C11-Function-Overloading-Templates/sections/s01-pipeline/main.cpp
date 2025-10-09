#include <vector>
#include <ranges>
#include <iostream>
int main(){
  std::vector<int> v{1,2,3,4,5,6};
  auto pipe = v | std::views::filter([](int x){return x%2;})
                | std::views::transform([](int x){return x*x;});
  for(int x: pipe) std::cout<<x<<" ";
  std::cout<<"\n";
}
