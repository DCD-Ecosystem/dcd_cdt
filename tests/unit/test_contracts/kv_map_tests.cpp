#include <dcd/dcd.hpp>
#include <dcd/table.hpp>

struct test_record {
   int pk;
   float s;
   std::string n;
};

class [[dcd::contract]] kv_map_tests : public dcd::contract {
public:
   using contract::contract;

   using testmap_t = dcd::kv::map<"testmap"_n, int, float>;
   using testmap2_t = dcd::kv::map<"testmap2"_n, std::string, std::string>;
   using testmap3_t = dcd::kv::map<"testmap3"_n, int, float>;
   using testmap4_t = dcd::kv::map<"testmap4"_n, int, float>;

   [[dcd::action]]
   void test() {
      testmap_t t = { {33, 23.4f}, {10, 13.44f}, {103, 334.3f} };

      auto p = t[33];

      p = 102.23; // note here this will update the held value and do a db set

      testmap_t t2;

      dcd::check(p == 102.23f, "should be the same value");
      dcd::check(p == t2.at(33), "should be the same value");

      auto it = t.begin();

      auto& el = *it;

      dcd::check(el.second() == 13.44f, "should still be the same from before");

      testmap2_t t3 = { {"dcd", "fast"}, {"bit...", "hmm"} };

      auto it2 = t3.begin();
      auto& el2 = *it2;

      dcd::check(el2.value == std::string("hmm"), "should point to the lowest lexicographic key");

      ++it2;
      auto& el3 = *it2;

      dcd::check(el3.second() == std::string("fast"), "should now be pointing to the next");

      ++it2;

      auto it3 = std::move(it2);

      it2 = t3.end();

      dcd::check(it2 == it3, "they should be at the end and pointing to the same thing");
      dcd::check(!it2.is_valid(), "iterator should be at end");

      dcd::check(!it3.is_valid(), "iterator should be at end");
   }

   [[dcd::action]]
   void iter() {
      testmap_t t = { {34, 23.4f}, {11, 13.44f}, {104, 334.3f}, {5, 33.42f} };

      float test_vals[7] = {33.42f, 13.44f, 13.44f, 102.23f, 23.4f, 334.3f, 334.3f};

      int i = 0;

      // test that this will work with auto ranged for loop
      for ( const auto& e : t ) {
         dcd::check(e.second() == test_vals[i++], "invalid value in iter test");
      }
   }

   [[dcd::action]]
   void erase() {
      testmap_t t;

      t.contains(34);
      t.erase(34);

      dcd::check(!t.contains(34), "should have erased a value");
   }

   [[dcd::action]]
   void eraseexcp() {
      testmap_t t;
      t.at(34); // this should cause an assertion
   }

   [[dcd::action]]
   void bounds() {
      testmap3_t t = {{33, 10}, {10, 41.2f}, {11, 100.100f}, {2, 17.42f}};

      auto it = t.lower_bound(11);

      dcd::check(it->first() == testmap3_t::full_key((int)11), "should be pointing to 11");

      it = t.lower_bound(31);

      dcd::check(it->first() == testmap3_t::full_key((int)33), "should be pointing to 33");

      it = t.lower_bound(36);

      dcd::check(!it.is_valid(), "should be pointing to end");

      auto it2 = t.lower_bound(1);

      dcd::check(it2->first() == testmap3_t::full_key((int)2), "should be pointing to 2");

      it = t.upper_bound(10);

      dcd::check(it->first() == testmap3_t::full_key((int)11), "should be pointing to 11");

      it = t.upper_bound(33);

      dcd::check(!it.is_valid(), "should be pointing to end");
   }

   [[dcd::action]]
   void ranges() {
      testmap3_t t = {{17, 9.9f}};

      auto range = t.equal_range(16);

      dcd::check(range.first->first() == testmap3_t::full_key((int)17), "should be pointing to 17");
      dcd::check(range.second->first() == testmap3_t::full_key((int)17), "should be pointing to 17");

      range = t.equal_range(1);

      dcd::check(range.first->first() == testmap3_t::full_key((int)2), "should be pointing to 2");
      dcd::check(range.second->first() == testmap3_t::full_key((int)2), "should be pointing to 2");

      auto vec = t.ranged_slice(10, 30);

      dcd::check(vec.size() == 3, "should contain 3 elements");
      dcd::check((float)vec[0].second() == 41.2f, "should contain 41.2");
      dcd::check((float)vec[1].second() == 100.100f, "should contain 100.100");
      dcd::check((float)vec[2].second() == 9.9f, "should contain 9.9");
   }

   [[dcd::action]]
   void empty() {
      testmap3_t t = {{33, 10}, {10, 41.2f}, {11, 100.100f}, {2, 17.42f}};

      dcd::check(!t.empty(), "t shouldn't be empty");

      testmap4_t t2 = {{10, 10}, {13, 13}};

      dcd::check(!t2.empty(), "t2 shouln't be empty");

      t2.erase(10);
      t2.erase(13);

      dcd::check(t2.empty(), "t2 should now be empty");
   }

   [[dcd::action]]
   void gettmpbuf() {
      testmap3_t t = {{33, 10}, {10, 41.2f}, {11, 100.100f}, {2, 17.42f}};

      auto buff = t.get_tmp_buffer(34); // ensure this interface doesn't regress

      auto iter = t.lower_bound(11);

      dcd::check(iter->value == 100.100f, "should be equal and not fail to compile");
   }

   [[dcd::action]]
   void constrct() {
      using map_t = dcd::kv::map<"map"_n, float, dcd::time_point>;
      map_t m = {{13.3f, dcd::time_point{}}};

      m[13.3f] = dcd::time_point{dcd::microseconds{(int64_t)13}};

      auto iter = m.find(13.3f);
      auto val = iter->second();

      auto expected = dcd::time_point{dcd::microseconds{(int64_t)13}};
      dcd::check(val == expected, "should be equal and not fail to compile");

      auto iter2 = m.find(10);
      dcd::check(iter2 == m.end(), "shouldn't be found");

      const auto citer = m.find(13.3f);
      dcd::check(citer->second() == val, "should still be the same with const and shouldn't fail to compile");
   }

   struct __attribute__((packed)) key_struct_fragments {
      uint8_t  magic;
      uint64_t table;
      uint64_t index;
   };

   [[dcd::action]]
   void keys() {
      using map_t = dcd::kv::map<"map"_n, float, dcd::time_point>;
      map_t m = {{13.3f, dcd::time_point{}}};

      auto iter = m.find(13.3f);
      auto k = iter->first();

      key_struct_fragments kfs;
      memcpy(&kfs, iter->first().data(), sizeof(kfs));

      kfs.table = __builtin_bswap64(kfs.table);
      kfs.index = __builtin_bswap64(kfs.index);

      dcd::check(kfs.magic == 1, "should still be hardcoded to 1 for now");
      dcd::check(kfs.table == dcd::name("map").value, "table should be named 'map'");
      dcd::check(kfs.index == dcd::name("map.index").value, "index should be named 'map.index'");
   }
};
