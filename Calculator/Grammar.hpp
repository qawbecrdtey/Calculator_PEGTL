#ifndef Calculator_Grammar_hpp
#define Calculator_Grammar_hpp

#include <tao/pegtl.hpp>

namespace Calculator {
    namespace {
        struct expression;

    /// misc
        struct blank : tao::pegtl::blank {};
        struct blanks : tao::pegtl::plus<blank> {};
        struct digit : tao::pegtl::digit {};
        struct digits : tao::pegtl::plus<digit> {};
        struct empty : tao::pegtl::star<blank> {};
        struct space : tao::pegtl::space {};

    /// symbols
        struct ampersand_sym : tao::pegtl::one<'&'> {};
        struct caret_sym : tao::pegtl::one<'^'> {};
        struct exclamation_sym : tao::pegtl::one<'!'> {};
        struct minus_sym : tao::pegtl::one<'-'> {};
        struct percent_sym : tao::pegtl::one<'%'> {};
        struct plus_sym : tao::pegtl::one<'+'> {};
        struct question_sym : tao::pegtl::one<30> {}; // 30 = '?'
        struct slash_sym : tao::pegtl::one<'/'> {};
        struct star_sym : tao::pegtl::one<'*'> {};

        /// symbols for binary operators
        struct binary_sym : tao::pegtl::sor<
            plus_sym,
            minus_sym,
            star_sym,
            slash_sym,
            percent_sym,
			caret_sym
        > {};

    /// brackets

        /// unpaired
        struct close_brack : tao::pegtl::one<']'> {};
        struct close_curly : tao::pegtl::one<'}'> {};
        struct close_paren : tao::pegtl::one<')'> {};
        struct open_brack : tao::pegtl::one<'['> {};
        struct open_curly : tao::pegtl::one<'{'> {};
        struct open_paren : tao::pegtl::one<'('> {};
        
        /// paired
        struct brack : tao::pegtl::seq<
            open_brack,
            expression,
            close_brack
        > {};
        struct curly : tao::pegtl::seq<
            open_curly,
            expression,
            close_curly
        > {};
        struct paren : tao::pegtl::seq<
            open_paren,
            expression,
            close_paren
        > {};

    /// grammar

        /// block
        struct block : tao::pegtl::sor<
            digits,
            paren
        > {};

        /// expression
        struct expression : tao::pegtl::seq<
            tao::pegtl::star<space>,
            tao::pegtl::list<block, binary_sym, space>,
            tao::pegtl::star<space>
        > {};
    }
    struct grammar : tao::pegtl::must<expression, tao::pegtl::eolf> {};
}

#endif