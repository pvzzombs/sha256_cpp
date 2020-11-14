#include <iostream>
#include <cassert>
#include <cstring>
#include "../sha256.hpp"

int main(){
  char test_vector_abc[] = "abc";
  char test_vector_long_abc[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
  char test_vector_empty[] = "";

  char test_vector_abc_result[] = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
  char test_vector_long_abc_result[] = "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1";
  char test_vector_empty_result[] = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";


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

  //assert()

  std::cout << "Test Success\n";
  return 0;
}
