#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
namespace mtest {
  inline std::vector<std::function<void()>>& registry(){ static std::vector<std::function<void()>> r; return r; }
  struct reg { reg(std::function<void()> f){ registry().push_back(std::move(f)); } };
  inline int run(){
    int failed=0;
    for (auto& f: registry()){
      try{ f(); } catch(const std::exception& e){ std::cerr<<"Test threw: "<<e.what()<<"\n"; failed++; }
      catch(...){ std::cerr<<"Test threw unknown\n"; failed++; }
    }
    if(failed){ std::cerr<<failed<<" test(s) failed\n"; return 1; }
    std::cout<<"All tests passed\n"; return 0;
  }
}
#define TEST_CASE(name) static void name(); static mtest::reg reg_##name{name}; static void name()
#define CHECK(cond) do{ if(!(cond)){ std::cerr<<"CHECK failed: " #cond " at " __FILE__ ":"<<__LINE__<<"\n"; throw std::runtime_error(\"check failed\"); } }while(0)
