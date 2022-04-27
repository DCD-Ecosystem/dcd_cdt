// Verifies that the dispatching code is self-contained

class [[dcd::contract]] minimal_tests {
 public:
   template<typename N, typename DS>
   explicit constexpr minimal_tests(const N&, const N&, const DS&) {}
   [[dcd::action]] void test1() {}
};
