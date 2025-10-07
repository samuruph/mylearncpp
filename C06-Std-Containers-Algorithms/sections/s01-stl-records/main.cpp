#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>
struct Rec{int id; std::string name; int score;};
int main(){
  std::vector<Rec> v{{1,"Ada",88},{2,"Grace",95},{3,"Linus",90}};
  std::sort(v.begin(), v.end(), [](const Rec&a,const Rec&b){return a.score>b.score;});
  std::unordered_map<int,std::string> idx;
  for(auto& r: v) idx[r.id]=r.name;
  auto it = std::find_if(v.begin(), v.end(), [](const Rec&r){return r.score>=90;});
  if(it!=v.end()) std::cout<<it->name<<"\n";
  std::cout<<"Top: "<<v.front().name<<"  id2: "<<idx[2]<<"\n";
}
