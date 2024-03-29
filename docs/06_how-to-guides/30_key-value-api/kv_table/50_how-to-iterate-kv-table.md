---
content_title: How-To Iterate Through Key-Value Table
link_text: "How-To Iterate Through Key-Value Table"
---

## Overview

This how-to provides instructions to iterate through a `Key-Value Table` (`kv table`) and read values from it.

[[caution | Alpha version]]
| `Key-Value Table` is designated as `alpha` and should not be used in production code.

Use the `iterator` defined by the `dcd::kv::table::index` class to accomplish this task.

## Before you begin

Make sure you have the following prerequisites in place:

* An DCD development environment, for details consult the [Get Started Guide](https://developers.dcd.io/welcome/latest/getting-started-guide/index)
* A smart contract named `smrtcontract`
* A user defined type, `struct` or `class`, which defines the data stored in the map, named `person`
* A `kv table` data type, `struct` or `class`, which inherits `dcd::kv::table`, and stores objects of type `person`, named `address_table`
* Each `person` object has the following data members:
  * `account_name`,
  * `first_name`,
  * `last_name`,
  * `personal_id`.
* A unique index, named `account_name_uidx`, defined on the `account_name` data member

Refer to the following reference implementation for your starting point:

`smartcontract.hpp file`

```cpp
struct person {
  dcd::name account_name;
  std::string first_name;
  std::string last_name;
  std::string personal_id;
};

class [[dcd::contract]] smrtcontract : public contract {
    struct [[dcd::table]] address_table : dcd::kv::table<person, "kvaddrbook"_n> {

     index<name> account_name_uidx {
        name{"accname"_n},
        &person::account_name };

     address_table(name contract_name) {
        init(contract_name, account_name_uidx)
     }
  };
  public:
     using contract::contract;
};
```

## Procedure

Complete the following steps to implement an action which iterates through the first N `person` objects in `address_table` and prints their first and last names:

1. Create a new action `iterate`, which takes as an input parameter the number of iterations to be executed.
2. In the `iterate` action access the instance of `address_table` by declaring a local variable of `address_table` type.
3. Capture the `begin` and the `end` of the `account_name_uidx` index defined.
4. Use the iterator `value` to access the current value of the iterator.
5. Increment the iterator until the first N `person` objects stored in `address_table` are visited.

Refer to the following reference implementation to implement an action which iterates through the first N `person` objects in `address_table` and prints their first and last names:

`smartcontract.hpp`

```cpp
class [[dcd::contract]] smrtcontract : public contract {
    struct [[dcd::table]] address_table : dcd::kv::table<person, "kvaddrbook"_n> {

     index<name> account_name_uidx {
        name{"accname"_n},
        &person::account_name };

     address_table(name contract_name) {
        init(contract_name, account_name_uidx)
     }
  };
  public:
     using contract::contract;

     // iterates over the first n persons in the table
     [[dcd::action]]
     std::vector<person> iterate(int iterations_count
);

     using iterate_action = action_wrapper<"iterate"_n, &smrtcontract::iterate>;
};
```

`smartcontract.cpp file`

```cpp
// Iterates over the first iterations_count persons in the table
[[dcd::action]]
std::vector<person> smrtcontract::iterate(int iterations_count) {
  address_table addresses{"kvaddrbook"_n};


  auto begin_itr = addresses.account_name_uidx.begin();
  auto end_itr = addresses.account_name_uidx.end();

  int current_iteration = 0;
  while (begin_itr != end_itr && current_iteration < iterations_count)
  {
     dcd::print_f(
        "Person found: {%, %}\n",
        begin_itr.value().first_name,
        begin_itr.value().last_name);

     ++ begin_itr;
     ++ current_iteration;
  }
}
```

## Summary

In conclusion, the above instructions show how to iterate through a `Key-Value Table` (`kv table`) and read values from it.
