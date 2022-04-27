#include <dcd/dcd.hpp>
#include <vector>

using namespace dcd;

struct test_res {
   int a;
   float b;
   name  c;
};

class [[dcd::contract]] action_results_test : public contract {
   public:
   using contract::contract;

   [[dcd::action]]
   void action1() {}

   [[dcd::action]]
   uint32_t action2() { return 42; }

   [[dcd::action]]
   std::string action3() { return "foo"; }

   [[dcd::action]]
   std::vector<name> action4() { return {"dan"_n}; }

   [[dcd::action]]
   test_res action5() { return {4, 42.4f, "bucky"_n}; }
};
