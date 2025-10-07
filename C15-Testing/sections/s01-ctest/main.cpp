#include <external/minitest/minitest.hpp>
int add(int a,int b){return a+b;}
TEST_CASE(addition){ CHECK(add(2,3)==5); }
int main(){ return mtest::run(); }
