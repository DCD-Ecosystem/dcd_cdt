---
content_title: How-To Use Key-Value Map
link_text: "How-To Use Key-Value Map"
---

## Overview

This how-to demonstrates how to define and use a `Key-Value Map` (`kv map`) in a smart contract.

To accomplish this task do the following:

1. Instantiate an object of type `dcd::kv::map`.
2. Specify the name for the instantiated `dcd::kv::map` object.
3. Specify the type for the map's key.
4. Specify the type for the values stored for each key.
5. The key and the values types can be of any standard type or a user defined type.

## Reference

See the following code reference:

* The [`kv::map`](https://developers.dcd.io/manuals/dcd.cdt/latest/classdcd_1_1kv_1_1map) class.

## Before you begin

Make sure you have the following prerequisites in place:

* An DCD development environment, for details consult the [Get Started Guide](https://developers.dcd.io/welcome/latest/getting-started-guide/index)
* A smart contract named `smrtcontract`
* A user defined type, `struct` or `class`, which defines the data stored in the map, named `person`

Refer to the following reference implementation for your starting point:

`smartcontract.hpp file`

```cpp
struct person {
  dcd::name account_name;
  std::string first_name;
  std::string last_name;
};

class [[dcd::contract]] smartcontract : public dcd::contract {
   public:
      using contract::contract;
      smartcontract(dcd::name receiver, dcd::name code, dcd::datastream<const char*> ds)
         : contract(receiver, code, ds) {}
};
```

## Procedure

Complete the following steps to define the `my_map_t` type, based on the `dcd::kv::map`, which stores objects of type `person` with unique keys of type `int` and instantiate a map object of type `my_map_t`:

* Define the `my_map_t` type based on `dcd::kv::map`.
* Specify `"kvmap"_n`, which is an `dcd::name`, as the first parameter, to name the map object.
* Specify `int` as the second parameter to give the type of the unique keys.
* Specify `person` as the third parameter to give the type of the values stored in the map with each key.
* Declare and instantiate, as a private data member, an instance of the type `my_map_t`, and name it `my_map`.

Refer below for a possible implementation of the above described steps:

`smartcontract.hpp file`

```cpp
class [[dcd::contract]] smartcontract : public dcd::contract {

   using my_map_t = dcd::kv::map<"kvmap"_n, int, person>;

   public:
      using contract::contract;
      smartcontract(dcd::name receiver, dcd::name code, dcd::datastream<const char*> ds)
         : contract(receiver, code, ds) {}

   private:
      my_map_t my_map{};
};
```

## Summary

In conclusion, the above instructions show how to define and use a `Key-Value Map` (`kv map`) in a smart contract.

## Next Steps

* You [can add values](30_how-to-upsert-into-kv-map.md) in the map object created.
