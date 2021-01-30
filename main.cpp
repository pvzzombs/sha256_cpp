//#define MEMLEAK
#include "sha256.hpp"
#include <iostream>
#include <sstream>
//#include <vector>
#include <fstream>
#include <exception>

///timer here
#ifdef _WIN32
  #include <windows.h>
  #include <conio.h>
#else
  #include <sys/time.h>
  #include <ctime>
#endif // _WIN32

using namespace std;

uint64_t GetTimeMs64(){
#ifdef _WIN32
  FILETIME ft;
  LARGE_INTEGER li;

  GetSystemTimeAsFileTime(&ft);
  li.LowPart = ft.dwLowDateTime;
  li.HighPart = ft.dwHighDateTime;

  uint64_t ret = li.QuadPart;
  ret -= 116444736000000000LL;
  ret /= 10000;

  return ret;
#else
  struct timeval tv;

  gettimeofday(&tv, NULL);

  uint64_t ret = tv.tv_usec;
  ret /= 1000;

  ret += (tv.tv_sec * 1000);

  return ret;
#endif // _WIN32
}

void show_percent(u32 x){
  u32 y, f = 0;
  cout << '[';
  f = x / 5;
  for(y = 0; y < f; y++){
	cout << '.';
  }
  f = 20 - f;
  for(y = 0; y < f; y++){
	cout << ' ';
  }
  cout << ']'<< ' ' << x << '%' << flush;
  cout << '\r';
}

int main(){
  #ifdef MEMLEAK
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
  std::cout << "Checking for memory leaks..." << std::endl;
  #endif //MEMLEAK
  u64 start_time, end_time;
  string input;
  sha256 sh;/*

  while(true){
    cout << "Enter text:";
    getline(cin, input);
    if(input == ":q" || input == ":e" || input == ".q" || input == ".e" || input == ":exit" || input == ".exit" || input == ".quit" || input == ":quit"){
      break;
    }
    cout << sh.hash(input) << endl;
  }*/

  cout << "Enter test file:";
  getline(cin, input);
  ifstream filex;
  //char inputMain[10];
  u64 sizex;
  //char * inp = new char[1];
  char * inp = nullptr;
  //u32 ipl = 0;
  cout << "Opening file test: " << input << endl;
  filex.open(input.c_str(), ios::in | ios::binary | ios::ate);
  if(filex.is_open()){
    sizex = (u64)filex.tellg();
    inp = new (nothrow) char[sizex];
    if(inp == 0){
      cout << "Allocation Error!" << endl;
      goto DEAD;
    }
    filex.seekg(0, ios::beg);
    filex.read(inp, sizex);
    filex.close();
    cout << "Starting to read test file..." << endl;

    try{
      start_time = GetTimeMs64();
      sh.hash_update(inp, sizex, show_percent);
      sh.hash_finalize();
      end_time = GetTimeMs64();
	  //for(u32 cl=0; cl < 27; cl++){
		//cout << ' ';
	  //}
	  //cout << '\r';
      cout << "The hash is done: " << sh.hash_result() << endl;
      cout << "Took " << (end_time - start_time) << " ms." << endl;
    }catch(exception& e){
      cerr << "An error happened. Error type: " << e.what() << endl;
      goto DEAD;
    }
  }else{
    cout << "The test cannot open the test file: " << input << endl;
  }
  DEAD:
    delete [] inp;
    cout << "Press any key to exit";
	//use _getch instead of getch
#ifdef _WIN32
    _getch();
#else
    getchar();
#endif
  return 0;
}
