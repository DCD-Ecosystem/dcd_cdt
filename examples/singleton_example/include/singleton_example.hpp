#include <dcd/dcd.hpp>
#include <dcd/singleton.hpp>
using namespace dcd;

class [[dcd::contract]] singleton_example : public contract {
   public:
      using contract::contract;
      singleton_example( name receiver, name code, datastream<const char*> ds ) :
         contract(receiver, code, ds),
         singleton_instance(receiver, receiver.value)
         {}

      [[dcd::action]]
      void set( name user, uint64_t value );
      [[dcd::action]]
      void get( );

      struct [[dcd::table]] testtable {
         name primary_value;
         uint64_t secondary_value;
         uint64_t primary_key() const { return primary_value.value; }
      } testtablerow;

      using singleton_type = dcd::singleton<"testtable"_n, testtable>;
      singleton_type singleton_instance;

      using set_action = action_wrapper<"set"_n, &singleton_example::set>;
      using get_action = action_wrapper<"get"_n, &singleton_example::get>;
};
