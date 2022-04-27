#include <dcd/dcd.hpp>
using namespace dcd;

CONTRACT hello : public contract {
   public:
      using contract::contract;

      ACTION hi( name nm ) {
         print_f("Name : %\n", nm);
      }
};
