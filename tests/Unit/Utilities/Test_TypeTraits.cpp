// Distributed under the MIT License.
// See LICENSE.txt for details.

#include <catch.hpp>

#include "Utilities/TypeTraits.hpp"

namespace {

/// \cond HIDDEN_SYMBOLS
class A {
 public:
  int operator()() { return 1; }
  A() = delete;
  std::unique_ptr<double> get_clone() const {
    return std::make_unique<double>();
  }
  int size() const { return 2; }
};
}  // namespace

class BClassInTestTypeTraits {
 public:
  double operator()(const int /* unused */, const double /* unused */) {
    return 0.;
  }
  std::unique_ptr<double> clone() const { return std::make_unique<double>(); }
};

class CClassInTestTypeTraits {};

class D;

namespace std {
template <>
struct hash<A> {
  size_t operator()(const A& /* a */) const { return 1; }
};
}  // namespace std

std::ostream& operator<<(std::ostream& os, const D&);

bool operator==(const CClassInTestTypeTraits&, const CClassInTestTypeTraits&);

bool operator!=(const CClassInTestTypeTraits&, const CClassInTestTypeTraits&);
/// \endcond

/// [conjunction_example]
static_assert(
    cpp17::conjunction<std::true_type, std::true_type, std::true_type>::value,
    "Failed testing type trait conjunction");
static_assert(not cpp17::conjunction<std::true_type, std::false_type,
                                     std::true_type>::value,
              "Failed testing type trait conjunction");
static_assert(not cpp17::conjunction<std::true_type, std::false_type>::value,
              "Failed testing type trait conjunction");
static_assert(not cpp17::conjunction<std::false_type, std::true_type>::value,
              "Failed testing type trait conjunction");
/// [conjunction_example]

/// [disjunction_example]
static_assert(not cpp17::disjunction<std::false_type, std::false_type,
                                     std::false_type>::value,
              "Failed testing type trait disjunction");
static_assert(
    cpp17::disjunction<std::false_type, std::true_type, std::false_type>::value,
    "Failed testing type trait disjunction");
static_assert(cpp17::disjunction<std::true_type, std::false_type>::value,
              "Failed testing type trait disjunction");
static_assert(cpp17::disjunction<std::false_type, std::true_type>::value,
              "Failed testing type trait disjunction");
/// [disjunction_example]

/// [negation_example]
static_assert(
    std::is_same<
        cpp17::bool_constant<false>,
        typename cpp17::negation<cpp17::bool_constant<true>>::type>::value,
    "Failed testing type trait negate");
static_assert(
    std::is_same<
        cpp17::bool_constant<true>,
        typename cpp17::negation<cpp17::bool_constant<false>>::type>::value,
    "Failed testing type trait negate");
static_assert(not cpp17::negation<cpp17::bool_constant<true>>::value,
              "Failed testing type trait negate");
static_assert(cpp17::negation<cpp17::bool_constant<false>>::value,
              "Failed testing type trait negate");
/// [negation_example]

/// [void_t_example]
static_assert(std::is_same<cpp17::void_t<char, bool, double>, void>::value,
              "Failed testing type trait void_t");
/// [void_t_example]

/// [is_std_array_example]
static_assert(tt::is_std_array<std::array<double, 3>>::value,
              "Failed testing type trait is_std_array");
static_assert(tt::is_std_array_t<std::array<double, 3>>::value,
              "Failed testing type trait is_std_array");
static_assert(tt::is_std_array_v<std::array<double, 3>>,
              "Failed testing type trait is_std_array");
static_assert(not tt::is_std_array<double>::value,
              "Failed testing type trait is_std_array");
static_assert(tt::is_std_array<std::array<D, 10>>::value,
              "Failed testing type trait is_std_array");
/// [is_std_array_example]

/// [is_std_array_of_size_example]
static_assert(tt::is_std_array_of_size<3, std::array<double, 3>>::value,
              "Failed testing type trait is_std_array_of_size");
static_assert(tt::is_std_array_of_size_t<3, std::array<double, 3>>::value,
              "Failed testing type trait is_std_array_of_size");
static_assert(tt::is_std_array_of_size_v<3, std::array<double, 3>>,
              "Failed testing type trait is_std_array_of_size");
static_assert(not tt::is_std_array_of_size<3, double>::value,
              "Failed testing type trait is_std_array_of_size");
static_assert(not tt::is_std_array_of_size<2, std::array<double, 3>>::value,
              "Failed testing type trait is_std_array_of_size");
static_assert(tt::is_std_array_of_size<10, std::array<D, 10>>::value,
              "Failed testing type trait is_std_array_of_size");
/// [is_std_array_of_size_example]

/// [is_a_example]
static_assert(tt::is_a<std::vector, std::vector<double>>::value,
              "Failed testing type trait is_a<vector>");
static_assert(not tt::is_a_t<std::vector, double>::value,
              "Failed testing type trait is_a<vector>");
static_assert(tt::is_a_v<std::vector, std::vector<D>>,
              "Failed testing type trait is_a<vector>");

static_assert(tt::is_a<std::deque, std::deque<double>>::value,
              "Failed testing type trait is_a<deque>");
static_assert(not tt::is_a<std::deque, double>::value,
              "Failed testing type trait is_a<deque>");
static_assert(tt::is_a<std::deque, std::deque<D>>::value,
              "Failed testing type trait is_a<deque>");

static_assert(tt::is_a<std::forward_list, std::forward_list<double>>::value,
              "Failed testing type trait is_a<forward_list>");
static_assert(not tt::is_a<std::forward_list, double>::value,
              "Failed testing type trait is_a<forward_list>");
static_assert(tt::is_a<std::forward_list, std::forward_list<D>>::value,
              "Failed testing type trait is_a<forward_list>");

static_assert(tt::is_a<std::list, std::list<double>>::value,
              "Failed testing type trait is_a<list>");
static_assert(not tt::is_a<std::list, double>::value,
              "Failed testing type trait is_a<list>");
static_assert(tt::is_a<std::list, std::list<D>>::value,
              "Failed testing type trait is_a<list>");

static_assert(tt::is_a<std::map, std::map<std::string, double>>::value,
              "Failed testing type trait is_a<map>");
static_assert(not tt::is_a<std::map, double>::value,
              "Failed testing type trait is_a<map>");
static_assert(tt::is_a<std::map, std::map<std::string, D>>::value,
              "Failed testing type trait is_a<map>");

static_assert(tt::is_a<std::unordered_map,
                       std::unordered_map<std::string, double>>::value,
              "Failed testing type trait is_a<unordered_map>");
static_assert(not tt::is_a<std::unordered_map, double>::value,
              "Failed testing type trait is_a<unordered_map>");
static_assert(
    tt::is_a<std::unordered_map, std::unordered_map<std::string, D>>::value,
    "Failed testing type trait is_a<unordered_map>");

static_assert(tt::is_a<std::set, std::set<double>>::value,
              "Failed testing type trait is_a<set>");
static_assert(not tt::is_a<std::set, double>::value,
              "Failed testing type trait is_a<set>");
static_assert(tt::is_a<std::set, std::set<D>>::value,
              "Failed testing type trait is_a<set>");

static_assert(tt::is_a<std::unordered_set, std::unordered_set<double>>::value,
              "Failed testing type trait is_a<unordered_set>");
static_assert(not tt::is_a<std::unordered_set, double>::value,
              "Failed testing type trait is_a<unordered_set>");
static_assert(tt::is_a<std::unordered_set, std::unordered_set<D>>::value,
              "Failed testing type trait is_a<unordered_set>");

static_assert(tt::is_a<std::multiset, std::multiset<double>>::value,
              "Failed testing type trait is_a<multiset>");
static_assert(not tt::is_a<std::multiset, double>::value,
              "Failed testing type trait is_a<multiset>");
static_assert(tt::is_a<std::multiset, std::multiset<D>>::value,
              "Failed testing type trait is_a<multiset>");

static_assert(
    tt::is_a<std::unordered_multiset, std::unordered_multiset<double>>::value,
    "Failed testing type trait is_a<unordered_multiset>");
static_assert(not tt::is_a<std::unordered_multiset, double>::value,
              "Failed testing type trait is_a<unordered_multiset>");
static_assert(
    tt::is_a<std::unordered_multiset, std::unordered_multiset<D>>::value,
    "Failed testing type trait is_a<unordered_multiset>");

static_assert(
    tt::is_a<std::multimap, std::multimap<std::string, double>>::value,
    "Failed testing type trait is_a<multimap>");
static_assert(not tt::is_a<std::multimap, double>::value,
              "Failed testing type trait is_a<multimap>");
static_assert(tt::is_a<std::multimap, std::multimap<std::string, D>>::value,
              "Failed testing type trait is_a<multimap>");

static_assert(tt::is_a<std::unordered_multimap,
                       std::unordered_multimap<std::string, double>>::value,
              "Failed testing type trait is_a<unordered_multimap>");
static_assert(not tt::is_a<std::unordered_multimap, double>::value,
              "Failed testing type trait is_a<unordered_multimap>");
static_assert(tt::is_a<std::unordered_multimap,
                       std::unordered_multimap<std::string, D>>::value,
              "Failed testing type trait is_a<unordered_multimap>");

static_assert(tt::is_a<std::priority_queue, std::priority_queue<double>>::value,
              "Failed testing type trait is_a<priority_queue>");
static_assert(not tt::is_a<std::priority_queue, double>::value,
              "Failed testing type trait is_a<priority_queue>");
static_assert(tt::is_a<std::priority_queue, std::priority_queue<D>>::value,
              "Failed testing type trait is_a<priority_queue>");

static_assert(tt::is_a<std::queue, std::queue<double>>::value,
              "Failed testing type trait is_a<queue>");
static_assert(not tt::is_a<std::queue, double>::value,
              "Failed testing type trait is_a<queue>");
static_assert(tt::is_a<std::queue, std::queue<D>>::value,
              "Failed testing type trait is_a<queue>");

static_assert(tt::is_a<std::stack, std::stack<double>>::value,
              "Failed testing type trait is_a<stack>");
static_assert(not tt::is_a<std::stack, double>::value,
              "Failed testing type trait is_a<stack>");
static_assert(tt::is_a<std::stack, std::stack<D>>::value,
              "Failed testing type trait is_a<stack>");

static_assert(tt::is_a<std::unique_ptr, std::unique_ptr<double>>::value,
              "Failed testing type trait is_a<unique_ptr>");
static_assert(
    tt::is_a<std::unique_ptr, std::unique_ptr<CClassInTestTypeTraits>>::value,
    "Failed testing type trait is_a<unique_ptr>");
static_assert(not tt::is_a<std::unique_ptr, std::shared_ptr<double>>::value,
              "Failed testing type trait is_a<unique_ptr>");
static_assert(not tt::is_a<std::unique_ptr, CClassInTestTypeTraits>::value,
              "Failed testing type trait is_a<unique_ptr>");

static_assert(tt::is_a<std::shared_ptr, std::shared_ptr<double>>::value,
              "Failed testing type trait is_a<shared_ptr>");
static_assert(
    tt::is_a<std::shared_ptr, std::shared_ptr<CClassInTestTypeTraits>>::value,
    "Failed testing type trait is_a<shared_ptr>");
static_assert(not tt::is_a<std::shared_ptr, std::unique_ptr<double>>::value,
              "Failed testing type trait is_a<shared_ptr>");
static_assert(not tt::is_a<std::shared_future, CClassInTestTypeTraits>::value,
              "Failed testing type trait is_a<shared_ptr>");

static_assert(tt::is_a<std::weak_ptr, std::weak_ptr<double>>::value,
              "Failed testing type trait is_a<weak_ptr>");
static_assert(
    tt::is_a<std::weak_ptr, std::weak_ptr<CClassInTestTypeTraits>>::value,
    "Failed testing type trait is_a<weak_ptr>");
static_assert(not tt::is_a<std::weak_ptr, std::unique_ptr<double>>::value,
              "Failed testing type trait is_a<weak_ptr>");
static_assert(not tt::is_a<std::weak_ptr, CClassInTestTypeTraits>::value,
              "Failed testing type trait is_a<weak_ptr>");

static_assert(tt::is_a<std::tuple, std::tuple<int, double, A>>::value,
              "Failed testing type trait is_a");
static_assert(tt::is_a<std::vector, std::vector<A>>::value,
              "Failed testing type trait is_a");

static_assert(tt::is_a<std::future, std::future<double>>::value,
              "Failed testing type trait is_a<future>");
static_assert(tt::is_a<std::future, std::future<std::vector<double>>>::value,
              "Failed testing type trait is_a<future>");
static_assert(not tt::is_a<std::future, std::shared_future<double>>::value,
              "Failed testing type trait is_a<future>");

static_assert(tt::is_a<std::shared_future, std::shared_future<double>>::value,
              "Failed testing type trait is_a<shared_future>");
static_assert(tt::is_a<std::shared_future,
                       std::shared_future<std::vector<double>>>::value,
              "Failed testing type trait is_a<shared_future>");
static_assert(not tt::is_a<std::shared_future, std::future<double>>::value,
              "Failed testing type trait is_a<shared_future>");
/// [is_a_example]

/// [is_iterable_example]
static_assert(tt::is_iterable<std::vector<double>>::value,
              "Failed testing type trait is_iterable");
static_assert(tt::is_iterable_t<std::vector<double>>::value,
              "Failed testing type trait is_iterable");
static_assert(tt::is_iterable_v<std::vector<double>>,
              "Failed testing type trait is_iterable");
static_assert(not tt::is_iterable<double>::value,
              "Failed testing type trait is_iterable");
/// [is_iterable_example]

/// [is_comparable_example]
static_assert(tt::is_comparable<std::vector<double>>::value,
              "Failed testing type trait is_comparable");
static_assert(tt::is_comparable_t<std::vector<double>>::value,
              "Failed testing type trait is_comparable");
static_assert(tt::is_comparable_v<std::vector<double>>,
              "Failed testing type trait is_comparable");
static_assert(tt::is_comparable<double>::value,
              "Failed testing type trait is_comparable");
static_assert(not tt::is_comparable<A>::value,
              "Failed testing type trait is_comparable");
/// [is_comparable_example]

/// [array_size_example]
static_assert(tt::array_size<std::array<double, 3>>::value == 3,
              "Failed testing type trait array_size");
static_assert(tt::array_size<std::array<A, 4>>::value == 4,
              "Failed testing type trait array_size");
/// [array_size_example]

/// [has_equivalence_example]
static_assert(not tt::has_equivalence<A>::value,
              "Failed testing type trait has_equivalence");
static_assert(tt::has_equivalence<CClassInTestTypeTraits>::value,
              "Failed testing type trait has_equivalence");
static_assert(tt::has_equivalence_t<CClassInTestTypeTraits>::value,
              "Failed testing type trait has_equivalence");
static_assert(tt::has_equivalence_v<CClassInTestTypeTraits>,
              "Failed testing type trait has_equivalence");
/// [has_equivalence_example]

/// [has_inequivalence_example]
static_assert(not tt::has_inequivalence<A>::value,
              "Failed testing type trait has_inequivalence");
static_assert(tt::has_inequivalence<CClassInTestTypeTraits>::value,
              "Failed testing type trait has_inequivalence");
static_assert(tt::has_inequivalence_t<CClassInTestTypeTraits>::value,
              "Failed testing type trait has_inequivalence");
static_assert(tt::has_inequivalence_v<CClassInTestTypeTraits>,
              "Failed testing type trait has_inequivalence");
/// [has_inequivalence_example]

/// [is_callable_example]
static_assert(not tt::is_callable<A, int, double>::value,
              "Failed testing type trait is_callable");
static_assert(not tt::is_callable<A, int>::value,
              "Failed testing type trait is_callable");
static_assert(tt::is_callable<A>::value,
              "Failed testing type trait is_callable");
static_assert(tt::is_callable<BClassInTestTypeTraits, int, double>::value,
              "Failed testing type trait is_callable");
static_assert(tt::is_callable_t<BClassInTestTypeTraits, int, double>::value,
              "Failed testing type trait is_callable");
static_assert(tt::is_callable_v<BClassInTestTypeTraits, int, double>,
              "Failed testing type trait is_callable");
static_assert(not tt::is_callable<BClassInTestTypeTraits>::value,
              "Failed testing type trait is_callable");
/// [is_callable_example]

namespace  {
/// [CREATE_IS_CALLABLE_EXAMPLE]
CREATE_IS_CALLABLE(foo)
CREATE_IS_CALLABLE(foobar)
struct bar {
  void foo(int /*unused*/, double /*unused*/) {}
};

static_assert(is_foo_callable_v<bar, int, double>,
              "Failed testing CREATE_IS_CALLABLE");
static_assert(not is_foo_callable_v<bar, int>,
              "Failed testing CREATE_IS_CALLABLE");
static_assert(not is_foo_callable_v<bar>,
              "Failed testing CREATE_IS_CALLABLE");
static_assert(not is_foobar_callable_v<bar, int, double>,
              "Failed testing CREATE_IS_CALLABLE");
/// [CREATE_IS_CALLABLE_EXAMPLE]
}  // namespace

/// [is_hashable_example]
static_assert(tt::is_hashable<double>::value,
              "Failed testing type trait is_hashable");
static_assert(tt::is_hashable_t<double>::value,
              "Failed testing type trait is_hashable");
static_assert(tt::is_hashable_v<double>,
              "Failed testing type trait is_hashable");
static_assert(tt::is_hashable<A>::value,
              "Failed testing type trait is_hashable");
// There is a bug in libc++ prior to version 4.0.0 that uses static_assert
// in the std::hash for enum instead of using something like enable_if
#if (defined(_LIBCPP_VERSION) && _LIBCPP_VERSION >= 4000) || \
    !(defined(_LIBCPP_VERSION))
static_assert(not tt::is_hashable<std::vector<std::unique_ptr<double>>>::value,
              "Failed testing type trait is_hashable");
#endif
/// [is_hashable_example]

/// [is_maplike_example]
static_assert(tt::is_maplike<std::unordered_map<int, double>>::value,
              "Failed testing type trait is_maplike");
static_assert(tt::is_maplike_t<std::unordered_map<int, double>>::value,
              "Failed testing type trait is_maplike");
static_assert(tt::is_maplike_v<std::unordered_map<int, double>>,
              "Failed testing type trait is_maplike");
static_assert(tt::is_maplike<std::map<int, CClassInTestTypeTraits>>::value,
              "Failed testing type trait is_maplike");
static_assert(not tt::is_maplike<std::vector<CClassInTestTypeTraits>>::value,
              "Failed testing type trait is_maplike");
static_assert(not tt::is_maplike<D>::value,
              "Failed testing type trait is_maplike");
/// [is_maplike_example]

/// [is_streamable_example]
static_assert(
    not tt::is_streamable<std::ostream, CClassInTestTypeTraits>::value,
    "Failed testing type trait is_streamable");
static_assert(
    not tt::is_streamable_t<std::ostream, CClassInTestTypeTraits>::value,
    "Failed testing type trait is_streamable");
static_assert(not tt::is_streamable_v<std::ostream, CClassInTestTypeTraits>,
              "Failed testing type trait is_streamable");
static_assert(not tt::is_streamable<std::ostream, A>::value,
              "Failed testing type trait is_streamable");
static_assert(tt::is_streamable<std::ostream, D>::value,
              "Failed testing type trait is_streamable");
/// [is_streamable_example]

/// [is_string_like_example]
static_assert(tt::is_string_like<std::string>::value,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like_t<std::string>::value,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like_v<std::string>,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like<std::string&>::value,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like<const std::string&>::value,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like<std::string&&>::value,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like<char*>::value,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like<const char*>::value,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like<char* const>::value,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like<const char* const>::value,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like<char>::value,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like<const char>::value,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like<char&&>::value,
              "Failed testing type trait is_string_like");
static_assert(tt::is_string_like<char&>::value,
              "Failed testing type trait is_string_like");
static_assert(not tt::is_string_like<int&>::value,
              "Failed testing type trait is_string_like");
static_assert(not tt::is_string_like<short&>::value,
              "Failed testing type trait is_string_like");
static_assert(not tt::is_string_like<int>::value,
              "Failed testing type trait is_string_like");
static_assert(not tt::is_string_like<short>::value,
              "Failed testing type trait is_string_like");
/// [is_string_like_example]

/// [has_get_clone_example]
static_assert(tt::has_get_clone<std::unique_ptr<A>>::value,
              "Failed testing type trait has_get_clone");
static_assert(tt::has_get_clone_t<std::unique_ptr<A>>::value,
              "Failed testing type trait has_get_clone");
static_assert(tt::has_get_clone_v<std::unique_ptr<A>>,
              "Failed testing type trait has_get_clone");
static_assert(tt::has_get_clone<A>::value,
              "Failed testing type trait has_get_clone");
static_assert(
    not tt::has_get_clone<std::unique_ptr<BClassInTestTypeTraits>>::value,
    "Failed testing type trait has_get_clone");
static_assert(not tt::has_get_clone<double>::value,
              "Failed testing type trait has_get_clone");
/// [has_get_clone_example]

/// [has_clone_example]
static_assert(tt::has_clone<BClassInTestTypeTraits>::value,
              "Failed testing type trait has_clone");
static_assert(tt::has_clone_t<BClassInTestTypeTraits>::value,
              "Failed testing type trait has_clone");
static_assert(tt::has_clone_v<BClassInTestTypeTraits>,
              "Failed testing type trait has_clone");
static_assert(tt::has_clone<std::unique_ptr<BClassInTestTypeTraits>>::value,
              "Failed testing type trait has_clone");
static_assert(not tt::has_clone<std::unique_ptr<A>>::value,
              "Failed testing type trait has_clone");
static_assert(not tt::has_clone<double>::value,
              "Failed testing type trait has_clone");
/// [has_clone_example]

/// [has_size_example]
static_assert(tt::has_size<A>::value, "Failed testing type trait has_size");
static_assert(tt::has_size_t<A>::value, "Failed testing type trait has_size");
static_assert(tt::has_size_v<A>, "Failed testing type trait has_size");
static_assert(tt::has_size<std::vector<BClassInTestTypeTraits>>::value,
              "Failed testing type trait has_size");
static_assert(not tt::has_size<BClassInTestTypeTraits>::value,
              "Failed testing type trait has_size");
static_assert(not tt::has_size<double>::value,
              "Failed testing type trait has_size");
/// [has_size_example]

/// [is_integer_example]
static_assert(tt::is_integer<short>::value,
              "Failed testing type trait is_integer");
static_assert(tt::is_integer_v<unsigned short>,
              "Failed testing type trait is_integer");
static_assert(tt::is_integer_v<int>, "Failed testing type trait is_integer");
static_assert(tt::is_integer_v<unsigned int>,
              "Failed testing type trait is_integer");
static_assert(tt::is_integer_v<long>, "Failed testing type trait is_integer");
static_assert(tt::is_integer_v<unsigned long>,
              "Failed testing type trait is_integer");
static_assert(tt::is_integer_v<long long>,
              "Failed testing type trait is_integer");
static_assert(tt::is_integer_v<unsigned long long>,
              "Failed testing type trait is_integer");
static_assert(not tt::is_integer_v<bool>,
              "Failed testing type trait is_integer");
static_assert(not tt::is_integer_v<char>,
              "Failed testing type trait is_integer");
/// [is_integer_example]

/// [remove_reference_wrapper_example]
static_assert(
    cpp17::is_same_v<const double, tt::remove_reference_wrapper_t<
                                       std::reference_wrapper<const double>>>,
    "Failed testing remove_reference_wrapper");
static_assert(cpp17::is_same_v<const double,
                               tt::remove_reference_wrapper_t<const double>>,
              "Failed testing remove_reference_wrapper");
static_assert(
    cpp17::is_same_v<
        double, tt::remove_reference_wrapper_t<std::reference_wrapper<double>>>,
    "Failed testing remove_reference_wrapper");
static_assert(cpp17::is_same_v<double, tt::remove_reference_wrapper_t<double>>,
              "Failed testing remove_reference_wrapper");
static_assert(cpp17::is_same_v<const A, tt::remove_reference_wrapper_t<
                                            std::reference_wrapper<const A>>>,
              "Failed testing remove_reference_wrapper");
static_assert(
    cpp17::is_same_v<const A, tt::remove_reference_wrapper_t<const A>>,
    "Failed testing remove_reference_wrapper");
static_assert(cpp17::is_same_v<
                  A, tt::remove_reference_wrapper_t<std::reference_wrapper<A>>>,
              "Failed testing remove_reference_wrapper");
static_assert(cpp17::is_same_v<A, tt::remove_reference_wrapper_t<A>>,
              "Failed testing remove_reference_wrapper");
/// [remove_reference_wrapper_example]
