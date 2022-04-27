/**
 *  @file
 *  @copyright defined in dcd/LICENSE
 */
#pragma once
#include "action.hpp"
#include "../../core/dcd/print.hpp"
#include "map.hpp"
#include "multi_index.hpp"
#include "dispatcher.hpp"
#include "contract.hpp"

#ifndef DCD_NATIVE
static_assert( sizeof(long) == sizeof(int), "unexpected size difference" );
#endif

/**
 * @defgroup core Core API
 * @brief C++ Core API for chain-agnostic smart-contract functionality
 */

 /**
  * @defgroup contracts Contracts API
  * @brief C++ Contracts API for chain-dependent smart-contract functionality
  */

/**
 * @defgroup types Types
 * @brief C++ Types API for data layout of data-structures available for the DCD platform
 */
