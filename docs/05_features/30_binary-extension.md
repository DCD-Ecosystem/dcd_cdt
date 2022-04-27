---
content_title: The dcd::binary_extension Type
---

Let's fully explain what the `dcd::binary_extension` type is, what it does, and why we need it for contract upgrades in certain situations.

You can find the implementation of `dcd::binary_extension` in the `dcd.cdt` repository in file: `dcd.cdt/libraries/dcdlib/core/dcd/binary_extension.hpp`.

Our primary concern when using this type is when we are adding a new field to a smart contract's data structure that is currently utilized in an `dcd::multi_index` type (AKA a _table_), or when adding a new parameter to an action declaration.

By wrapping the new field in an `dcd::binary_extension`, you are enabling your contract to be backwards compatible for future use. Note that this new field/parameter **MUST** be appended at the end of a data structure (this is due to implementation details in `dcd::multi_index`, which relies on the `boost::multi_index` type), or at the end of the parameter list in an action declaration.

If you don't wrap the new field in an `dcd::binary_extension`, the `dcd::multi_index` table will be reformatted in such a way that disallows reads to the former datum; or in an action's case, the function will be uncallable.

<hr>

But let's see how the `dcd::binary_extension` type works with a good example.

Take a moment to study this smart contract and its corresponding `.abi`.

This contract not only serves as a good example to the `dcd::binary_extension` type, but can also be used as a gateway for developing smart contracts on the dcd protocol.

**binary_extension_contract.hpp**

```c++
#include <dcd/contract.hpp>         // dcd::contract
#include <dcd/binary_extension.hpp> // dcd::binary_extension
#include <dcd/datastream.hpp>       // dcd::datastream
#include <dcd/name.hpp>             // dcd::name
#include <dcd/multi_index.hpp>      // dcd::indexed_by, dcd::multi_index
#include <dcd/print.hpp>            // dcd::print_f

class [[dcd::contract]] binary_extension_contract : public dcd::contract {
public:
   using contract::contract;
   binary_extension_contract(dcd::name receiver, dcd::name code, dcd::datastream<const char*> ds)
      : contract{receiver, code, ds}, _table{receiver, receiver.value}
   { }

   [[dcd::action]] void regpkey (dcd::name primary_key);                ///< Register primary key.
   [[dcd::action]] void printbyp(dcd::name primary_key);                ///< Print by primary key.
   [[dcd::action]] void printbys(dcd::name secondary_key);              ///< Print by secondary key.
   [[dcd::action]] void modifyp (dcd::name primary_key, dcd::name n); ///< Modify primary key by primary key.
   [[dcd::action]] void modifys (dcd::name primary_key, dcd::name n); ///< Modify secondary key by primary key.

   struct [[dcd::table]] structure {
      dcd::name _primary_key;
      dcd::name _secondary_key;
         
      uint64_t primary_key()   const { return _primary_key.value;   }
      uint64_t secondary_key() const { return _secondary_key.value; }
   };

   using index1 = dcd::indexed_by<"index1"_n, dcd::const_mem_fun<structure, uint64_t, &structure::primary_key>>;
   using index2 = dcd::indexed_by<"index2"_n, dcd::const_mem_fun<structure, uint64_t, &structure::secondary_key>>;
   using table  = dcd::multi_index<"table"_n, structure, index1, index2>;

private:
   table _table;
};

```

**binary_extension_contract.cpp**

```c++
#include "binary_extension_contract.hpp"

using dcd::name;

[[dcd::action]] void binary_extension_contract::regpkey(name primary_key) {
   dcd::print_f("`regpkey` executing.\n");
   
   auto index{_table.get_index<"index1"_n>()}; ///< `index` represents `_table` organized by `index1`.
   auto iter {index.find(primary_key.value) }; ///< Note: the type returned by `index.find` is different than the type returned by `_table.find`.
   
   if (iter == _table.get_index<"index1"_n>().end()) {
      dcd::print_f("`_primary_key`: % not found; registering.\n", primary_key.to_string());
      _table.emplace(_self, [&](auto& row) {
         row._primary_key   = primary_key;
         row._secondary_key = "nothin"_n;
      });
   }
   else {
      dcd::print_f("`_primary_key`: % found; not registering.\n", primary_key.to_string());
   }

   dcd::print_f("`regpkey` finished executing.\n");
}

[[dcd::action]] void binary_extension_contract::printbyp(dcd::name primary_key) {
   dcd::print_f("`printbyp` executing.\n");
   
   auto index{_table.get_index<"index1"_n>()};
   auto iter {index.find(primary_key.value) };
   
   if (iter != _table.get_index<"index1"_n>().end()) {
      dcd::print_f("`_primary_key`: % found; printing.\n", primary_key.to_string());
      dcd::print_f("{%, %}\n", iter->_primary_key, iter->_secondary_key);
   }
   else {
      dcd::print_f("`_primary_key`: % not found; not printing.\n", primary_key.to_string());
   }

   dcd::print_f("`printbyp` finished executing.\n");
}

[[dcd::action]] void binary_extension_contract::printbys(dcd::name secondary_key) {
   dcd::print_f("`printbys` executing.\n");
   
   auto index{_table.get_index<"index2"_n>()};
   auto iter {index.find(secondary_key.value)};
   
   if (iter != _table.get_index<"index2"_n>().end()) {
      dcd::print_f("`_secondary_key`: % found; printing.\n", secondary_key.to_string());
      printbyp(iter->_primary_key);
   }
   else {
      dcd::print_f("`_secondary_key`: % not found; not printing.\n", secondary_key.to_string());
   }

   dcd::print_f("`printbys` finished executing.\n");
}

[[dcd::action]] void binary_extension_contract::modifyp(dcd::name primary_key, name n) {
   dcd::print_f("`modifyp` executing.\n");
   
   auto index{_table.get_index<"index1"_n>()};
   auto iter {index.find(primary_key.value)};
   
   if (iter != _table.get_index<"index1"_n>().end()) {
      dcd::print_f("`_primary_key`: % found; modifying `_primary_key`.\n", primary_key.to_string());
      index.modify(iter, _self, [&](auto& row) {
         row._primary_key = n;
      });
   }
   else {
      dcd::print_f("`_primary_key`: % not found; not modifying `_primary_key`.\n", primary_key.to_string());
   }

   dcd::print_f("`modifyp` finished executing.\n");
}

[[dcd::action]] void binary_extension_contract::modifys(dcd::name primary_key, name n) {
   dcd::print_f("`modifys` executing.\n");
   
   auto index{_table.get_index<"index1"_n>()};
   auto iter {index.find(primary_key.value)};
   
   if (iter != _table.get_index<"index1"_n>().end()) {
      dcd::print_f("`_primary_key`: % found; modifying `_secondary_key`.\n", primary_key.to_string());
      index.modify(iter, _self, [&](auto& row) {
         row._secondary_key = n;
      });
   }
   else {
      dcd::print_f("`_primary_key`: % not found; not modifying `_secondary_key`.\n", primary_key.to_string());
   }

   dcd::print_f("`modifys` finished executing.\n");
}
```

**binary_extension_contract.abi**

```javascript
{
    "____comment": "This file was generated with dcd-abigen. DO NOT EDIT ",
    "version": "eosio::abi/1.1",
    "types": [],
    "structs": [
        {
            "name": "modifyp",
            "base": "",
            "fields": [
                {
                    "name": "primary_key",
                    "type": "name"
                },
                {
                    "name": "n",
                    "type": "name"
                }
            ]
        },
        {
            "name": "modifys",
            "base": "",
            "fields": [
                {
                    "name": "primary_key",
                    "type": "name"
                },
                {
                    "name": "n",
                    "type": "name"
                }
            ]
        },
        {
            "name": "printbyp",
            "base": "",
            "fields": [
                {
                    "name": "primary_key",
                    "type": "name"
                }
            ]
        },
        {
            "name": "printbys",
            "base": "",
            "fields": [
                {
                    "name": "secondary_key",
                    "type": "name"
                }
            ]
        },
        {
            "name": "regpkey",
            "base": "",
            "fields": [
                {
                    "name": "primary_key",
                    "type": "name"
                }
            ]
        },
        {
            "name": "structure",
            "base": "",
            "fields": [
                {
                    "name": "_primary_key",
                    "type": "name"
                },
                {
                    "name": "_secondary_key",
                    "type": "name"
                }
            ]
        }
    ],
    "actions": [
        {
            "name": "modifyp",
            "type": "modifyp",
            "ricardian_contract": ""
        },
        {
            "name": "modifys",
            "type": "modifys",
            "ricardian_contract": ""
        },
        {
            "name": "printbyp",
            "type": "printbyp",
            "ricardian_contract": ""
        },
        {
            "name": "printbys",
            "type": "printbys",
            "ricardian_contract": ""
        },
        {
            "name": "regpkey",
            "type": "regpkey",
            "ricardian_contract": ""
        }
    ],
    "tables": [
        {
            "name": "table",
            "type": "structure",
            "index_type": "i64",
            "key_names": [],
            "key_types": []
        }
    ],
    "ricardian_clauses": [],
    "variants": []
}
```

<hr>

Take note of the action `regpkey`, and the struct `structure` in `con.hpp` and `con.cpp`; the parts of the contract we will be upgrading.

**binary_extension_contract.hpp**

```c++
[[dcd::action]] void regpkey (dcd::name primary_key);
```

```c++
struct [[dcd::table]] structure {
    dcd::name _primary_key;
    dcd::name _secondary_key;

    uint64_t primary_key()   const { return _primary_key.value;   }
    uint64_t secondary_key() const { return _secondary_key.value; }
};
```

**binary_extension_contract.cpp**

```c++
[[dcd::action]] void binary_extension_contract::regpkey(name primary_key) {
   dcd::print_f("`regpkey` executing.\n");
   
   auto index{_table.get_index<"index1"_n>()}; ///< `index` represents `_table` organized by `index1`.
   auto iter {index.find(primary_key.value) }; ///< Note: the type returned by `index.find` is different than the type returned by `_table.find`.
   
   if (iter == _table.get_index<"index1"_n>().end()) {
      dcd::print_f("`_primary_key`: % not found; registering.\n", primary_key.to_string());
      _table.emplace(_self, [&](auto& row) {
         row._primary_key   = primary_key;
         row._secondary_key = "nothin"_n;
      });
   }
   else {
      dcd::print_f("`_primary_key`: % found; not registering.\n", primary_key.to_string());
   }

   dcd::print_f("`regpkey` finished executing.\n");
}
```

Find below their corresponding sections in the `.abi` files:

**binary_extension_contract.abi**

```javascript
{
    "name": "regpkey",
    "base": "",
    "fields": [
        {
            "name": "primary_key",
            "type": "name"
        }
    ]
}
```

```javascript
{
    "name": "structure",
    "base": "",
    "fields": [
        {
            "name": "_primary_key",
            "type": "name"
        },
        {
            "name": "_secondary_key",
            "type": "name"
        }
    ]
}
```

<hr>

Now, let's start up a blockchain instance, compile this smart contract, and test it out.

```
~/binary_extension_contract $ dcd-cpp binary_extension_contract.cpp -o binary_extension_contract.wasm
```

```
~/binary_extension_contract $ cldcd set contract dcd ./
```

```
Reading WASM from /Users/john.debord/binary_extension_contract/binary_extension_contract.wasm...
Publishing contract...
executed transaction: 6c5c7d869a5be67611869b5f300bc452bc57d258d11755f12ced99c7d7fe154c  4160 bytes  729 us
#         dcd <= dcd::setcode               "0000000000ea30550000d7600061736d01000000018f011760000060017f0060027f7f0060037f7f7f017f6000017e60067...
#         dcd <= dcd::setabi                "0000000000ea3055d1020e656f73696f3a3a6162692f312e310006076d6f646966797000020b7072696d6172795f6b65790...
warning: transaction executed locally, but may not be confirmed by the network yet
```

Next, let's push some data to our contract.

```
~/binary_extension_contract $ cldcd push action dcd regpkey '{"primary_key":"dcd.name"}' -p dcd
```

```
executed transaction: 3c708f10dcbf4412801d901eb82687e82287c2249a29a2f4e746d0116d6795f0  104 bytes  248 us
#         dcd <= dcd::regpkey               {"primary_key":"dcd.name"}
[(dcd,regpkey)->dcd]: CONSOLE OUTPUT BEGIN =====================
`regpkey` executing.
`_primary_key`: dcd.name not found; registering.
`regpkey` finished executing.
[(dcd,regpkey)->dcd]: CONSOLE OUTPUT END   =====================
warning: transaction executed locally, but may not be confirmed by the network yet
```

Finally, let's read back the data we have just written.

```
~/binary_extension_contract $ cldcd push action dcd printbyp '{"primary_key":"dcd.name"}' -p dcd
```

```
executed transaction: e9b77d3cfba322a7a3a93970c0c883cb8b67e2072a26d714d46eef9d79b2f55e  104 bytes  227 us
#         dcd <= dcd::printbyp              {"primary_key":"dcd.name"}
[(dcd,printbyp)->dcd]: CONSOLE OUTPUT BEGIN =====================
`printbyp` executing.
`_primary_key`: dcd.name found; printing.
{dcd.name, nothin}
`printbyp` finished executing.
[(dcd,printbyp)->dcd]: CONSOLE OUTPUT END   =====================
warning: transaction executed locally, but may not be confirmed by the network yet
```

<hr>

Now, let's upgrade the smart contract by adding a new field to the table and a new parameter to an action while **NOT** wrapping the new field/parameter in an `dcd::binary_extension` type and see what happens:

**binary_extension_contract.hpp**

```diff
+[[dcd::action]] void regpkey (dcd::name primary_key, dcd::name secondary_key);
-[[dcd::action]] void regpkey (dcd::name primary_key);
```

```diff
struct [[dcd::table]] structure {
    dcd::name _primary_key;
    dcd::name _secondary_key;
+   dcd::name _non_binary_extension_key;

    uint64_t primary_key()   const { return _primary_key.value;   }
    uint64_t secondary_key() const { return _secondary_key.value; }
};
```

**binary_extension_contract.cpp**

```diff
+[[dcd::action]] void binary_extension_contract::regpkey(name primary_key, name secondary_key) {
-[[dcd::action]] void binary_extension_contract::regpkey(name primary_key) {
   dcd::print_f("`regpkey` executing.\n");
   
   auto index{_table.get_index<"index1"_n>()}; ///< `index` represents `_table` organized by `index1`.
   auto iter {index.find(primary_key.value) }; ///< Note: the type returned by `index.find` is different than the type returned by `_table.find`.
   
   if (iter == _table.get_index<"index1"_n>().end()) {
      dcd::print_f("`_primary_key`: % not found; registering.\n", primary_key.to_string());
      _table.emplace(_self, [&](auto& row) {
         row._primary_key   = primary_key;
+        if (secondary_key) {
+           row._secondary_key = secondary_key;
+         }
+         else {
            row._secondary_key = "nothin"_n;
+         }
      });
   }
   else {
      dcd::print_f("`_primary_key`: % found; not registering.\n", primary_key.to_string());
   }

   dcd::print_f("`regpkey` finished executing.\n");
}
```

**binary_extension_contract.abi**
```diff
{
    "name": "regpkey",
    "base": "",
    "fields": [
        {
            "name": "primary_key",
            "type": "name"
+       },
+       {
+           "name": "secondary_key",
+           "type": "name"
        }
    ]
}
```

```diff
{
    "name": "structure",
    "base": "",
    "fields": [
        {
            "name": "_primary_key",
            "type": "name"
        },
        {
            "name": "_secondary_key",
            "type": "name"
+       },
+	{
+           "name": "_non_binary_extension_key",
+           "type": "name"
        }
    ]
}
```

Next, let's upgrade the contract and try to read from our table and write to our table the original way:

```
~/binary_extension_contract $ dcd-cpp binary_extension_contract.cpp -o binary_extension_contract.wasm
```

```
~/binary_extension_contract $ cldcd set contract dcd ./
```

```
Reading WASM from /Users/john.debord/binary_extension_contract/binary_extension_contract.wasm...
Publishing contract...
executed transaction: b8ea485842fa5645e61d35edd97e78858e062409efcd0a4099d69385d9bc6b3e  4408 bytes  664 us
#         dcd <= dcd::setcode               "0000000000ea30550000a2660061736d01000000018f011760000060017f0060027f7f0060037f7f7f017f6000017e60067...
#         dcd <= dcd::setabi                "0000000000ea305583030e656f73696f3a3a6162692f312e310006076d6f646966797000020b7072696d6172795f6b65790...
warning: transaction executed locally, but may not be confirmed by the network yet
```

```
~/binary_extension_contract $ cldcd push action dcd printbyp '{"primary_key":"dcd.name"}' -p dcd
```

```
Error 3050003: dcd_assert_message assertion failure
Error Details:
assertion failure with message: read
```

Whoops! We aren't able to read the data we've previously written to our table!

```
~/binary_extension_contract $ cldcd push action dcd regpkey '{"primary_key":"dcd.name2"}' -p dcd
```

```
Error 3015014: Pack data exception
Error Details:
Missing field 'secondary_key' in input object while processing struct 'regpkey'
```

Whoops! We aren't able to write to our table the original way with the upgraded action either!

<hr>

Ok, let's back up and wrap the new field and the new action parameter in an `dcd::binary_extension` type:

**binary_extension_contract.hpp**

```diff
+[[dcd::action]] void regpkey (dcd::name primary_key. dcd::binary_extension<dcd::name> secondary_key);
-[[dcd::action]] void regpkey (dcd::name primary_key, dcd::name secondary_key);
```

```diff
struct [[dcd::table]] structure {
    dcd::name                          _primary_key;
    dcd::name                          _secondary_key;
+   dcd::binary_extension<dcd::name> _binary_extension_key;
-   dcd::name                          _non_binary_extension_key;

    uint64_t primary_key()   const { return _primary_key.value;   }
    uint64_t secondary_key() const { return _secondary_key.value; }
};
```

**binary_extension_contract.cpp**

```diff
+[[dcd::action]] void binary_extension_contract::regpkey(name primary_key, binary_extension<name> secondary_key) {
-[[dcd::action]] void binary_extension_contract::regpkey(name primary_key, name secondary_key) {
   dcd::print_f("`regpkey` executing.\n");
   
   auto index{_table.get_index<"index1"_n>()}; ///< `index` represents `_table` organized by `index1`.
   auto iter {index.find(primary_key.value) }; ///< Note: the type returned by `index.find` is different than the type returned by `_table.find`.
   
   if (iter == _table.get_index<"index1"_n>().end()) {
      dcd::print_f("`_primary_key`: % not found; registering.\n", primary_key.to_string());
      _table.emplace(_self, [&](auto& row) {
         row._primary_key   = primary_key;
         if (secondary_key) {
+           row._secondary_key = secondary_key.value();
-           row._secondary_key = secondary_key;
          }
          else {
            row._secondary_key = "nothin"_n;
          }
      });
   }
   else {
      dcd::print_f("`_primary_key`: % found; not registering.\n", primary_key.to_string());
   }

   dcd::print_f("`regpkey` finished executing.\n");
}
```

**binary_extension_contract.abi**
```diff
{
    "name": "regpkey",
    "base": "",
    "fields": [
        {
            "name": "primary_key",
            "type": "name"
        },
        {
            "name": "secondary_key",
+           "type": "name$"
-           "type": "name"
        }
    ]
}
```

```diff
{
    "name": "structure",
    "base": "",
    "fields": [
        {
            "name": "_primary_key",
            "type": "name"
        },
        {
            "name": "_secondary_key",
            "type": "name"
        },
	{
+           "name": "_binary_extension_key",
+           "type": "name$"
-           "name": "_non_binary_extension_key",
-           "type": "name"
        }
    ]
}
```

Note the `$` after the types now; this indicates that this type is an `dcd::binary_extension` type field.
```diff
{
    "name": "secondary_key",
+   "type": "name$"
-   "type": "name"
}
```

```diff
{
    "name": "_binary_extension_key",
+   "type": "name$"
-   "type": "name"
}
```

Now, let's upgrade the contract again and try to read/write from/to our table:

```
~/binary_extension_contract $ cldcd set contract dcd ./
```

```
Reading WASM from /Users/john.debord/binary_extension_contract/binary_extension_contract.wasm...
Publishing contract...
executed transaction: 497584d4e43ec114dbef83c134570492893f49eacb555d0cd47d08ea4a3a72f7  4696 bytes  648 us
#         dcd <= dcd::setcode               "0000000000ea30550000cb6a0061736d01000000018f011760000060017f0060027f7f0060037f7f7f017f6000017e60017...
#         dcd <= dcd::setabi                "0000000000ea305581030e656f73696f3a3a6162692f312e310006076d6f646966797000020b7072696d6172795f6b65790...
warning: transaction executed locally, but may not be confirmed by the network yet
```

```
~/binary_extension_contract $ cldcd push action dcd printbyp '{"primary_key":"dcd.name"}' -p dcd
```

```
executed transaction: 6108f3206e1824fe3a1fdcbc2fe733f38dc07ae3d411a1ccf777ecef56ddec97  104 bytes  224 us
#         dcd <= dcd::printbyp              {"primary_key":"dcd.name"}
[(dcd,printbyp)->dcd]: CONSOLE OUTPUT BEGIN =====================
`printbyp` executing.
`_primary_key`: dcd.name found; printing.
{dcd.name, nothin}
`printbyp` finished executing.
[(dcd,printbyp)->dcd]: CONSOLE OUTPUT END   =====================
warning: transaction executed locally, but may not be confirmed by the network yet
```

```
~/binary_extension_contract $ cldcd push action dcd regpkey '{"primary_key":"dcd.name2"}' -p dcd
```

```
executed transaction: 75a135d1279a9c967078b0ebe337dc0cd58e1ccd07e370a899d9769391509afc  104 bytes  227 us
#         dcd <= dcd::regpkey               {"primary_key":"dcd.name2"}
[(dcd,regpkey)->dcd]: CONSOLE OUTPUT BEGIN =====================
`regpkey` executing.
`_primary_key`: dcd.name2 not found; registering.
`regpkey` finished executing.
[(dcd,regpkey)->dcd]: CONSOLE OUTPUT END   =====================
warning: transaction executed locally, but may not be confirmed by the network yet
```

Nice! The smart contract is now backwards compatible for the future use of its tables and/or actions.

<hr>

Just keep these simple rules in mind when upgrading a smart contract.
If you are adding a new field to a struct currently in use by a `dcd::multi_index` be **SURE** to:
- add the field at the end of the struct.
- wrap the type using an `dcd::binary_extension` type.
