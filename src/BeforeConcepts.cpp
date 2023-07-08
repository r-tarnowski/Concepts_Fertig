#include <iostream>

using std::cout;
using std::endl;

void printHeader() {
   cout << endl;
   cout << "===============================================" << endl;
   cout << "   Programming with C++20 by Andreas Fertig    " << endl;
   cout << "    Concepts - Programming before Concepts     " << endl;
   cout << "===============================================" << endl;
   cout << endl;
}

template <typename T, typename ... Ts>
constexpr inline bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename T, typename ... >
struct first_arg {
   using type = T;
};

template<typename ... Args>
using firts_arg_t = typename first_arg<Args...>::type;

template<typename... Args>
std::enable_if_t<are_same_v<Args...>, firts_arg_t<Args...>>
add( const Args&... args ) noexcept {
   return ( ... + args );
}

template<typename... Args>
requires are_same_v<Args...>
auto add_with_concept( const Args&... args ) noexcept {
   return ( ... + args );
}

int main(int argc, char *argv[]) {
   printHeader();

   std::cout <<  "add( 1, 2, 3, 4 ) -> " << add( 1, 2, 3, 4 ) << std::endl;

   std::string ala = "Ala";
   std::string ma = "ma";
   std::string kota = "kota";
   std::string spacja = " ";
   std::cout <<  "add( ala, spacja, ma, spacja, kota ) -> "
             << add( ala, spacja, ma, spacja, kota ) << std::endl;

   std::cout << "add( 1.0, 2.0, 3.0, 4.5 ) -> "
             << add( 1.0, 2.0, 3.0, 4.5 ) << std::endl;

   cout << "------------------------------------------------------------------------" << endl;
   std::cout <<  "add_with_concept( 1, 2, 3, 4 ) -> " << add_with_concept( 1, 2, 3, 4 ) << std::endl;
   std::cout << "add_with_concept( 1.0, 2.0, 3.0, 4.5 ) -> "
             << add_with_concept( 1.0, 2.0, 3.0, 4.5 ) << std::endl;
   std::cout <<  "add_with_concept( ala, spacja, ma, spacja, kota ) -> "
             << add_with_concept( ala, spacja, ma, spacja, kota ) << std::endl;
   std::cout <<  "add_with_concept( ala, spacja, ma, spacja, static_cast<std::string>(\"psa\") ) -> "
             << add_with_concept( ala, spacja, ma, spacja, static_cast<std::string>("psa") ) << std::endl;
   std::cout <<  "add_with_concept( ala, spacja, ma, spacja, std::string(\"papugę\") ) -> "
             << add_with_concept( ala, spacja, ma, spacja, std::string("papugę") ) << std::endl;

   return 0;
}
