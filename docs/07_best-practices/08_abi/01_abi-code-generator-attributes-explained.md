---
content_title: ABI/Code generator attributes
link_text: ABI/Code generator attributes
---

The new ABI generator tool uses C++11 or GNU style attributes to mark `actions` and `tables`.

## [[dcd::action]]
This attribute marks a method as an action.
Example (four ways to declare an action for ABI generation):
```cpp
// this is the C++11 and greater style attribute
[[dcd::action]]
void testa( name n ) {
   // do something
}

// this is the GNU style attribute, this can be used in C code and prior to C++ 11
__attribute__((dcd_action))
void testa( name n ){
   // do something
}

struct [[dcd::action]] testa {
   name n;
   DCDLIB_SERIALIZE( testa, (n) )
};

struct __attribute__((dcd_action)) testa {
   name n;
   DCDLIB_SERIALIZE( testa, (n) )
};
```

If your action name is not a valid [DCD name](../02_naming-conventions.md) you can explicitly specify the name in the attribute ```c++ [[dcd::action("<valid action name>")]]```

## [[dcd::table]]
Example (two ways to declare a table for ABI generation):
```cpp
struct [[dcd::table]] testtable {
   uint64_t owner;
   /* all other fields */
};

struct __attribute__((dcd_table)) testtable {
   uint64_t owner;
   /* all other fields */
};

typedef dcd::multi_index<"tablename"_n, testtable> testtable_t;
```

If you don't want to use the multi-index you can explicitly specify the name in the attribute ```c++ [[dcd::table("<valid action name>")]]```.

## [[dcd::contract("ANY_NAME_YOU_LIKE")]]
```cpp
class [[dcd::contract("ANY_NAME_YOU_LIKE")]] test_contract : public dcd::contract {
};
```

The code above will mark this `class` as being an `DCD` contract, this allows for namespacing of contracts, i.e. you can include headers like `dcd::token` and not have `dcd::token`'s actions/tables wind up in you ABI or generated dispatcher.

## [[dcd::on_notify("VALID_DCD_ACCOUNT_NAME::VALID_DCD_ACTION_NAME")]]
```cpp
[[dcd::on_notify("dcd.token::transfer")]]
void on_token_transfer(name from, name to, assert quantity, std::string memo) {
   // do something on dcd.token contract's transfer action from any account to the account where the contract is deployed.
}

[[dcd::on_notify("*::transfer")]]
void on_any_transfer(name from, name to, assert quantity, std::string memo) {
   // do something on any contract's transfer action from any account to the account where the contract is deployed.
}
```

## [[dcd::wasm_entry]]
```cpp
[[dcd::wasm_entry]]
void some_function(...) {
   // do something
}
```

The code above will mark an arbitrary function as an entry point, which will then wrap the function with global constructors (ctors) and global destructors (dtors).  This will allow for the dcd.cdt toolchain to produce WASM binaries for other ecosystems.

## [[dcd::wasm_import]]
```cpp
extern "C" {
   __attribute__((dcd_wasm_import))
   void some_intrinsic(...);
}
```

The code above will mark a function declaration as being a WebAssembly import.  This allows for other compilation modes to specify which functions are import only (i.e. do not link) without having to maintain a secondary file with duplicate declarations.

## [[dcd::action, dcd::read-only]]
The `read-only` attribute marks a method which has been defined as an action as a read-only action.

Example:

```cpp
[[dcd::action, dcd::read-only]]
std::vector<my_struct> get() {
   std::vector<my_struct> ret;
   // retrieve blockchain state and populate the ret vector
   return ret; 
}
```

Contract actions tagged read-only:
* Cannot call insert/update (write) functions on the `Multi-Index API`, nor the `Key Value API`.
* Cannot call `deferred transactions`.
* Cannot call `inline actions`.
* The amount of data returned by read-only queries is limited by the action return value size. By default these are set to 256 bytes by `default_max_action_return_value_size`.

The `dcd-cpp` and `dcd-cc` tools will generate an error and terminate compilation if an action tagged read-only attempts to call insert/update (write) functions, `deferred transactions` or `inline actions`. However, if the command-line override option `--warn-action-read-only` is used, the `dcd-cpp` and `dcd-cc` tools will issue a warning and continue compilation.
