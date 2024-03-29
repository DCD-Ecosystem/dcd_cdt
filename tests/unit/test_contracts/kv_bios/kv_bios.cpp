#include <dcd/contract.hpp>
#include <dcd/name.hpp>
#include <dcd/privileged.hpp>

extern "C" __attribute__((dcd_wasm_import)) void set_resource_limit(int64_t, int64_t, int64_t);
extern "C" __attribute__((dcd_wasm_import)) uint32_t get_kv_parameters_packed(void* params, uint32_t size, uint32_t max_version);
extern "C" __attribute__((dcd_wasm_import)) void set_kv_parameters_packed(const char* params, uint32_t size);

using namespace dcd;

// Manages resources used by the kv-store
class [[dcd::contract]] kv_bios : dcd::contract {
 public:
   using contract::contract;
   [[dcd::action]] void setdisklimit(name account, int64_t limit) {
      set_resource_limit(account.value, "disk"_n.value, limit);
   }
   [[dcd::action]] void setramlimit(name account, int64_t limit) {
      set_resource_limit(account.value, "ram"_n.value, limit);
   }
   [[dcd::action]] void ramkvlimits(uint32_t k, uint32_t v, uint32_t i) {
      kvlimits_impl("dcd.kvram"_n, k, v, i);
   }
   [[dcd::action]] void diskkvlimits(uint32_t k, uint32_t v, uint32_t i) {
      kvlimits_impl("dcd.kvdisk"_n, k, v, i);
   }
   void kvlimits_impl(name db, uint32_t k, uint32_t v, uint32_t i) {
      uint32_t limits[4];
      limits[0] = 0;
      limits[1] = k;
      limits[2] = v;
      limits[3] = i;
      char limits_buf[sizeof(limits)];
      memcpy(limits_buf, limits, sizeof(limits));
      set_kv_parameters_packed(limits_buf, sizeof(limits));
      int sz = get_kv_parameters_packed(nullptr, 0, 0);
      std::fill_n(limits, sizeof(limits)/sizeof(limits[0]), 0xFFFFFFFFu);
      check(sz == 16, "wrong kv parameters size");
      sz = get_kv_parameters_packed(limits, sizeof(limits), 0);
      check(sz == 16, "wrong kv parameters result");
      check(limits[0] == 0, "wrong version");
      check(limits[1] == k, "wrong key");
      check(limits[2] == v, "wrong value");
      check(limits[3] == i, "wrong iter limit");
   }
};
