#include <dcd/dcd.hpp>
#include <dcd/tester.hpp>

using namespace dcd::native;

DCD_TEST_BEGIN(print_test)
   CHECK_PRINT("27", [](){ dcd::print((uint8_t)27); });
   CHECK_PRINT("34", [](){ dcd::print((int)34); });
   CHECK_PRINT([](std::string s){return s[0] == 'a';},  [](){ dcd::print((char)'a'); });
   CHECK_PRINT([](std::string s){return s[0] == 'b';},  [](){ dcd::print((int8_t)'b'); });
   CHECK_PRINT("202", [](){ dcd::print((unsigned int)202); });
   CHECK_PRINT("-202", [](){ dcd::print((int)-202); });
   CHECK_PRINT("707", [](){ dcd::print((unsigned long)707); });
   CHECK_PRINT("-707", [](){ dcd::print((long)-707); });
   CHECK_PRINT("909", [](){ dcd::print((unsigned long long)909); });
   CHECK_PRINT("-909", [](){ dcd::print((long long)-909); });
   CHECK_PRINT("404", [](){ dcd::print((uint32_t)404); });
   CHECK_PRINT("-404", [](){ dcd::print((int32_t)-404); });
   CHECK_PRINT("404000000", [](){ dcd::print((uint64_t)404000000); });
   CHECK_PRINT("-404000000", [](){ dcd::print((int64_t)-404000000); });
   CHECK_PRINT("0x0066000000000000", [](){ dcd::print((uint128_t)102); });
   CHECK_PRINT("0xffffff9affffffffffffffffffffffff", [](){ dcd::print((int128_t)-102); });
DCD_TEST_END

int main(int argc, char** argv) {
   bool verbose = false;
   if( argc >= 2 && std::strcmp( argv[1], "-v" ) == 0 ) {
      verbose = true;
   }
   silence_output(!verbose);

   DCD_TEST(print_test);
   return has_failed();
}
