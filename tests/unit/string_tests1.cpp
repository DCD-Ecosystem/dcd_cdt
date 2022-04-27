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

//// template <size_t N>
//// string(const char (&str)[N])
DCD_TEST_BEGIN(string_test_ctr_lit)
   const string dcdtr0{"a"};
   const string dcdtr1{"abcdef"};

   CHECK_EQUAL( dcdtr0.size(), 1 )
   CHECK_EQUAL( dcdtr0.capacity(), 1 )
   CHECK_EQUAL( strcmp(dcdtr0.c_str(), "a"), 0 )

   CHECK_EQUAL( dcdtr1.size(), 6 )
   CHECK_EQUAL( dcdtr1.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr1.c_str(), "abcdef"), 0)
DCD_TEST_END

//// string()
DCD_TEST_BEGIN(string_test_ctr_def)
   const string dcdtr{};

   CHECK_EQUAL( dcdtr.size(), 0 )
   CHECK_EQUAL( dcdtr.capacity(), 0 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), ""), 0)
DCD_TEST_END

//// const string(const char* str, const size_t n)
DCD_TEST_BEGIN(string_test_ctr_char_ptr)
   const char* str0{""};
   const char* str1{"abc"};
   const char* str2{"abcdef"};

   const string dcdtr0(str0, 0);
   const string dcdtr1(str1, 1);
   const string dcdtr2(str2, 6);

   CHECK_EQUAL( dcdtr0.size(), 0 )
   CHECK_EQUAL( dcdtr0.capacity(), 0 )
   CHECK_EQUAL( strcmp(dcdtr0.c_str(), ""), 0)

   CHECK_EQUAL( dcdtr1.size(), 1 )
   CHECK_EQUAL( dcdtr1.capacity(), 2 )
   CHECK_EQUAL( strcmp(dcdtr1.c_str(), "a"), 0)

   CHECK_EQUAL( dcdtr2.size(), 6 )
   CHECK_EQUAL( dcdtr2.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr2.c_str(), "abcdef"), 0)
DCD_TEST_END

//// string(const size_t n, const char c)
DCD_TEST_BEGIN(string_test_ctr_char_rep)
   const string dcdtr0(0, 'c');
   const string dcdtr1(1, 'c');
   const string dcdtr2(3, 'c');

   CHECK_EQUAL( dcdtr0.size(), 0 )
   CHECK_EQUAL( dcdtr0.capacity(), 0 )
   CHECK_EQUAL( strcmp(dcdtr0.c_str(), ""), 0)

   CHECK_EQUAL( dcdtr1.size(), 1 )
   CHECK_EQUAL( dcdtr1.capacity(), 2 )
   CHECK_EQUAL( strcmp(dcdtr1.c_str(), "c"), 0)

   CHECK_EQUAL( dcdtr2.size(), 3 )
   CHECK_EQUAL( dcdtr2.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr2.c_str(), "ccc"), 0)
DCD_TEST_END

//// string(const string& str, const size_t pos, const size_t n = string::npos)
DCD_TEST_BEGIN(string_test_ctr_str_sub)
   const string dcdtr{"abcdef"};
   const string dcdtr0_sub(dcdtr, 0, 0);
   const string dcdtr1_sub(dcdtr, 1, 0);
   const string dcdtr2_sub(dcdtr, 0, 1);
   const string dcdtr3_sub(dcdtr, 0, 3);
   const string dcdtr4_sub(dcdtr, 0, 8);
   const string dcdtr5_sub(dcdtr, 0, 7);
   const string dcdtr6_sub(dcdtr, 0, 6);
   const string dcdtr7_sub(dcdtr, 3, 3);
   const string dcdtr8_sub(dcdtr, 3, 2);

   CHECK_EQUAL( dcdtr0_sub.size(), 0 )
   CHECK_EQUAL( dcdtr0_sub.capacity(), 0 )
   CHECK_EQUAL( strcmp(dcdtr0_sub.c_str(), ""), 0)

   CHECK_EQUAL( dcdtr1_sub.size(), 0 )
   CHECK_EQUAL( dcdtr1_sub.capacity(), 0 )
   CHECK_EQUAL( strcmp(dcdtr1_sub.c_str(), ""), 0)

   CHECK_EQUAL( dcdtr2_sub.size(), 1 )
   CHECK_EQUAL( dcdtr2_sub.capacity(), 2 )
   CHECK_EQUAL( strcmp(dcdtr2_sub.c_str(), "a"), 0)

   CHECK_EQUAL( dcdtr3_sub.size(), 3 )
   CHECK_EQUAL( dcdtr3_sub.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr3_sub.c_str(), "abc"), 0)

   CHECK_EQUAL( dcdtr4_sub.size(), 6 )
   CHECK_EQUAL( dcdtr4_sub.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr4_sub.c_str(), "abcdef"), 0)

   CHECK_EQUAL( dcdtr5_sub.size(), 6 )
   CHECK_EQUAL( dcdtr5_sub.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr5_sub.c_str(), "abcdef"), 0)

   CHECK_EQUAL( dcdtr6_sub.size(), 6 )
   CHECK_EQUAL( dcdtr6_sub.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr6_sub.c_str(), "abcdef"), 0 )

   CHECK_EQUAL( dcdtr7_sub.size(), 3 )
   CHECK_EQUAL( dcdtr7_sub.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr7_sub.c_str(), "def"), 0 )

   CHECK_EQUAL( dcdtr8_sub.size(), 2 )
   CHECK_EQUAL( dcdtr8_sub.capacity(), 4 )
   CHECK_EQUAL( strcmp(dcdtr8_sub.c_str(), "de"), 0)
DCD_TEST_END

//// const string(const string& str)
DCD_TEST_BEGIN(string_test_ctr_cpy)
   const string dcdtr0{""};
   const string dcdtr1{"a"};
   const string dcdtr2{"abcdef"};
   const string dcdtr0_cpy{dcdtr0};
   const string dcdtr1_cpy{dcdtr1};
   const string dcdtr2_cpy{dcdtr2};

   CHECK_EQUAL( dcdtr0_cpy.size(), 0 )
   CHECK_EQUAL( dcdtr0_cpy.capacity(), 0 )
   CHECK_EQUAL( strcmp(dcdtr0_cpy.c_str(), ""), 0)

   CHECK_EQUAL( dcdtr1_cpy.size(), 1 )
   CHECK_EQUAL( dcdtr1_cpy.capacity(), 1 )
   CHECK_EQUAL( strcmp(dcdtr1_cpy.c_str(), "a"), 0)

   CHECK_EQUAL( dcdtr2_cpy.size(), 6 )
   CHECK_EQUAL( dcdtr2_cpy.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr2_cpy.c_str(), "abcdef"), 0)
DCD_TEST_END

DCD_TEST_BEGIN(string_test_op_pl)
   static string dcdtr0{""};
   dcdtr0 += "a";
   static string dcdtr1{"abc"};
   dcdtr1 += "def";
   static string dcdtr0_cpy{dcdtr0};
   static string dcdtr1_cpy{dcdtr1};

   CHECK_EQUAL( dcdtr0_cpy.size(), 1 )
   CHECK_EQUAL( dcdtr0_cpy.capacity(), 2 )
   CHECK_EQUAL( strcmp(dcdtr0_cpy.c_str(), "a"), 0)

   CHECK_EQUAL( dcdtr1_cpy.size(), 6 )
   CHECK_EQUAL( dcdtr1_cpy.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr1_cpy.c_str(), "abcdef"), 0)
DCD_TEST_END

//// const string(const string&& str)
DCD_TEST_BEGIN(string_test_ctr_mv)
   const string dcdtr0{""};
   const string dcdtr1{"a"};
   const string dcdtr2{"abcdef"};
   const string dcdtr0_mv{move(dcdtr0)};
   const string dcdtr1_mv{move(dcdtr1)};
   const string dcdtr2_mv{move(dcdtr2)};

   CHECK_EQUAL( dcdtr0_mv.size(), 0 )
   CHECK_EQUAL( dcdtr0_mv.capacity(), 0 )
   CHECK_EQUAL( strcmp(dcdtr0.c_str(), ""), 0)

   CHECK_EQUAL( dcdtr1_mv.size(), 1 )
   CHECK_EQUAL( dcdtr1_mv.capacity(), 1 )
   CHECK_EQUAL( strcmp(dcdtr1.c_str(), "a"), 0)

   CHECK_EQUAL( dcdtr2_mv.size(), 6 )
   CHECK_EQUAL( dcdtr2_mv.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr2.c_str(), "abcdef"), 0)
DCD_TEST_END

DCD_TEST_BEGIN(string_test_op_pl_ctr_mv)
   string dcdtr0{""};
   dcdtr0 += "a";
   string dcdtr1{"abc"};
   dcdtr1 += "def";
   string dcdtr0_cpy{move(dcdtr0)};
   string dcdtr1_cpy{move(dcdtr1)};

   CHECK_EQUAL( dcdtr0_cpy.size(), 1 )
   CHECK_EQUAL( dcdtr0_cpy.capacity(), 2 )
   CHECK_EQUAL( strcmp(dcdtr0_cpy.c_str(), "a"), 0)

   CHECK_EQUAL( dcdtr1_cpy.size(), 6 )
   CHECK_EQUAL( dcdtr1_cpy.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr1_cpy.c_str(), "abcdef"), 0)
DCD_TEST_END

//// string& operator=(const string& str);
DCD_TEST_BEGIN(string_test_op_asgn_1)
   const string dcdtr0{""};
   const string dcdtr1{"a"};
   const string dcdtr2{"abcdef"};
   string dcdtr0_cpy_assig{};
   string dcdtr1_cpy_assig{};
   string dcdtr2_cpy_assig{};
   dcdtr0_cpy_assig = dcdtr0;
   dcdtr1_cpy_assig = dcdtr1;
   dcdtr2_cpy_assig = dcdtr2;

   CHECK_EQUAL( dcdtr0_cpy_assig.size(), 0 )
   CHECK_EQUAL( dcdtr0_cpy_assig.capacity(), 0 )
   CHECK_EQUAL( strcmp(dcdtr0_cpy_assig.c_str(), ""), 0)

   CHECK_EQUAL( dcdtr1_cpy_assig.size(), 1 )
   CHECK_EQUAL( dcdtr1_cpy_assig.capacity(), 1 )
   CHECK_EQUAL( strcmp(dcdtr1_cpy_assig.c_str(), "a"), 0)

   CHECK_EQUAL( dcdtr2_cpy_assig.size(), 6 )
   CHECK_EQUAL( dcdtr2_cpy_assig.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr2_cpy_assig.c_str(), "abcdef"), 0)
DCD_TEST_END

DCD_TEST_BEGIN(string_test_op_pl_asgn)
   string dcdtr0{""};
   dcdtr0 += "a";
   string dcdtr1{"abc"};
   dcdtr1 += "def";
   string dcdtr0_cpy_assig{};
   string dcdtr1_cpy_assig{};
   dcdtr0_cpy_assig = dcdtr0;
   dcdtr1_cpy_assig = dcdtr1;

   CHECK_EQUAL( dcdtr0_cpy_assig.size(), 1 )
   CHECK_EQUAL( dcdtr0_cpy_assig.capacity(), 2 )
   CHECK_EQUAL( strcmp(dcdtr0_cpy_assig.c_str(), "a"), 0)

   CHECK_EQUAL( dcdtr1_cpy_assig.size(), 6 )
   CHECK_EQUAL( dcdtr1_cpy_assig.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr1_cpy_assig.c_str(), "abcdef"), 0)
DCD_TEST_END

//// string& operator=(string&& str)
DCD_TEST_BEGIN(string_test_mv_asgn)
   string dcdtr0{""};
   string dcdtr1{"a"};
   string dcdtr2{"abcdef"};
   string dcdtr0_mv_assig{};
   string dcdtr1_mv_assig{};
   string dcdtr2_mv_assig{};
   dcdtr0_mv_assig = move(dcdtr0);
   dcdtr1_mv_assig = move(dcdtr1);
   dcdtr2_mv_assig = move(dcdtr2);

   CHECK_EQUAL( dcdtr0_mv_assig.size(), 0 )
   CHECK_EQUAL( dcdtr0_mv_assig.capacity(), 0 )
   CHECK_EQUAL( strcmp(dcdtr0_mv_assig.c_str(), ""), 0)

   CHECK_EQUAL( dcdtr1_mv_assig.size(), 1 )
   CHECK_EQUAL( dcdtr1_mv_assig.capacity(), 1 )
   CHECK_EQUAL( strcmp(dcdtr1_mv_assig.c_str(), "a"), 0)

   CHECK_EQUAL( dcdtr2_mv_assig.size(), 6 )
   CHECK_EQUAL( dcdtr2_mv_assig.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr2_mv_assig.c_str(), "abcdef"), 0)
DCD_TEST_END

DCD_TEST_BEGIN(string_test_op_pl_mv)
   string dcdtr0{""};
   dcdtr0 += "a";
   string dcdtr1{"abc"};
   dcdtr1 += "def";
   string dcdtr0_mv_assig{};
   string dcdtr1_mv_assig{};
   dcdtr0_mv_assig = move(dcdtr0);
   dcdtr1_mv_assig = move(dcdtr1);

   CHECK_EQUAL( dcdtr0_mv_assig.size(), 1 )
   CHECK_EQUAL( dcdtr0_mv_assig.capacity(), 2 )
   CHECK_EQUAL( strcmp(dcdtr0_mv_assig.c_str(), "a"), 0)

   CHECK_EQUAL( dcdtr1_mv_assig.size(), 6 )
   CHECK_EQUAL( dcdtr1_mv_assig.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr1_mv_assig.c_str(), "abcdef"), 0)
DCD_TEST_END

//// string& operator=(const char* str)
DCD_TEST_BEGIN(string_test_op_asgn_2)
   string dcdtr{};
   dcdtr = "abcdef";

   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdef"), 0 )

   dcdtr = dcdtr;
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdef"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_op_asgn_pl)
   string dcdtr{};
   dcdtr = "";
   dcdtr += "abcdef";

   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdef"), 0 )

   dcdtr = dcdtr;
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdef"), 0 )
DCD_TEST_END

//// char& operator[](const size_t n)
DCD_TEST_BEGIN(string_test_char_eq)
   string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr[0], 'a' )
   CHECK_EQUAL( dcdtr[5], 'f' )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_char_eq_pl)
   string dcdtr{"abc"};
   dcdtr += "def";
   CHECK_EQUAL( dcdtr[0], 'a' )
   CHECK_EQUAL( dcdtr[5], 'f' )
DCD_TEST_END

//// const char& operator[](const size_t n) const
DCD_TEST_BEGIN(string_test_char_eq_ctr)
   const string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr[0], 'a' )
   CHECK_EQUAL( dcdtr[5], 'f' )
DCD_TEST_END

//// char& at(const size_t n)
DCD_TEST_BEGIN(string_test_char_eq_at_1)
   string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr.at(0), 'a' )
   CHECK_EQUAL( dcdtr.at(5), 'f' )

   CHECK_ASSERT( "dcd::string::at", [&]() {dcdtr.at(6);} )
DCD_TEST_END

//// const char& at(const size_t n) const
DCD_TEST_BEGIN(string_test_char_eq_at_2)
   const string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr.at(0), 'a' )
   CHECK_EQUAL( dcdtr.at(5), 'f' )

   CHECK_ASSERT( "dcd::string::at const", [&]() {dcdtr.at(6);} )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_char_eq_at_3)
   string dcdtr{""};
   dcdtr += "abcdef";
   const char c0{dcdtr.at(0)};
   const char c1{dcdtr.at(5)};
   CHECK_EQUAL( c0, 'a' )
   CHECK_EQUAL( c1, 'f' )
DCD_TEST_END

//// char& front()
DCD_TEST_BEGIN(string_test_front_1)
   const string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr.front(), 'a' )

   const string empty_str;
   CHECK_EQUAL( dcdtr.front(), 'a' )
DCD_TEST_END

//// const char& front() const
DCD_TEST_BEGIN(string_test_front_2)
   const string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr.front(), 'a' )
DCD_TEST_END

//// char& back()
DCD_TEST_BEGIN(string_test_back_1)
   const string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr.back(), 'f' )
DCD_TEST_END

//// const char& back() const
DCD_TEST_BEGIN(string_test_back_2)
   const string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr.back(), 'f' )
DCD_TEST_END

//// char* data()
DCD_TEST_BEGIN(string_test_data_1)
   string dcdtr{"abcdef"};
   CHECK_EQUAL( strcmp(dcdtr.data(), "abcdef"), 0 )

   dcdtr = "abc";
   CHECK_EQUAL( strcmp(dcdtr.data(), "abc"), 0 )
DCD_TEST_END

//// const char* data() const
DCD_TEST_BEGIN(string_test_data_2)
   const string dcdtr{"abcdef"};
   CHECK_EQUAL( strcmp(dcdtr.data(), "abcdef"), 0 )
DCD_TEST_END

//// const char* c_str() const
DCD_TEST_BEGIN(string_test_null_term_1)
   const string dcdtr{"abcdef"};
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdef"), 0 )
   CHECK_EQUAL( dcdtr.c_str()[dcdtr.size()], '\0' )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_null_term_2)
   string dcdtr{""};
   dcdtr += "abcdef";
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdef"), 0 )
   CHECK_EQUAL( dcdtr.c_str()[dcdtr.size()], '\0' )
DCD_TEST_END

//// char* begin()
DCD_TEST_BEGIN(string_test_iter_begin_1)
   string dcdtr{"abcdef"};
   char* iter{dcdtr.begin()};
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), iter), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_iter_begin_2)
   string dcdtr{""};
   dcdtr += "abcdef";
   char* iter{dcdtr.begin()};
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), iter), 0 )
DCD_TEST_END

//// const char* cbegin() const
DCD_TEST_BEGIN(string_test_iter_cbegin)
   string dcdtr{"abcdef"};
   const char* iter{dcdtr.cbegin()};
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), iter), 0 )
DCD_TEST_END

//// char* end()
DCD_TEST_BEGIN(string_test_iter_end_1)
   string dcdtr{"abcdef"};
   char* iter{dcdtr.end()};
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str()+dcdtr.size(), iter), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_iter_end_2)
   string dcdtr{""};
   dcdtr += "abcdef";
   char* iter{dcdtr.end()};
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str()+dcdtr.size(), iter), 0 )
DCD_TEST_END

//// const char* cend() const
DCD_TEST_BEGIN(string_test_iter_cend)
   string dcdtr{"abcdef"};
   const char* iter{dcdtr.cend()};
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.data()+dcdtr.size(), iter), 0 )
DCD_TEST_END

//// bool string::empty() const
DCD_TEST_BEGIN(string_test_empty)
   string dcdtr{};
   CHECK_EQUAL( dcdtr.empty(), true )
   dcdtr += 'c';
   CHECK_EQUAL( dcdtr.empty(), false )
DCD_TEST_END

//// size_t string::size() const
DCD_TEST_BEGIN(string_test_op_plus_char)
   string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr.size(), 6 )
   dcdtr += 'g';
   CHECK_EQUAL( dcdtr.size(), 7 )
DCD_TEST_END

//// size_t string::length() const
DCD_TEST_BEGIN(string_test_length)
   string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr.length(), 6 )
   dcdtr += 'g';
   CHECK_EQUAL( dcdtr.length(), 7 )
DCD_TEST_END

//// size_t string::capacity() const
DCD_TEST_BEGIN(string_test_capacity)
   string dcdtr{"abc"};
   CHECK_EQUAL( dcdtr.capacity(), 3 )
   dcdtr += 'd', dcdtr += 'e', dcdtr += 'f';
   CHECK_EQUAL( dcdtr.capacity(), 8 )
   dcdtr += 'g';
   CHECK_EQUAL( dcdtr.capacity(), 8 )
DCD_TEST_END

//// size_t string::max_size() const
DCD_TEST_BEGIN(string_test_max_size)
   const string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr.max_size(), string::npos )
DCD_TEST_END

//// void reserve(const size_t n)
DCD_TEST_BEGIN(string_test_reserve_1)
   string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   dcdtr.reserve(10);
   CHECK_EQUAL( dcdtr.capacity(), 10 )
   dcdtr.reserve(24);
   CHECK_EQUAL( dcdtr.capacity(), 24 )
   dcdtr.reserve(1);
   CHECK_EQUAL( dcdtr.capacity(), 24 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_reserve_2)
   string dcdtr{""};
   dcdtr += "abcdef";
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   dcdtr.reserve(10);
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   dcdtr.reserve(24);
   CHECK_EQUAL( dcdtr.capacity(), 24 )
   dcdtr.reserve(1);
   CHECK_EQUAL( dcdtr.capacity(), 24 )
DCD_TEST_END

//// void string::shrink_to_fit() const
DCD_TEST_BEGIN(string_test_shrink_to_fit)
   string dcdtr0{};
   string dcdtr1{"a"};
   string dcdtr2{"abcdef"};

   CHECK_EQUAL( dcdtr0.capacity(), 0 )
   dcdtr0.reserve(100);
   CHECK_EQUAL( dcdtr0.capacity(), 100 )
   dcdtr0.shrink_to_fit();
   CHECK_EQUAL( dcdtr0.capacity(), 0 )

   CHECK_EQUAL( dcdtr1.capacity(), 1 )
   dcdtr1.reserve(100);
   CHECK_EQUAL( dcdtr1.capacity(), 100 )
   dcdtr1.shrink_to_fit();
   CHECK_EQUAL( dcdtr1.capacity(), 1 )

   CHECK_EQUAL( dcdtr2.capacity(), 6 )
   dcdtr2.reserve(100);
   CHECK_EQUAL( dcdtr2.capacity(), 100 )
   dcdtr2.shrink_to_fit();
   CHECK_EQUAL( dcdtr2.capacity(), 6 )
DCD_TEST_END

//// void string::clear()
DCD_TEST_BEGIN(string_test_clear_1)
   string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr.empty(), false )
   dcdtr.clear();
   CHECK_EQUAL( dcdtr.empty(), true )
   CHECK_EQUAL( dcdtr.size(), 0 )
   CHECK_EQUAL( dcdtr.data()[0], '\0' )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_clear_2)
   string dcdtr{""};
   dcdtr += "abcdef";
   CHECK_EQUAL( dcdtr.empty(), false )
   dcdtr.clear();
   CHECK_EQUAL( dcdtr.empty(), true )
   CHECK_EQUAL( dcdtr.size(), 0 )
   CHECK_EQUAL( dcdtr.data()[0], '\0' )
DCD_TEST_END

//// void resize(size_t n)
DCD_TEST_BEGIN(string_test_resize_1)
   string dcdtr{"abcdef"};

   dcdtr.resize(3);
   CHECK_EQUAL( dcdtr.size(), 3 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abc"), 0 )

   dcdtr.resize(5);
   CHECK_EQUAL( dcdtr.size(), 5 )
   CHECK_EQUAL( dcdtr.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abc"), 0 )

   dcdtr.resize(13);
   CHECK_EQUAL( dcdtr.size(), 13 )
   CHECK_EQUAL( dcdtr.capacity(), 26 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abc"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_resize_2)
   string dcdtr{""};
   dcdtr += "abcdef";

   dcdtr.resize(3);
   CHECK_EQUAL( dcdtr.size(), 3 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abc"), 0 )

   dcdtr.resize(5);
   CHECK_EQUAL( dcdtr.size(), 5 )
   CHECK_EQUAL( dcdtr.capacity(), 12 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abc"), 0 )

   dcdtr.resize(13);
   CHECK_EQUAL( dcdtr.size(), 13 )
   CHECK_EQUAL( dcdtr.capacity(), 26 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abc"), 0 )
DCD_TEST_END

//// void swap(string& str)
DCD_TEST_BEGIN(string_test_swap)
   string dcdtr_swap0{"abc"};
   string dcdtr_swap1{"123456"};

   dcdtr_swap0.swap(dcdtr_swap1);

   CHECK_EQUAL( dcdtr_swap0.size(), 6 )
   CHECK_EQUAL( dcdtr_swap0.capacity(), 6 )
   CHECK_EQUAL( strcmp(dcdtr_swap0.c_str(), "123456"), 0 )

   CHECK_EQUAL( dcdtr_swap1.size(), 3 )
   CHECK_EQUAL( dcdtr_swap1.capacity(), 3 )
   CHECK_EQUAL( strcmp(dcdtr_swap1.c_str(), "abc"), 0 )
DCD_TEST_END

//// void push_back(char c)
DCD_TEST_BEGIN(string_test_push_back)
   string dcdtr{"abcdef"};
   CHECK_EQUAL( dcdtr.size(), 6 )
   dcdtr.push_back('g');
   CHECK_EQUAL( dcdtr.size(), 7 )
   CHECK_EQUAL( dcdtr.capacity(), 14 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdefg"), 0 )
DCD_TEST_END

//// void pop_back()
DCD_TEST_BEGIN(string_test_pop_back_1)
   string dcdtr{"abcdefg"};
   CHECK_EQUAL( dcdtr.size(), 7 )
   dcdtr.pop_back();
   CHECK_EQUAL( dcdtr.size(), 6 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "abcdef"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_pop_back_2)
   string dcdtr{"abc"};
   CHECK_EQUAL( dcdtr.size(), 3 )
   dcdtr.pop_back();
   dcdtr.pop_back();
   dcdtr.pop_back();
   CHECK_EQUAL( dcdtr.size(), 0 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), ""), 0 )

   dcdtr.pop_back();
   CHECK_EQUAL( dcdtr.size(), 0 )
   CHECK_EQUAL( strcmp(dcdtr.c_str(), ""), 0 )
DCD_TEST_END

//// string substr(size_t pos = 0, size_t len = npos) const
DCD_TEST_BEGIN(string_test_substr_1)
   static const string dcdtr{"abcdef"};
   CHECK_EQUAL( strcmp(dcdtr.substr(0).c_str(), "abcdef"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,0).c_str(), ""), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,1).c_str(), "a"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,2).c_str(), "ab"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,3).c_str(), "abc"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,4).c_str(), "abcd"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,5).c_str(), "abcde"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,6).c_str(), "abcdef"), 0 )

   CHECK_EQUAL( strcmp(dcdtr.substr(1,0).c_str(), ""), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(1,1).c_str(), "b"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(1,2).c_str(), "bc"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(1,3).c_str(), "bcd"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(1,4).c_str(), "bcde"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(1,5).c_str(), "bcdef"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(1,6).c_str(), "bcdef"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_substr_2)
   string dcdtr{""};
   dcdtr += "abcdef";
   CHECK_EQUAL( strcmp(dcdtr.substr(0).c_str(), "abcdef"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,0).c_str(), ""), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,1).c_str(), "a"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,2).c_str(), "ab"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,3).c_str(), "abc"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,4).c_str(), "abcd"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,5).c_str(), "abcde"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(0,6).c_str(), "abcdef"), 0 )

   CHECK_EQUAL( strcmp(dcdtr.substr(1,0).c_str(), ""), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(1,1).c_str(), "b"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(1,2).c_str(), "bc"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(1,3).c_str(), "bcd"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(1,4).c_str(), "bcde"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(1,5).c_str(), "bcdef"), 0 )
   CHECK_EQUAL( strcmp(dcdtr.substr(1,6).c_str(), "bcdef"), 0 )
DCD_TEST_END

//// size_t copy(char* dest, size_t len, size_t pos = 0) const
DCD_TEST_BEGIN(string_test_copy_1)
   const string dcdtr{"abcdef"};
   char str[7]{};

   CHECK_EQUAL( dcdtr.copy(str, 0), 0 )
   CHECK_EQUAL( strcmp(str, ""), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10), 6 )
   CHECK_EQUAL( strcmp(str, "abcdef"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 0), 6 )
   CHECK_EQUAL( strcmp(str, "abcdef"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 1), 5 )
   CHECK_EQUAL( strcmp(str, "bcdef"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 2), 4 )
   CHECK_EQUAL( strcmp(str, "cdef"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 3), 3 )
   CHECK_EQUAL( strcmp(str, "def"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 4), 2 )
   CHECK_EQUAL( strcmp(str, "ef"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 5), 1 )
   CHECK_EQUAL( strcmp(str, "f"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 6), 0 )
   CHECK_EQUAL( strcmp(str, ""), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_copy_2)
   string dcdtr{""};
   dcdtr += "abcdef";
   char str[7]{};

   CHECK_EQUAL( dcdtr.copy(str, 0), 0 )
   CHECK_EQUAL( strcmp(str, ""), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10), 6 )
   CHECK_EQUAL( strcmp(str, "abcdef"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 0), 6 )
   CHECK_EQUAL( strcmp(str, "abcdef"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 1), 5 )
   CHECK_EQUAL( strcmp(str, "bcdef"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 2), 4 )
   CHECK_EQUAL( strcmp(str, "cdef"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 3), 3 )
   CHECK_EQUAL( strcmp(str, "def"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 4), 2 )
   CHECK_EQUAL( strcmp(str, "ef"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 5), 1 )
   CHECK_EQUAL( strcmp(str, "f"), 0 )

   CHECK_EQUAL( dcdtr.copy(str, 10, 6), 0 )
   CHECK_EQUAL( strcmp(str, ""), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_copy_3)
   const string dcdtr{"abcdef"};
   char str[7]{};
   CHECK_ASSERT( "dcd::string::copy", [&]() {dcdtr.copy(str, 1, dcdtr.size()+1);} )
DCD_TEST_END

//// string& insert(const size_t pos, const char* str)
DCD_TEST_BEGIN(string_test_ins_1)
   string dcdtr{"iii"};
   const char* str{"ooo"};
   dcdtr.insert(0, str);
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "oooiii"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_2)
   string dcdtr{"iii"};
   const char* str{"ooo"};
   dcdtr.insert(1, str);
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "ioooii"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_3)
   string dcdtr{"iii"};
   const char* str{"ooo"};
   dcdtr.insert(2, str);
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "iioooi"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_4)
   string dcdtr{"iii"};
   const char* str{"ooo"};
   dcdtr.insert(3, str);
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "iiiooo"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_5)
   string dcdtr{""};
   dcdtr += "iii";
   const char* str{"ooo"};
   dcdtr.insert(0, str);
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "oooiii"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_6)
   string dcdtr{""};
   dcdtr += "iii";
   const char* str{"ooo"};
   dcdtr.insert(1, str);
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "ioooii"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_7)
   string dcdtr{""};
   dcdtr += "iii";
   const char* str{"ooo"};
   dcdtr.insert(2, str);
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "iioooi"), 0 )
DCD_TEST_END

DCD_TEST_BEGIN(string_test_ins_8)
   string dcdtr{""};
   dcdtr += "iii";
   const char* str{"ooo"};
   dcdtr.insert(3, str);
   CHECK_EQUAL( strcmp(dcdtr.c_str(), "iiiooo"), 0 )
DCD_TEST_END

int main(int argc, char* argv[]) {
   bool verbose = false;
   if( argc >= 2 && std::strcmp( argv[1], "-v" ) == 0 ) {
      verbose = true;
   }
   silence_output(!verbose);

   DCD_TEST(string_test_ctr_lit)
   DCD_TEST(string_test_ctr_def)
   DCD_TEST(string_test_ctr_char_ptr)
   DCD_TEST(string_test_ctr_char_rep)
   DCD_TEST(string_test_ctr_str_sub)
   DCD_TEST(string_test_ctr_cpy)
   DCD_TEST(string_test_op_pl)
   DCD_TEST(string_test_ctr_mv)
   DCD_TEST(string_test_op_pl_ctr_mv)
   DCD_TEST(string_test_op_asgn_1)
   DCD_TEST(string_test_op_pl_asgn)
   DCD_TEST(string_test_mv_asgn)
   DCD_TEST(string_test_op_pl_mv)
   DCD_TEST(string_test_op_asgn_2)
   DCD_TEST(string_test_op_asgn_pl)
   DCD_TEST(string_test_char_eq)
   DCD_TEST(string_test_char_eq_pl)
   DCD_TEST(string_test_char_eq_ctr)
   DCD_TEST(string_test_char_eq_at_1)
   DCD_TEST(string_test_char_eq_at_2)
   DCD_TEST(string_test_char_eq_at_3)
   DCD_TEST(string_test_front_1)
   DCD_TEST(string_test_front_2)
   DCD_TEST(string_test_back_1)
   DCD_TEST(string_test_back_2)
   DCD_TEST(string_test_data_1)
   DCD_TEST(string_test_data_2)
   DCD_TEST(string_test_null_term_1)
   DCD_TEST(string_test_null_term_2)
   DCD_TEST(string_test_iter_begin_1)
   DCD_TEST(string_test_iter_begin_2)
   DCD_TEST(string_test_iter_cbegin)
   DCD_TEST(string_test_iter_end_1)
   DCD_TEST(string_test_iter_end_2)
   DCD_TEST(string_test_iter_cend)
   DCD_TEST(string_test_empty)
   DCD_TEST(string_test_op_plus_char)
   DCD_TEST(string_test_length)
   DCD_TEST(string_test_capacity)
   DCD_TEST(string_test_max_size)
   DCD_TEST(string_test_reserve_1)
   DCD_TEST(string_test_reserve_2)
   DCD_TEST(string_test_shrink_to_fit)
   DCD_TEST(string_test_clear_1)
   DCD_TEST(string_test_clear_2)
   DCD_TEST(string_test_resize_1)
   DCD_TEST(string_test_resize_2)
   DCD_TEST(string_test_swap)
   DCD_TEST(string_test_push_back)
   DCD_TEST(string_test_pop_back_1)
   DCD_TEST(string_test_pop_back_2)
   DCD_TEST(string_test_substr_1)
   DCD_TEST(string_test_substr_2)
   DCD_TEST(string_test_copy_1)
   DCD_TEST(string_test_copy_2)
   DCD_TEST(string_test_copy_3)
   DCD_TEST(string_test_ins_1)
   DCD_TEST(string_test_ins_2)
   DCD_TEST(string_test_ins_3)
   DCD_TEST(string_test_ins_4)
   DCD_TEST(string_test_ins_5)
   DCD_TEST(string_test_ins_6)
   DCD_TEST(string_test_ins_7)
   DCD_TEST(string_test_ins_8)

   return has_failed();
}
