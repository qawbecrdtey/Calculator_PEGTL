#ifndef Calculator_Grammar_hpp
#define Calculator_Grammar_hpp

#include <tao/pegtl.hpp>

namespace Calculator {
    namespace {
        struct expression;
        struct semiexpr;
		struct mathexpr;

    /// misc
        struct blank : tao::pegtl::blank {};
        struct blanks : tao::pegtl::plus<blank> {};
        struct digit : tao::pegtl::digit {};
        struct digits : tao::pegtl::plus<digit> {};
        struct empty : tao::pegtl::star<blank> {};
        struct space : tao::pegtl::space {};
		struct spaces : tao::pegtl::star<space> {};

    /// symbols
        struct ampersand_sym : tao::pegtl::one<'&'> {};
        struct caret_sym : tao::pegtl::one<'^'> {};
        struct colon_sym : tao::pegtl::one<':'> {};
        struct exclamation_sym : tao::pegtl::one<'!'> {};
        struct minus_sym : tao::pegtl::one<'-'> {};
        struct percent_sym : tao::pegtl::one<'%'> {};
        struct plus_sym : tao::pegtl::one<'+'> {};
        struct question_sym : tao::pegtl::one<'?'> {};
        struct semicolon_sym : tao::pegtl::one<';'> {};
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

        /// precedence based on C
        struct precedence_5 : tao::pegtl::sor<
            star_sym,
            slash_sym,
            percent_sym
        > {};

        struct precedence_6 : tao::pegtl::sor<
            plus_sym,
            minus_sym
        > {};

    /// brackets

        /// unpaired
        struct close_brack : tao::pegtl::one<']'> {};
        struct close_curly : tao::pegtl::one<'}'> {};
        struct close_paren : tao::pegtl::one<')'> {};
        struct open_brack : tao::pegtl::one<'['> {};
        struct open_curly : tao::pegtl::one<'{'> {};
        struct open_paren : tao::pegtl::one<'('> {};
        
        /// paired brackets
        struct brack : tao::pegtl::seq<
            open_brack,
            mathexpr,
            close_brack
        > {};
        struct curly : tao::pegtl::seq<
            open_curly,
            mathexpr,
            close_curly
        > {};
		template<typename what>
		struct paren : tao::pegtl::seq<
			open_paren,
			what,
			close_paren
		> {};

    /// keywords
        struct print_str : tao::pegtl::string<'p', 'r', 'i', 'n', 't'> {};

        struct keyword : tao::pegtl::sor<
            print_str
        > {};

    /// grammar

        /// block
        struct block : tao::pegtl::sor<
            digits,
            paren<mathexpr>
        > {};

        /// term
        struct term : tao::pegtl::seq<
            spaces,
			tao::pegtl::list<
				block,
				precedence_5,
				space
			>,
            spaces
        >{};

        /// mathexpr
        struct mathexpr : tao::pegtl::seq<
            spaces,
			tao::pegtl::list<
				term,
				precedence_6,
				space
			>,
            spaces
        > {};

		/// print command
		struct print_command : tao::pegtl::seq<
			print_str,
			spaces,
			paren<mathexpr>
		> {};

        /// semiexpr
        struct semiexpr : tao::pegtl::sor<
            mathexpr,
            print_command
        > {};

        /// expression
        struct expression : tao::pegtl::seq<
            semiexpr,
            semicolon_sym
        > {};
    }
    struct grammar : tao::pegtl::must<
        tao::pegtl::list<expression, spaces>,
        tao::pegtl::eolf
    > {};
}

#endif