#include <dcd/dcd.hpp>
#include <dcd/privileged.hpp>

using namespace dcd;
extern "C" __attribute__((weak)) __attribute__((dcd_wasm_import)) void set_resource_limit(int64_t, int64_t, int64_t);

class [[dcd::contract]] warn_action_read_only : public contract {
  public:
      using contract::contract;
      
      [[dcd::action, dcd::read_only]]
      void test1( name user ) {
	      set_resource_limit(user.value, 0, 0);
      }
};
