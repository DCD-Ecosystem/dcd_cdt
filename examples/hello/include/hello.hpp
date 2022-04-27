#include <dcd/dcd.hpp>
using namespace dcd;

class [[dcd::contract]] hello : public contract {
   public:
      using contract::contract;

      [[dcd::action]] 
      void hi( name nm );
      [[dcd::action]] 
      void check( name nm );
      [[dcd::action]]
      std::pair<int, std::string> checkwithrv( name nm );

      using hi_action = action_wrapper<"hi"_n, &hello::hi>;
      using check_action = action_wrapper<"check"_n, &hello::check>;
      using checkwithrv_action = action_wrapper<"checkwithrv"_n, &hello::checkwithrv>;
};
