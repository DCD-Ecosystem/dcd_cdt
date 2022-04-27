#include <dcd/dcd.hpp>

class [[dcd::contract]] separate_cpp_hpp : dcd::contract {
public:
   using contract::contract;

   [[dcd::action]] void act();
};
