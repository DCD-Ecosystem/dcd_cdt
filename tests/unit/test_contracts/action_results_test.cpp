#include <dcd/dcd.hpp>

using namespace dcd;

class [[dcd::contract]] action_results_test : public contract {
   public:
   using contract::contract;

   [[dcd::action]]
   void action1() {}

   [[dcd::action]]
   uint32_t action2() { return 42; }

   [[dcd::action]]
   std::string action3() { return "foo"; }
};
