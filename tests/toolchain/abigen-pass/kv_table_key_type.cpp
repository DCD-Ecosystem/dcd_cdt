#include <dcd/dcd.hpp>
#include <dcd/table.hpp>

class [[dcd::contract]] kv_table_key_type : public dcd::contract {
public:
   using contract::contract;

   struct my_struct {
      dcd::name primary_key;
      std::string foo;
      uint64_t bar;

      std::string fullname;
      uint32_t age;

      std::pair<int, int> a;
      std::optional<float> b;
      std::list<double> c;
      std::vector<int> d;
      std::variant<int, bool, float> e;

      std::tuple<std::string, uint32_t> non_unique_name;

      bool operator==(const my_struct& b) const {
         return primary_key == b.primary_key &&
                foo == b.foo &&
                bar == b.bar &&
                fullname == b.fullname &&
                age == b.age;
      }
   };

   struct [[dcd::table]] my_table : dcd::kv::table<my_struct, "testtable"_n> {
      index<dcd::name> primary_key {
         dcd::name{"primarykey"_n},
         &my_struct::primary_key };

      index<std::string> foo {
         dcd::name{"foo"_n},
         &my_struct::foo };

      index<uint64_t> bar{dcd::name{"bar"_n}, &value_type::bar};

      index<std::tuple<std::string, uint32_t>> non_unique_name {
          dcd::name{"nonunique"_n},
          &my_struct::non_unique_name };

      KV_NAMED_INDEX("age"_n, age)

      my_table(dcd::name contract_name) {
         init(contract_name, primary_key, foo, bar, non_unique_name, age);
      }
   };

   [[dcd::action]]
   void noop() {}

};
