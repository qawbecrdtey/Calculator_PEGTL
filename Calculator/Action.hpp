#ifndef Calculator_Action_hpp
#define Calculator_Action_hpp

#include <iostream>
#include <stack>

#include "Grammar.hpp"

namespace Calculator {
    template<typename Rule>
    struct action : tao::pegtl::nothing<Rule> {};
    
    template<>
    struct action<open_paren> {
        static void apply0() {
            std::cout << '(' << std::endl;
        }
    };

    template<>
    struct action<close_paren> {
        static void apply0() {
            std::cout << ')' << std::endl;
        }
    };

    template<>
    struct action<digit> {
        template<typename Input>
        static void apply(Input const &in) {
            std::cout << in.string() << " is a digit\n";
        }
    };

    template<>
    struct action<block> {
        template<typename Input>
        static void apply(Input const &in) {
            std::cout << in.string() << " is a block\n";
        }
    };

	template<>
	struct action<term> {
		template<typename Input>
		static void apply(Input const &in) {
			std::cout << in.string() << " is a term\n";
		}
	};

    template<>
    struct action<mathexpr> {
        template<typename Input>
        static void apply(Input const &in) {
            std::cout << in.string() << " is a mathexpr\n";
        }
	};

	template<>
	struct action<print_command> {
		template<typename Input>
		static void apply(Input const &in) {
			std::cout << in.string() << " is a print command\n";
		}
	};

    template<>
    struct action<semiexpr> {
        template<typename Input>
        static void apply(Input const &in) {
            std::cout << in.string() << " is a semiexpr\n";
        }
    };

    template<>
    struct action<expression> {
        template<typename Input>
        static void apply(Input const &in) {
            std::cout << in.string() << " is an expression\n";
        }
    };

    template<>
    struct action<binary_sym> {
        template<typename Input>
        static void apply(Input const &in) {
            std::cout << in.string() << " is a binary operator\n";
        }
    };

    template<>
    struct action<grammar> {
        template<typename Input>
        static void apply(Input const &in) {
            std::cout << in.string() << " matches the grammar!\n";
        }
	};
}

#endif