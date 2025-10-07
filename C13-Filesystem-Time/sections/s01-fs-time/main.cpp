#include <filesystem>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <numeric>
namespace fs = std::filesystem;
int main(){
  for(auto& p: fs::directory_iterator(".")) std::cout<<p.path().string()<<"\n";
  auto t0 = std::chrono::steady_clock::now();
  std::vector<int> v(100000); std::iota(v.begin(), v.end(), 0); std::reverse(v.begin(), v.end()); std::sort(v.begin(), v.end());
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-t0).count();
  std::cout<<"elapsed(ms)="<<ms<<"\n";
}
