#include <dcd/dcd.hpp>

using namespace dcd;

namespace test {
   using _Bool = int32_t;
}

using My_Bool = float;

class [[dcd::contract]] bool_template : public dcd::contract {
   public:
      using contract::contract;

      [[dcd::action]] void test1(std::optional<bool> a) {}
      [[dcd::action]] void test2(std::variant<uint64_t, bool> a) {}
      [[dcd::action]] void test3(bool a) {}

      [[dcd::action]] void test4(test::_Bool a) {}
      [[dcd::action]] void test5(My_Bool a) {}
};
