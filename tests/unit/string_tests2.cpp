/**
 *  @file
 *  @copyright defined in dcd.cdt/LICENSE.txt
 */

#include <dcd/tester.hpp>
#include <dcd/datastream.hpp>
#include <dcd/string.hpp>

using std::fill;
using std::move;

using dcd::datastream;
using dcd::string;

// Definitions found in `dcd.cdt/libraries/dcdlib/core/dcd/string.hpp`

DCD_TEST_BEGIN(string_test_ins_null)
   string dcdtr{"abcdefg"};
   const char* null_man{nullptr};
   CHECK_ASSERT( "dcd::string::insert", [&]() {dcdtr.insert(0, null_man, 1);} )
   CHECK_ASSERT( "dcd::string::insert", [&]() {dcdtr.insert(-1, "ooo", 1);} )
DCD_TEST_END

//// string& insert(const size_t pos, const string& str)
DCD_TEST_BEGIN(string_test_ins_to_blank)
   string dcdtr{};
   const string str{"ooo"};
   dcdtr.insert(0, str);
   CHECK_EQUAL( dcdtr.size(), 3 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "ooo"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_at_bgn_single)
   string dcdtr{"abc"};
   const string str{"d"};
   dcdtr.insert(0, str);
   CHECK_EQUAL( dcdtr.size(), 4 )
   CHECK_EQUAL( dcdtr.capacity(), 8 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "dabc"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_at_bgn_mul_1)
   string dcdtr{"abc"};
   const string str{"def"};
   dcdtr.insert(0, str);
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "defabc"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_at_bgn_mul_2)
   string dcdtr{"iii"};
   const string str{"ooo"};
   dcdtr.insert(0, str);
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "oooiii") , 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_in_middle_1)
   string dcdtr{"iii"};
   const string str{"ooo"};
   dcdtr.insert(1, str);
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "ioooii") , 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_in_middle_2)
   string dcdtr{"iii"};
   const string str{"ooo"};
   dcdtr.insert(2, str);
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "iioooi") , 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_at_end)
   string dcdtr{"iii"};
   const string str{"ooo"};
   dcdtr.insert(3, str);
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "iiiooo") , 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_neg_index_1)
   string dcdtr{"abcdefg"};
   const string str{"ooo"};
   CHECK_ASSERT( "dcd::string::insert", [&]() {dcdtr.insert(-1, str);} )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_op_pl_1)
   string dcdtr{""};
   string str{""};
   str += "ooo";
   dcdtr.insert(0, str);
   CHECK_EQUAL( dcdtr.size(), 3 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "ooo"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_op_pl_2)
   string dcdtr{""};
   dcdtr += "abc";
   string str{""};
   str += "d";
   dcdtr.insert(0, str);
   CHECK_EQUAL( dcdtr.size(), 4 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "dabc"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_op_pl_3)
   string dcdtr{""};
   dcdtr += "abc";
   string str{""};
   str += "def";
   dcdtr.insert(0, str);
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "defabc"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_op_pl_4)
   string dcdtr{""};
   dcdtr += "iii";
   string str{""};
   str += "ooo";
   dcdtr.insert(0, str);
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "oooiii") , 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_op_pl_5)
   string dcdtr{""};
   dcdtr += "iii";
   string str{""};
   str += "ooo";
   dcdtr.insert(1, str);
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "ioooii") , 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_op_pl_6)
   string dcdtr{""};
   dcdtr += "iii";
   string str{""};
   str += "ooo";
   dcdtr.insert(2, str);
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "iioooi") , 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_op_pl_7)
   string dcdtr{""};
   dcdtr += "iii";
   string str{""};
   str += "ooo";
   dcdtr.insert(3, str);
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "iiiooo") , 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_neg_index_2)
   string dcdtr{"abcdefg"};
   string str{"ooo"};
   CHECK_ASSERT( "dcd::string::insert", [&]() {dcdtr.insert(-1, str);} )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_capacity)
   string dcdtr = "hello";
   dcdtr.insert(0, "0", 1); /// `_capacity` is now 12; `_begin` now holds `std::unique_ptr<char[]>`
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "0hello") , 0 )

   dcdtr.insert(0, "h", 1);
   CHECK_EQUAL( dcdtr.size(), 7 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "h0hello") , 0 )
DCD_TEST_END

//// string& erase(size_t pos = 0, size_t len = npos)
DCD_TEST_BEGIN(string_test_erase)
   string dcdtr{"abcdefgh"};
   dcdtr.erase();
   CHECK_EQUAL( dcdtr.size(), 0 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), ""), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_at_zero)
   string dcdtr{"abcdefgh"};
   dcdtr.erase(0);
   CHECK_EQUAL( dcdtr.size(), 0 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), ""), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_to_npos)
   string dcdtr{"abcdefgh"};
   dcdtr.erase(0, string::npos);
   CHECK_EQUAL( dcdtr.size(), 0 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), ""), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_1)
   string dcdtr{"abcdefgh"};
   dcdtr.erase(1, string::npos);
   CHECK_EQUAL( dcdtr.size(), 1 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "a"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_2)
   string dcdtr{"abcdefgh"};
   dcdtr.erase(2, string::npos);
   CHECK_EQUAL( dcdtr.size(), 2 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "ab"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_3)
   string dcdtr{"abcdefgh"};
   dcdtr.erase(3, string::npos);
   CHECK_EQUAL( dcdtr.size(), 3 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abc"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_4)
   string dcdtr{"abcdefgh"};
   dcdtr.erase(4, string::npos);
   CHECK_EQUAL( dcdtr.size(), 4 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcd"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_5)
   string dcdtr{"abcdefgh"};
   dcdtr.erase(5, string::npos);
   CHECK_EQUAL( dcdtr.size(), 5 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcde"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_6)
   string dcdtr{"abcdefgh"};
   dcdtr.erase(6, string::npos);
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdef"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_7)
   string dcdtr{"abcdefgh"};
   dcdtr.erase(7, string::npos);
   CHECK_EQUAL( dcdtr.size(), 7 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdefg"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_8)
   string dcdtr{"abcdefgh"};
   dcdtr.erase(8, string::npos);
   CHECK_EQUAL( dcdtr.size(), 8 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdefgh"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_8_len_0)
   string dcdtr{"abcdefgh"};
   dcdtr.erase(8, 0);
   CHECK_EQUAL( dcdtr.size(), 8 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdefgh"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_neg_index_1)
   string dcdtr{"abcdefg"};
   CHECK_ASSERT( "dcd::string::erase", [&]() {dcdtr.erase(-1, 1);} )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_op_pl)
   string dcdtr{""};
   dcdtr += "abcdefgh";

   dcdtr.erase();
   CHECK_EQUAL( dcdtr.size(), 0 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), ""), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_at_0_op_pl)
   string dcdtr{""};
   dcdtr += "abcdefgh";

   dcdtr.erase(0);
   CHECK_EQUAL( dcdtr.size(), 0 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), ""), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_at_0_op_pl_npos)
   string dcdtr{""};
   dcdtr += "abcdefgh";

   dcdtr.erase(0, string::npos);
   CHECK_EQUAL( dcdtr.size(), 0 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), ""), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_1_op_pl)
   string dcdtr{""};
   dcdtr += "abcdefgh";

   dcdtr.erase(1, string::npos);
   CHECK_EQUAL( dcdtr.size(), 1 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "a"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_2_op_pl)
   string dcdtr{""};
   dcdtr += "abcdefgh";

   dcdtr.erase(2, string::npos);
   CHECK_EQUAL( dcdtr.size(), 2 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "ab"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_3_op_pl)
   string dcdtr{""};
   dcdtr += "abcdefgh";

   dcdtr.erase(3, string::npos);
   CHECK_EQUAL( dcdtr.size(), 3 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abc"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_4_op_pl)
   string dcdtr{""};
   dcdtr += "abcdefgh";

   dcdtr.erase(4, string::npos);
   CHECK_EQUAL( dcdtr.size(), 4 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcd"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_5_op_pl)
   string dcdtr{""};
   dcdtr += "abcdefgh";

   dcdtr.erase(5, string::npos);
   CHECK_EQUAL( dcdtr.size(), 5 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcde"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_6_op_pl)
   string dcdtr{""};
   dcdtr += "abcdefgh";

   dcdtr.erase(6, string::npos);
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdef"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_7_op_pl)
   string dcdtr{""};
   dcdtr += "abcdefgh";

   dcdtr.erase(7, string::npos);
   CHECK_EQUAL( dcdtr.size(), 7 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdefg"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_8_op_pl)
   string dcdtr{""};
   dcdtr += "abcdefgh";

   dcdtr.erase(8, string::npos);
   CHECK_EQUAL( dcdtr.size(), 8 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdefgh"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_at_8_op_pl)
   string dcdtr{""};
   dcdtr += "abcdefgh";

   dcdtr.erase(8, 0);
   CHECK_EQUAL( dcdtr.size(), 8 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdefgh"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_erase_neg_index_2)
   string dcdtr{"abcdefg"};
   CHECK_ASSERT( "dcd::string::erase", [&]() {dcdtr.erase(-1, 1);} )
DCD_TEST_END

//// string& append(const char* str)
DCD_TEST_BEGIN(string_test_append_to_blank_1)
   string dcdtr{};
   const char* str{"iii"};
   dcdtr.append(str);
   CHECK_EQUAL( dcdtr.size(), 3 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "iii"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_append_1)
   string dcdtr{"abcdefg"};
   const char* str{"iii"};
   dcdtr.append(str);
   CHECK_EQUAL( dcdtr.size(), 10 )
   CHECK_EQUAL( dcdtr.capacity(), 20 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdefgiii"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_append_null)
   string dcdtr{"abcdefg"};
   const char* null_man{nullptr};
   CHECK_ASSERT( "dcd::string::append", [&]() {dcdtr.append(null_man);} )
DCD_TEST_END

//// string& append(const string& str)
DCD_TEST_BEGIN(string_test_append_to_blank_2)
   string dcdtr{};
   const string str{"iii"};
   dcdtr.append(str);
   CHECK_EQUAL( dcdtr.size(), 3 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "iii"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_append_2)
   string dcdtr{"abcdefg"};
   const string str{"iii"};
   dcdtr.append(str);
   CHECK_EQUAL( dcdtr.size(), 10 )
   CHECK_EQUAL( dcdtr.capacity(), 20 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdefgiii"), 0 )
DCD_TEST_END

//// string& operator+=(const char c)
DCD_TEST_BEGIN(string_test_append_3)
   string dcdtr0{};
   string dcdtr1{"a"};
   string dcdtr2{"abcdef"};

   dcdtr0 += 'c';
   CHECK_EQUAL( dcdtr0.size(), 1 )
   CHECK_EQUAL( dcdtr0.capacity(), 2 )
   CHECK_EQUAL( strcmp(dcdtr0.c_str(), "c"), 0 )

   dcdtr1 += 'c';
   dcdtr1 += 'c';
   CHECK_EQUAL( dcdtr1.size(), 3 )
   CHECK_EQUAL( dcdtr1.capacity(), 4 )
   CHECK_EQUAL( strcmp(dcdtr1.c_str(), "acc"), 0 )

   dcdtr2 += 'c';
   CHECK_EQUAL( dcdtr2.size(), 7 )
   CHECK_EQUAL( dcdtr2.capacity(), 14 )
   CHECK_EQUAL( strcmp(dcdtr2.c_str(), "abcdefc"), 0 )
DCD_TEST_END

//// string& operator+=(const char* rhs)
DCD_TEST_BEGIN(string_test_append_op_pl_1)
   string dcdtr0{};
   string dcdtr1{"a"};
   string dcdtr2{"abcdef"};
   string dcdtr3{"abcdef"};

   dcdtr0 += "c";
   CHECK_EQUAL( dcdtr0.size(), 1 )
   CHECK_EQUAL( dcdtr0.capacity(), 2 )
   CHECK_EQUAL( strcmp(dcdtr0.c_str(), "c"), 0 )

   dcdtr1 += "c";
   dcdtr1 += "c";
   CHECK_EQUAL( dcdtr1.size(), 3 )
   CHECK_EQUAL( dcdtr1.capacity(), 4 )
   CHECK_EQUAL( strcmp(dcdtr1.c_str(), "acc"), 0 )

   dcdtr2 += "c";
   CHECK_EQUAL( dcdtr2.size(), 7 )
   CHECK_EQUAL( dcdtr2.capacity(), 14 )
   CHECK_EQUAL( strcmp(dcdtr2.c_str(), "abcdefc"), 0 )

   dcdtr3 += "ghijklm";
   CHECK_EQUAL( dcdtr3.size(), 13 )
   CHECK_EQUAL( dcdtr3.capacity(), 26 )
   CHECK_EQUAL( strcmp(dcdtr3.c_str(), "abcdefghijklm"), 0 )
DCD_TEST_END

//// string& operator+=(const string& rhs)
DCD_TEST_BEGIN(string_test_append_op_pl_2)
   string dcdtr0{};
   string dcdtr1{"a"};
   string dcdtr2{"abcdef"};
   string dcdtr3{"abcdef"};

   dcdtr0 += string{"c"};
   CHECK_EQUAL( dcdtr0.size(), 1 )
   CHECK_EQUAL( dcdtr0.capacity(), 2 )
   CHECK_EQUAL( strcmp(dcdtr0.c_str(), "c"), 0 )

   dcdtr1 += string{"c"};
   dcdtr1 += string{"c"};
   CHECK_EQUAL( dcdtr1.size(), 3 )
   CHECK_EQUAL( dcdtr1.capacity(), 4 )
   CHECK_EQUAL( strcmp(dcdtr1.c_str(), "acc"), 0 )

   dcdtr2 += string{"c"};
   CHECK_EQUAL( dcdtr2.size(), 7 )
   CHECK_EQUAL( dcdtr2.capacity(), 14 )
   CHECK_EQUAL( strcmp(dcdtr2.c_str(), "abcdefc"), 0 )

   dcdtr3 += string{"ghijklm"};
   CHECK_EQUAL( dcdtr3.size(), 13 )
   CHECK_EQUAL( dcdtr3.capacity(), 26 )
   CHECK_EQUAL( strcmp(dcdtr3.c_str(), "abcdefghijklm"), 0 )
DCD_TEST_END

//// string& operator+=(const string& s)
DCD_TEST_BEGIN(string_test_append_op_pl_3)
   string dcdtr0{"a"};
   string dcdtr1{"b"};
   CHECK_EQUAL( dcdtr0.size(), 1 )
   dcdtr0 += dcdtr1;
   CHECK_EQUAL( dcdtr0.size(), 2 )
   CHECK_EQUAL( strcmp(dcdtr0.c_str(), "ab"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_append_op_pl_4)
   string dcdtr0{"abc"};
   string dcdtr1{"def"};
   CHECK_EQUAL( dcdtr0.size(), 3 )
   dcdtr0 += dcdtr1;
   CHECK_EQUAL( dcdtr0.size(), 6 )
   CHECK_EQUAL( strcmp(dcdtr0.c_str(), "abcdef"), 0 )
DCD_TEST_END

//// inline void print(dcd::string str)
DCD_TEST_BEGIN(string_test_print)
   const string dcdtr0{""};
   const string dcdtr1{"abc"};
   const string dcdtr2{"abcdef"};

   CHECK_PRINT( "", [&](){ print(dcdtr0); } )
   CHECK_PRINT( "abc", [&](){ print(dcdtr1); } )
   CHECK_PRINT( "abcdef", [&](){ print(dcdtr2); } )
DCD_TEST_END

//// friend bool operator< (const string& lhs, const string& rhs)
DCD_TEST_BEGIN(string_test_less_than)
   const string dcdtr0{"abc"};
   const string dcdtr1{"def"};
   CHECK_EQUAL( (dcdtr0 < dcdtr0), false )
   CHECK_EQUAL( (dcdtr1 < dcdtr1), false )
   CHECK_EQUAL( (dcdtr0 < dcdtr1), true )
DCD_TEST_END

//// friend bool operator> (const string& lhs, const string& rhs)
DCD_TEST_BEGIN(string_test_gt)
   const string dcdtr0{"abc"};
   const string dcdtr1{"def"};
   CHECK_EQUAL( (dcdtr0 > dcdtr0), false )
   CHECK_EQUAL( (dcdtr1 > dcdtr1), false )
   CHECK_EQUAL( (dcdtr0 > dcdtr1), false )
DCD_TEST_END

//// friend bool operator<=(const string& lhs, const string& rhs)
DCD_TEST_BEGIN(string_test_lt_or_eq)
   const string dcdtr0{"abc"};
   const string dcdtr1{"def"};
   CHECK_EQUAL( (dcdtr0 <= dcdtr0), true )
   CHECK_EQUAL( (dcdtr1 <= dcdtr1), true )
   CHECK_EQUAL( (dcdtr0 <= dcdtr1), true )
DCD_TEST_END

//// friend bool operator>=(const string& lhs, const string& rhs)
DCD_TEST_BEGIN(string_test_gt_or_eq)
   const string dcdtr0{"abc"};
   const string dcdtr1{"def"};
   CHECK_EQUAL( (dcdtr0 >= dcdtr0), true )
   CHECK_EQUAL( (dcdtr1 >= dcdtr1), true )
   CHECK_EQUAL( (dcdtr0 >= dcdtr1), false )
DCD_TEST_END

//// friend bool operator==(const string& lhs, const string& rhs)
DCD_TEST_BEGIN(string_test_equal)
   const string dcdtr0{"abc"};
   const string dcdtr1{"def"};
   CHECK_EQUAL( (dcdtr0 == dcdtr0), true )
   CHECK_EQUAL( (dcdtr1 == dcdtr1), true )
   CHECK_EQUAL( (dcdtr0 == dcdtr1), false )
DCD_TEST_END

//// friend bool operator!=(const string& lhs, const string& rhs)
DCD_TEST_BEGIN(string_test_not_equal)
   const string dcdtr0{"abc"};
   const string dcdtr1{"def"};
   CHECK_EQUAL( (dcdtr0 != dcdtr0), false )
   CHECK_EQUAL( (dcdtr1 != dcdtr1), false )
   CHECK_EQUAL( (dcdtr0 != dcdtr1), true )
DCD_TEST_END

//// template<typename DataStream>
//// DataStream& operator<<(DataStream& ds, const string& str)
//// DataStream& operator>>(DataStream& ds, string& str)
DCD_TEST_BEGIN(string_test_stream_io_1)
   constexpr uint16_t buffer_size{256};
   char datastream_buffer[buffer_size]{}; // Buffer for the datastream to point to
   char buffer[buffer_size]; // Buffer to compare `datastream_buffer` with
   datastream<char*> ds{datastream_buffer, buffer_size};

   ds.seekp(0);
   fill(std::begin(datastream_buffer), std::end(datastream_buffer), 0);
   const string cstr {""};
   string str{};
   ds << cstr;
   ds.seekp(0);
   ds >> str;
   CHECK_EQUAL( cstr, str )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_stream_io_2)
   constexpr uint16_t buffer_size{256};
   char datastream_buffer[buffer_size]{};
   char buffer[buffer_size];
   datastream<char*> ds{datastream_buffer, buffer_size};

   ds.seekp(0);
   fill(std::begin(datastream_buffer), std::end(datastream_buffer), 0);
   const string cstr {"a"};
   string str{};
   ds << cstr;
   ds.seekp(0);
   ds >> str;
   CHECK_EQUAL( cstr, str )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_stream_io_3)
   constexpr uint16_t buffer_size{256};
   char datastream_buffer[buffer_size]{};
   char buffer[buffer_size];
   datastream<char*> ds{datastream_buffer, buffer_size};

   ds.seekp(0);
   fill(std::begin(datastream_buffer), std::end(datastream_buffer), 0);
   const string cstr {"abcdefghi"};
   string str{};
   ds << cstr;
   ds.seekp(0);
   ds >> str;
   CHECK_EQUAL( cstr, str )
DCD_TEST_END

int main(int argc, char* argv[]) {
   bool verbose = false;
   if( argc >= 2 && std::strcmp( argv[1], "-v" ) == 0 ) {
      verbose = true;
   }
   silence_output(!verbose);

   DCD_TEST(string_test_ins_null)
   DCD_TEST(string_test_ins_to_blank)
   DCD_TEST(string_test_ins_at_bgn_single)
   DCD_TEST(string_test_ins_at_bgn_mul_1)
   DCD_TEST(string_test_ins_at_bgn_mul_2)
   DCD_TEST(string_test_ins_in_middle_1)
   DCD_TEST(string_test_ins_in_middle_2)
   DCD_TEST(string_test_ins_at_end)
   DCD_TEST(string_test_ins_neg_index_1)
   DCD_TEST(string_test_ins_op_pl_1)
   DCD_TEST(string_test_ins_op_pl_2)
   DCD_TEST(string_test_ins_op_pl_3)
   DCD_TEST(string_test_ins_op_pl_4)
   DCD_TEST(string_test_ins_op_pl_5)
   DCD_TEST(string_test_ins_op_pl_6)
   DCD_TEST(string_test_ins_op_pl_7)
   DCD_TEST(string_test_ins_neg_index_2)
   DCD_TEST(string_test_ins_capacity)
   DCD_TEST(string_test_erase)
   DCD_TEST(string_test_erase_at_zero)
   DCD_TEST(string_test_erase_to_npos)
   DCD_TEST(string_test_erase_1)
   DCD_TEST(string_test_erase_2)
   DCD_TEST(string_test_erase_3)
   DCD_TEST(string_test_erase_4)
   DCD_TEST(string_test_erase_5)
   DCD_TEST(string_test_erase_6)
   DCD_TEST(string_test_erase_7)
   DCD_TEST(string_test_erase_8)
   DCD_TEST(string_test_erase_8_len_0)
   DCD_TEST(string_test_erase_neg_index_1)
   DCD_TEST(string_test_erase_op_pl)
   DCD_TEST(string_test_erase_at_0_op_pl)
   DCD_TEST(string_test_erase_at_0_op_pl_npos)
   DCD_TEST(string_test_erase_1_op_pl)
   DCD_TEST(string_test_erase_2_op_pl)
   DCD_TEST(string_test_erase_3_op_pl)
   DCD_TEST(string_test_erase_4_op_pl)
   DCD_TEST(string_test_erase_5_op_pl)
   DCD_TEST(string_test_erase_6_op_pl)
   DCD_TEST(string_test_erase_7_op_pl)
   DCD_TEST(string_test_erase_8_op_pl)
   DCD_TEST(string_test_erase_at_8_op_pl)
   DCD_TEST(string_test_erase_neg_index_2)
   DCD_TEST(string_test_append_to_blank_1)
   DCD_TEST(string_test_append_1)
   DCD_TEST(string_test_append_null)
   DCD_TEST(string_test_append_to_blank_2)
   DCD_TEST(string_test_append_2)
   DCD_TEST(string_test_append_3)
   DCD_TEST(string_test_append_op_pl_1)
   DCD_TEST(string_test_append_op_pl_2)
   DCD_TEST(string_test_append_op_pl_3)
   DCD_TEST(string_test_append_op_pl_4)
   DCD_TEST(string_test_print)
   DCD_TEST(string_test_less_than)
   DCD_TEST(string_test_gt)
   DCD_TEST(string_test_lt_or_eq)
   DCD_TEST(string_test_gt_or_eq)
   DCD_TEST(string_test_equal)
   DCD_TEST(string_test_not_equal)
   DCD_TEST(string_test_stream_io_1)
   DCD_TEST(string_test_stream_io_2)
   DCD_TEST(string_test_stream_io_3)

   return has_failed();
}
