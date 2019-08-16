#include <iostream>

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/parse_tree.hpp>

#include "Calculator/Grammar.hpp"
#include "Calculator/Action.hpp"
#include "Calculator/ParseTree.hpp"

int main() {
	std::string const s = "1+2*(3-4)-5/6;\nprint(7*8-9/10);";
    try {
        tao::pegtl::memory_input in(s, "");
        tao::pegtl::parse<Calculator::grammar, Calculator::action>(in);

        //auto root = tao::pegtl::parse_tree::parse<Calculator::grammar>(in);
    }
    catch(tao::pegtl::parse_error &e) {
        std::cout << s << " is not an expression!\n";
		std::cout << e.what() << std::endl;
    }
    catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}