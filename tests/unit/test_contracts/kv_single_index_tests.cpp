#include <dcd/dcd.hpp>
#include <dcd/table.hpp>

struct my_struct {
   dcd::name primary_key;

   bool operator==(const my_struct b) const {
      return primary_key == b.primary_key;
   }
};

struct my_table : dcd::kv::table<my_struct, "testtable"_n> {
   KV_NAMED_INDEX("primary"_n, primary_key);

   my_table(dcd::name contract_name) {
      init(contract_name, primary_key);
   }
};

class [[dcd::contract]] kv_single_index_tests : public dcd::contract {
public:
   using contract::contract;

   my_struct s{
      .primary_key = "bob"_n
   };
   my_struct s2{
      .primary_key = "alice"_n
   };
   my_struct s3{
      .primary_key = "john"_n
   };
   my_struct s4{
      .primary_key = "joe"_n
   };
   my_struct s5{
      .primary_key = "billy"_n
   };

   [[dcd::action]]
   void setup() {
      my_table t{"kvtest"_n};

      t.put(s3, get_self());
      t.put(s, get_self());
      t.put(s4, get_self());
      t.put(s2, get_self());
      t.put(s5, get_self());
   }

   [[dcd::action]]
   void find() {
      my_table t{"kvtest"_n};
      my_table::iterator end_itr = t.primary_key.end();

      auto itr = t.primary_key.find("bob"_n);
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "bob"_n, "Got the wrong primary_key: bob");

      itr = t.primary_key.find("joe"_n);
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "joe"_n, "Got the wrong primary_key: joe");

      itr = t.primary_key.find("alice"_n);
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "alice"_n, "Got the wrong primary_key: alice");

      itr = t.primary_key.find("john"_n);
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "john"_n, "Got the wrong primary_key: john");

      itr = t.primary_key.find("billy"_n);
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "billy"_n, "Got the wrong primary_key: billy");
   }

   [[dcd::action]]
   void finderror() {
      my_table t{"kvtest"_n};
      auto itr = t.primary_key.find("larry"_n);
      auto val = itr.value();
   }

   [[dcd::action]]
   void get() {
      my_table t{"kvtest"_n};
      auto end_itr = t.primary_key.end();

      auto val = t.primary_key.get("bob"_n);
      dcd::check(val->primary_key == "bob"_n, "Got the wrong value");

      val = t.primary_key.get("william"_n);
      dcd::check(!val, "Should not have gotten a value");

      dcd::check(t.primary_key.exists("bob"_n), "Exists should return true");
      dcd::check(!t.primary_key.exists("william"_n), "Exists should return false");

      auto vval = t.primary_key["bob"_n];
      dcd::check(vval.primary_key == "bob"_n, "Got the wrong value");
   }

   [[dcd::action]]
   void geterror() {
      my_table t{"kvtest"_n};
      auto val = t.primary_key["william"_n];
   }

   [[dcd::action]]
   void bounds() {
      my_table t{"kvtest"_n};
      auto end_itr = t.primary_key.end();

      auto itr = t.primary_key.lower_bound("bob"_n);
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "bob"_n, "Got the wrong primary_key: lower_bound - bob");

      itr = t.primary_key.lower_bound("catherine"_n);
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "joe"_n, "Got the wrong primary_key: lower_bound - joe");

      itr = t.primary_key.lower_bound("william"_n);
      dcd::check(itr == end_itr, "Should be the end");

      itr = t.primary_key.upper_bound("billy"_n);
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "bob"_n, "Got the wrong primary_key: upper_bound - bob");

      itr = t.primary_key.upper_bound("ian"_n);
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "joe"_n, "Got the wrong primary_key: upper_bound - joe");

      itr = t.primary_key.upper_bound("john"_n);
      dcd::check(itr == end_itr, "Should be the end");
   }

   [[dcd::action]]
   void iteration() {
      my_table t{"kvtest"_n};
      auto begin_itr = t.primary_key.begin();
      auto end_itr = t.primary_key.end();

      // operator++
      // ----------
      auto itr = t.primary_key.begin();
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "alice"_n, "Got the wrong beginning");
      ++itr;
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "billy"_n, "Got the wrong value: billy");
      ++itr;
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "bob"_n, "Got the wrong value: bob");
      ++itr;
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "joe"_n, "Got the wrong value: joe");
      ++itr;
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "john"_n, "Got the wrong value: john");
      ++itr;
      dcd::check(itr == end_itr, "Should be the end");

      // operator--
      // ----------
      --itr;
      dcd::check(itr != begin_itr, "Should not be the beginning: 1");
      --itr;
      dcd::check(itr != begin_itr, "Should not be the beginning: 2");
      --itr;
      dcd::check(itr != begin_itr, "Should not be the beginning: 3");
      --itr;
      dcd::check(itr != begin_itr, "Should not be the beginning: 4");
      --itr;
      dcd::check(itr == begin_itr, "Should be the beginning");
   }

   [[dcd::action]]
   void itrerror1() {
      my_table t{"kvtest"_n};
      auto end_itr = t.primary_key.end();
      ++end_itr;
   }

   [[dcd::action]]
   void itrerror2() {
      my_table t{"kvtest"_n};
      auto begin_itr = t.primary_key.begin();
      --begin_itr;
   }

   [[dcd::action]]
   void riteration() {
      my_table t{"kvtest"_n};
      auto begin_itr = t.primary_key.rbegin();
      auto end_itr = t.primary_key.rend();

      // operator++
      // ----------
      auto itr = t.primary_key.rbegin();
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "john"_n, "Got the wrong value: john");
      ++itr;
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "joe"_n, "Got the wrong value: joe");
      ++itr;
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "bob"_n, "Got the wrong value: bob");
      ++itr;
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "billy"_n, "Got the wrong value: billy");
      ++itr;
      dcd::check(itr != end_itr, "Should not be the end");
      dcd::check(itr.value().primary_key == "alice"_n, "Got the wrong beginning");
      ++itr;
      dcd::check(itr == end_itr, "Should be the end");

      // operator--
      // ----------
      --itr;
      dcd::check(itr != begin_itr, "Should not be the beginning: 1");
      --itr;
      dcd::check(itr != begin_itr, "Should not be the beginning: 2");
      --itr;
      dcd::check(itr != begin_itr, "Should not be the beginning: 3");
      --itr;
      dcd::check(itr != begin_itr, "Should not be the beginning: 4");
      --itr;
      dcd::check(itr == begin_itr, "Should be the beginning");

      dcd::check(end_itr > begin_itr, "end should be greater than beginning");
      dcd::check(end_itr >= begin_itr, "end should be greater than or equal to beginning");
      dcd::check(begin_itr < end_itr, "beginning should be less than end");
      dcd::check(begin_itr <= end_itr, "beginning should be less than or equal to end");

      auto b = t.primary_key.rbegin();
      auto c = t.primary_key.rbegin();
      ++c;
      dcd::check(c > b, "c should be greater than b");
      dcd::check(c >= b, "c should be greater than or equal to b");
      dcd::check(b <= c, "b should be less than or equal to c");
      dcd::check(b < c, "b should be less than c");
   }

   [[dcd::action]]
   void ritrerror1() {
      my_table t{"kvtest"_n};
      auto end_itr = t.primary_key.rend();
      ++end_itr;
   }

   [[dcd::action]]
   void ritrerror2() {
      my_table t{"kvtest"_n};
      auto begin_itr = t.primary_key.rbegin();
      --begin_itr;
   }

   [[dcd::action]]
   void range() {
      my_table t{"kvtest"_n};

      std::vector<my_struct> expected{s, s4};
      auto vals = t.primary_key.range("bob"_n, "john"_n);
      dcd::check(vals == expected, "range did not return expected vector");

      expected = {};
      vals = t.primary_key.range("bob"_n, "bob"_n);
      dcd::check(vals == expected, "range did not return expected vector: {} - 1");
      vals = t.primary_key.range("chris"_n, "joe"_n);
      dcd::check(vals == expected, "range did not return expected vector: {} - 2");
      vals = t.primary_key.range("joe"_n, "alice"_n);
      dcd::check(vals == expected, "range did not return expected vector: {} - 3");

      expected = {s2, s5, s, s4, s3};
      vals = t.primary_key.range("alice"_n, "william"_n);
      dcd::check(vals == expected, "range did not return expected vector: {s2, s5, s, s4, s3}");
   }

   [[dcd::action]]
   void erase() {
      my_table t{"kvtest"_n};
      auto end_itr = t.primary_key.end();

      auto v = *(t.primary_key.get("joe"_n));
      t.erase(v);
      auto itr = t.primary_key.find("joe"_n);
      dcd::check(itr == end_itr, "key was not properly deleted");

      std::vector<my_struct> expected = {s};
      auto vals = t.primary_key.range("bob"_n, "john"_n);
      dcd::check(vals == expected, "range did not return expected vector");
   }
};
