#include <iostream>

#include <tao/pegtl.hpp>

#include "Calculator/Grammar.hpp"
#include "Calculator/Action.hpp"

int main() {
	std::string const s = "((1+2-3 *4-(5+6	*7)+(8-9+  10))+(11*12*(13-     14)+15))         /(16^17+18%19)";
    try {
        tao::pegtl::memory_input in(s, "");
        tao::pegtl::parse<Calculator::grammar, Calculator::action>(in);
    }
    catch(tao::pegtl::parse_error &e) {
        std::cout << s << " is not an expression!\n";
    }
    catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}