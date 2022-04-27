#include <dcd/dcd.hpp>
using namespace dcd;

class [[dcd::contract]] send_inline : public contract {
   public:
      using contract::contract;

      [[dcd::action]]
      void test( name user, name inline_code );

      using test_action = action_wrapper<"test"_n, &send_inline::test>;
};
