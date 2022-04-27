#include <dcd/dcd.hpp>
#include <dcd/table.hpp>

class [[dcd::contract]] read_only_query_tests : public dcd::contract {
public:
   struct my_struct {
      uint32_t id;
      std::string name;
      uint32_t gender;
      uint32_t age;

      bool operator==(const my_struct& b) const {
         return id == b.id &&
                name == b.name &&
                gender == b.gender &&
                age == b.age;
      }
   };

   struct [[dcd::table]] my_table_m : dcd::kv::table<my_struct, "roqm"_n> {
      KV_NAMED_INDEX("id"_n, id)

      my_table_m(dcd::name contract_name) {
         init(contract_name, id);
      }
   };
   struct [[dcd::table]] my_table_f : dcd::kv::table<my_struct, "roqf"_n> {
      KV_NAMED_INDEX("id"_n, id)

      my_table_f(dcd::name contract_name) {
         init(contract_name, id);
      }
   };
   using contract::contract;
   my_struct s1{
      .id = 1,
      .name = "Bob Smith",
      .gender = 1,
      .age = 25
   };
   my_struct s2{
      .id = 2,
      .name = "Alice Smith",
      .gender = 0,
      .age = 20
   };
   my_struct s3{
      .id = 3,
      .name = "John Smith",
      .gender = 1,
      .age = 42
   };
   my_struct s4{
      .id = 4,
      .name = "Jack Smith",
      .gender = 1,
      .age = 27
   };
   my_struct s5{
      .id = 5,
      .name = "Youko Niihara",
      .gender = 0,
      .age = 26
   };
   my_struct s6{
      .id = 6,
      .name = "Rose Lee",
      .gender = 0,
      .age = 18,
   };
   my_struct s7{
      .id = 7,
      .name = "Youko Kawakami",
      .gender = 0,
      .age = 25,
   };
   my_struct s8{
      .id = 8,
      .name = "Yuu Yamada",
      .gender = 0,
      .age = 24,
   };

   [[dcd::action]]
   void setup() {
      my_table_m tm{get_self()};
      my_table_f tf{get_self()};

      tm.put(s1, get_self());
      tf.put(s2, get_self());
      tm.put(s3, get_self());
      tm.put(s4, get_self());
      tf.put(s5, get_self());
      tf.put(s6, get_self());
      tf.put(s7, get_self());
      tf.put(s8, get_self());
  }

   [[dcd::action, dcd::read_only]]
   std::vector<my_struct> get() {
      my_table_m tm{get_self()};
      my_table_f tf{get_self()};

      std::vector<my_struct> ret;
      auto itm = tm.id.begin();
      auto itm_e = tm.id.end();
      dcd::cout << "Males: \n";
      while(itm != itm_e){
         auto row = itm.value(); 
         dcd::cout << "id=" << row.id << ", name=" << row.name << ",gender=" << row.gender << ", age=" << row.age << "\n"; 
         my_struct s;
         s.id = row.id;
         s.name = row.name;
         s.gender = row.gender;
         s.age = row.age;
         ret.push_back(s);
         ++itm;
      }
      dcd::cout << "Females: \n"; 
      auto itf = tf.id.begin();
      auto itf_e = tf.id.end();
      while(itf != itf_e){
         auto row = itf.value();
         dcd::cout << "id=" << row.id << ", name=" << row.name << ",gender=" << row.gender << ", age=" << row.age << "\n"; 
         my_struct s;
         s.id = row.id;
         s.name = row.name;
         s.gender = row.gender;
         s.age = row.age;
         ret.push_back(s);
        ++itf; 
     }
     return ret;
   }
   [[dcd::action]]
   // usage: cldcd -v push action dcd put '{"id":10,"name":"GULU","gender":1,"age":128}' -p dcd@active
   void put(uint32_t id, std::string name, uint32_t gender, uint32_t age ) {
      my_table_m tm{get_self()};
      my_table_f tf{get_self()};
      if(gender == 0){
         tf.put({
         .id = id,
         .name = name,
         .gender = gender,
         .age = age
         }, get_self());
      } else {
         tm.put({
         .id = id,
         .name = name,
         .gender = gender,
         .age = age
         }, get_self());
      }
   }
};
