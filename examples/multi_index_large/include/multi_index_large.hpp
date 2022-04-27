#include <dcd/dcd.hpp>
using namespace dcd;

class [[dcd::contract]] multi_index_large : public contract {
   public:
      using contract::contract;
      multi_index_large( name receiver, name code, datastream<const char*> ds )
         : contract(receiver, code, ds), testtab(receiver, receiver.value) {}

      struct [[dcd::table("data")]] main_record {
         uint64_t           id         = 0;

         uint64_t           u64 = 0;
         uint128_t          u128 = 0ULL;
         double             f64 = 0.0L;
         long double        f128 = 0.0L;
         dcd::checksum256 chk256;

         uint64_t                  primary_key()const { return id; }
         uint64_t                  get_u64()const     { return u64; }
         uint128_t                 get_u128()const   { return u128; }
         double                    get_f64()const     { return f64; }
         long double               get_f128()const    { return f128; }
         const dcd::checksum256& get_chk256()const  { return chk256; }

         DCDLIB_SERIALIZE( main_record, (id)(u64)(u128)(f64)(f128)(chk256))
      };

      using test_tables = dcd::multi_index<"testtaba"_n, main_record,
         dcd::indexed_by< "byuu"_n,   dcd::const_mem_fun< main_record, uint64_t,
                                                            &main_record::get_u64 > >,
         dcd::indexed_by< "byuuuu"_n,   dcd::const_mem_fun< main_record, uint128_t,
                                                            &main_record::get_u128 > >,
         dcd::indexed_by< "byf"_n,   dcd::const_mem_fun< main_record, double,
                                                            &main_record::get_f64> >,
         dcd::indexed_by< "byff"_n,   dcd::const_mem_fun< main_record, long double,
                                                            &main_record::get_f128> >,
         dcd::indexed_by< "bychkb"_n, dcd::const_mem_fun< main_record, const dcd::checksum256&,
                                                            &main_record::get_chk256 > >
      >;
      test_tables testtab;

      [[dcd::action]] 
      void set( uint64_t id, uint64_t u64, uint128_t u128,
         double f64, long double f128, dcd::checksum256 chk256 );

      [[dcd::action]] 
      void print( uint64_t id );

      [[dcd::action]] 
      void byf( double f64);

      [[dcd::action]] 
      void byff( long double f128 );

      [[dcd::action]] 
      void byuuuu( uint128_t u128 );

      [[dcd::action]] 
      void bychkb(dcd::checksum256 chk256);

      [[dcd::action]] 
      void mod( uint64_t id, uint64_t u64, uint128_t u128,
         double f64, long double f128, dcd::checksum256 chk256 );

      [[dcd::action]] 
      void del( uint64_t id );
};
