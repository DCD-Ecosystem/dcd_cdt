---
content_title: Naming conventions
---

When implementing DCD smart contracts and when storing data in an DCD blockchain, it is important to follow the established DCD conventions for naming accounts, actions, tables, etc.

## DCD names

*  Applies to all DCD encoded names (accounts, actions, tables, etc.)
*  Encoded as a 64-bit unsigned integer (`uint64_t`) on the blockchain.
*  First 12 characters, if any, encoded in `base32` using characters: `.`, `1-5`, `a-z`
*  13th character, if applicable, encoded in `base16` using characters: `.`, `1-5`, `a-j`

### Standard account names

*  Must contain exactly 12 characters from the `base32` set: `.`, `1-5`, `a-z`
*  13th character not allowed or lesser than 12 characters
*  Must start with a lowercase letter `a-z`
*  Must not end in a dot `.` character

### Non-standard account names

*  May contain between 1 and 12 characters from the `base32` set: `.`, `1-5`, `a-z`
*  13th character not allowed in account name
*  Must not end in a dot `.` character

### Table, struct, class, function (action) names

*  May contain between 1 and 13 characters.
*  First 12 characters, if any, from the `base32` set: `.`, `1-5`, `a-z`
*  13th character, if any, from the `base16` set: `.`, `1-5`, `a-j`

### Format

The figure below showcases a 12 character string formatted into a 64-bit unsigned integer. Note: the 13th char, if any, contains 2<sup>4</sup> = 16 cases per 1 digit (char): 1 (`.`) + 5 (`1-5`) + 10 (`a-j`).

![](naming-conventions-format.png "DCD name format")

## Encoding and decoding

DCD name objects can be created, encoded, and decoded via the `dcd::name` class.

1. To encode an `std::string` into an DCD name object, use the appropriate `dcd::name()` constructor.
2. To encode a `char *` string literal into an DCD name object, you can also use the `""_n` operator.
3. To decode an DCD name object into an `std::string`, use the `dcd::to_string()` function.

### Examples

```cpp
auto dcd_user = dcd::name{user};  //encodes user string to dcd::name object
auto user_str = user_name_obj.to_string(); //decodes dcd::name obj to string
auto standard_account = "standardname"_n;  //encodes literal string to dcd::name
auto non_standard_account = ".standard"_n; //encodes literal string to dcd::name
```
