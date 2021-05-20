#include <iostream>
#include <cassert>
#include <cstring>
#include "../sha256.hpp"

void show_percent(u32 x){
  u32 y, f = 0;
  std::cout << '[';
  f = x / 5;
  for(y = 0; y < f; y++){
	std::cout << '.';
  }
  f = 20 - f;
  for(y = 0; y < f; y++){
	std::cout << ' ';
  }
  std::cout << ']'<< ' ' << x << '%' << std::flush;
  std::cout << '\r';
}

int main(){
  char test_vector_abc[] = "abc";
  char test_vector_long_abc[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
  char test_vector_empty[] = "";
  char test_vector_896[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
  char test_vector_a_million[1000000];
  memset(test_vector_a_million, 'a', 1000000);

  char test_vector_abc_result[] = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
  char test_vector_long_abc_result[] = "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1";
  char test_vector_empty_result[] = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
  char test_vector_896_result[] = "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1";
  char test_vector_a_million_result[] = "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0";

  /**
    Create a sha256 class
  */

  sha256 Hash;

  assert(Hash.hash(test_vector_abc) == std::string(test_vector_abc_result));
  assert(Hash.hash(test_vector_long_abc) == std::string(test_vector_long_abc_result));
  assert(Hash.hash(test_vector_empty) == std::string(test_vector_empty_result));

  Hash = sha256();

  Hash.hash_update(test_vector_abc, strlen(test_vector_abc));
  Hash.hash_finalize();
  assert(Hash.hash_result() == std::string(test_vector_abc_result));

  Hash.hash_update(test_vector_long_abc, strlen(test_vector_long_abc));
  Hash.hash_finalize();
  assert(Hash.hash_result() == std::string(test_vector_long_abc_result));

  Hash.hash_update(test_vector_empty, strlen(test_vector_empty));
  Hash.hash_finalize();
  assert(Hash.hash_result() == std::string(test_vector_empty_result));

  Hash = sha256();

  Hash.hash_update(std::string(test_vector_abc));
  Hash.hash_finalize();
  assert(Hash.hash_result() == std::string(test_vector_abc_result));

  Hash.hash_update(std::string(test_vector_long_abc));
  Hash.hash_finalize();
  assert(Hash.hash_result() == std::string(test_vector_long_abc_result));

  Hash.hash_update(std::string(test_vector_empty));
  Hash.hash_finalize();
  assert(Hash.hash_result() == std::string(test_vector_empty_result));

  Hash = sha256();

  Hash.hash_update(test_vector_896, strlen(test_vector_896), show_percent);
  Hash.hash_finalize();
  assert(Hash.hash_result() == std::string(test_vector_896_result));
  std::cout << '\n';

  Hash.hash_update(test_vector_a_million, 1000000, show_percent);
  Hash.hash_finalize();
  assert(Hash.hash_result() == std::string(test_vector_a_million_result));
  std::cout << '\n';
  //assert()

  std::cout << "Test Success\n";
  return 0;
}
