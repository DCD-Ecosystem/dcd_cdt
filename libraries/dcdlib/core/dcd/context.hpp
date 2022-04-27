#pragma once

#include "name.hpp"

namespace dcd {
   namespace internal_use_do_not_use {
      extern "C" uint64_t dcd_contract_name;
   }

   inline name current_context_contract() { return name{internal_use_do_not_use::dcd_contract_name}; }
}
