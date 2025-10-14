#include <cstdio>
#include <stdexcept>
#include <iostream>
class File{
  std::FILE* f{};
public:
  File(const char* path,const char* mode):f(std::fopen(path,mode)){ if(!f) throw std::runtime_error("open failed"); }
  ~File(){ if(f) std::fclose(f); }
  File(const File&)=delete; File& operator=(const File&)=delete;
  File(File&& o) noexcept : f(o.f){ o.f=nullptr; }
  File& operator=(File&& o) noexcept { if(this!=&o){ if(f) std::fclose(f); f=o.f; o.f=nullptr;} return *this; }
  std::FILE* get() const { return f; }
};
int main(){
  const char* in="C07-Classes-RAII/sections/s01-file-raii/main.cpp";
  const char* out="C07-Classes-RAII/sections/s01-file-raii/copy.txt";
  try{ File fi(in,"rb"); File fo(out,"wb"); char buf[4096]; size_t n{}; while((n=std::fread(buf,1,sizeof buf,fi.get()))>0){ std::fwrite(buf,1,n,fo.get()); } std::cout<<"Copied to "<<out<<"\n"; }
  catch(const std::exception& e){ std::cerr<<"Error: "<<e.what()<<"\n"; }
}
