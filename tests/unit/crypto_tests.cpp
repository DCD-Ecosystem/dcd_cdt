/**
 *  @file
 *  @copyright defined in dcd.cdt/LICENSE.txt
 */

#include <dcd/tester.hpp>
#include <dcd/crypto.hpp>

using dcd::public_key;
using dcd::signature;

// Definitions in `dcd.cdt/libraries/dcd/crypto.hpp`
DCD_TEST_BEGIN(public_key_type_test)
   // -----------------------------------------------------
   // bool operator==(const public_key&, const public_key&)
   CHECK_EQUAL( (public_key(std::in_place_index<0>, std::array<char, 33>{})  == public_key(std::in_place_index<0>, std::array<char, 33>{})), true  )
   CHECK_EQUAL( (public_key(std::in_place_index<0>, std::array<char, 33>{1}) == public_key(std::in_place_index<0>, std::array<char, 33>{})), false )

   // -----------------------------------------------------
   // bool operator!=(const public_key&, const public_key&)
   CHECK_EQUAL( (public_key(std::in_place_index<0>, std::array<char, 33>{})  != public_key(std::in_place_index<0>, std::array<char, 33>{})), false )
   CHECK_EQUAL( (public_key(std::in_place_index<0>, std::array<char, 33>{1}) != public_key(std::in_place_index<0>, std::array<char, 33>{})), true  )
DCD_TEST_END

// Definitions in `dcd.cdt/libraries/dcd/crypto.hpp`
DCD_TEST_BEGIN(signature_type_test)
   // ---------------------------------------------------
   // bool operator==(const signature&, const signature&)
   CHECK_EQUAL( (signature(std::in_place_index<0>, std::array<char, 65>{})  == signature(std::in_place_index<0>, std::array<char, 65>{})), true  )
   CHECK_EQUAL( (signature(std::in_place_index<0>, std::array<char, 65>{1}) == signature(std::in_place_index<0>, std::array<char, 65>{})), false )

   // ---------------------------------------------------
   // bool operator!=(const signature&, const signature&)
   CHECK_EQUAL( (signature(std::in_place_index<0>, std::array<char, 65>{1}) != signature(std::in_place_index<0>, std::array<char, 65>{})), true  )
   CHECK_EQUAL( (signature(std::in_place_index<0>, std::array<char, 65>{})  != signature(std::in_place_index<0>, std::array<char, 65>{})), false )
DCD_TEST_END

int main(int argc, char* argv[]) {
   bool verbose = false;
   if( argc >= 2 && std::strcmp( argv[1], "-v" ) == 0 ) {
      verbose = true;
   }
   silence_output(!verbose);

   DCD_TEST(public_key_type_test)
   DCD_TEST(signature_type_test)
   return has_failed();
}
