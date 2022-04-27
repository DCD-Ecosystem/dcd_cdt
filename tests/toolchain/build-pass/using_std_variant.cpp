/*
 * Regression test for https://github.com/DCD/dcd.cdt/issues/558
 *
 * Verifies that a class/function can be used from the std namespace
 */

#include <dcd/dcd.hpp>
#include <dcd/print.hpp>
#include <variant>

using std::variant;
using namespace dcd;

class[[dcd::contract("hello")]] hello : public contract
{
public:
   using contract::contract;

   [[dcd::action]] void hi(name user) {
      require_auth(user);
      print("Hello, ", user);
   }

   struct [[dcd::table]] greeting {
      uint64_t id;
      variant<int32_t, int64_t> t;
      uint64_t primary_key() const { return id; }
   };
   typedef multi_index<"greeting"_n, greeting> greeting_index;
};
