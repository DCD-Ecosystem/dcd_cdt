#pragma once

/**
 * Define specific things for the dcd system
 */

extern "C" {
   void dcd_assert(unsigned int, const char*);
   void __cxa_pure_virtual() { dcd_assert(false, "pure virtual method called"); }
}
