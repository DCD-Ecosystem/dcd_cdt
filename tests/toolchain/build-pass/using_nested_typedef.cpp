/*
 * Regression test for https://github.com/DCD/dcd.cdt/issues/600
 *
 * Verifies that nested typedefs build.
 */

#include <dcd/dcd.hpp>
using namespace dcd;

namespace foo {
//using str = std::string;
typedef std::string str;
}

class [[dcd::contract]] using_nested_typedef : public contract {
public:
   using contract::contract;
   [[dcd::action]]
   void hi(foo::str s) {
      print(s);
   }
};
