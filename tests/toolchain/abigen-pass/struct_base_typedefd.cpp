/*
 * Regression test for https://github.com/DCD/dcd.cdt/issues/601.
 *
 * Verifies that a struct can inherit from a typedef'd class/struct.
 */

#include <dcd/dcd.hpp>

using namespace dcd;

struct foo {
   int value;
};

using bar = foo;

struct baz : bar {
};

class [[dcd::contract]] struct_base_typedefd : public contract {
public:
   using contract::contract;

   [[dcd::action]]
   void hi(baz b) {
      print(b.value);
   }
};
