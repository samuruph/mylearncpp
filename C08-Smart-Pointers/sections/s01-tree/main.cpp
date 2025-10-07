#include <memory>
#include <vector>
#include <iostream>
struct Node{ int id{}; std::vector<std::unique_ptr<Node>> children; };
int main(){
  auto root = std::make_unique<Node>(); root->id=0;
  root->children.push_back(std::make_unique<Node>()); root->children.back()->id=1;
  std::cout<<root->children[0]->id<<"\n";
}
