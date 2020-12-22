// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.
// //                    "%code top" blocks.
#line 33 "parser.y" // lalr1.cc:397

    #include <iostream>
    #include "scanner.h"
    #include "parser.hpp"
    #include "interpreter.h"
    #include "location.hh"
    
    // yylex() arguments are defined in parser.y
    static Compiler::Parser::symbol_type yylex(Compiler::Scanner &scanner, Compiler::Interpreter &driver) {
        return scanner.get_next_token();
    }
    
    // you can accomplish the same thing by inlining the code using preprocessor
    // x and y are same as in above static function
    // #define yylex(x, y) scanner.get_next_token()
    
    using namespace Compiler;

#line 53 "parser.cpp" // lalr1.cc:397


// First part of user declarations.

#line 58 "parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hpp"

// User implementation prologue.

#line 72 "parser.cpp" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 16 "parser.y" // lalr1.cc:479
namespace  Compiler  {
#line 158 "parser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   Parser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
   Parser :: Parser  (Compiler::Scanner &scanner_yyarg, Compiler::Interpreter &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

   Parser ::~ Parser  ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
   Parser ::by_state::by_state ()
    : state (empty_state)
  {}

  inline
   Parser ::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
   Parser ::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
   Parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
   Parser ::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
   Parser ::symbol_number_type
   Parser ::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
   Parser ::stack_symbol_type::stack_symbol_type ()
  {}


  inline
   Parser ::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 3: // LP
      case 4: // RP
      case 5: // LC
      case 6: // RC
      case 7: // LB
      case 8: // RB
      case 9: // COMMA
      case 10: // DOT
      case 11: // SEMI
      case 12: // LT
      case 13: // LE
      case 14: // GT
      case 15: // GE
      case 16: // NE
      case 17: // EQ
      case 18: // PLUS
      case 19: // MINUS
      case 20: // MUL
      case 21: // DIV
      case 22: // AND
      case 23: // OR
      case 24: // NOT
      case 25: // ASSIGN
      case 26: // STRUCT
      case 27: // ID
      case 28: // CHAR
      case 29: // INT
      case 30: // FLOAT
      case 31: // WHILE
      case 32: // TYPE
      case 33: // IF
      case 34: // ELSE
      case 35: // RETURN
      case 36: // UNKNOW
      case 40: // Program
      case 41: // ExtDefList
      case 42: // ExtDef
      case 43: // ExtDecList
      case 44: // Specifier
      case 45: // StructSpecifier
      case 46: // VarDec
      case 47: // FunDec
      case 48: // VarList
      case 49: // ParamDec
      case 50: // CompSt
      case 51: // StmtList
      case 52: // Stmt
      case 53: // DefList
      case 54: // Def
      case 55: // DecList
      case 56: // Dec
      case 57: // Exp
      case 58: // Args
        value.move< Compiler::ASTNode* > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 3: // LP
      case 4: // RP
      case 5: // LC
      case 6: // RC
      case 7: // LB
      case 8: // RB
      case 9: // COMMA
      case 10: // DOT
      case 11: // SEMI
      case 12: // LT
      case 13: // LE
      case 14: // GT
      case 15: // GE
      case 16: // NE
      case 17: // EQ
      case 18: // PLUS
      case 19: // MINUS
      case 20: // MUL
      case 21: // DIV
      case 22: // AND
      case 23: // OR
      case 24: // NOT
      case 25: // ASSIGN
      case 26: // STRUCT
      case 27: // ID
      case 28: // CHAR
      case 29: // INT
      case 30: // FLOAT
      case 31: // WHILE
      case 32: // TYPE
      case 33: // IF
      case 34: // ELSE
      case 35: // RETURN
      case 36: // UNKNOW
      case 40: // Program
      case 41: // ExtDefList
      case 42: // ExtDef
      case 43: // ExtDecList
      case 44: // Specifier
      case 45: // StructSpecifier
      case 46: // VarDec
      case 47: // FunDec
      case 48: // VarList
      case 49: // ParamDec
      case 50: // CompSt
      case 51: // StmtList
      case 52: // Stmt
      case 53: // DefList
      case 54: // Def
      case 55: // DecList
      case 56: // Dec
      case 57: // Exp
      case 58: // Args
        value.copy< Compiler::ASTNode* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
   Parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   Parser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
   Parser ::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
   Parser ::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
   Parser ::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   Parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   Parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   Parser ::debug_level_type
   Parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   Parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline  Parser ::state_type
   Parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
   Parser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
   Parser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   Parser ::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 3: // LP
      case 4: // RP
      case 5: // LC
      case 6: // RC
      case 7: // LB
      case 8: // RB
      case 9: // COMMA
      case 10: // DOT
      case 11: // SEMI
      case 12: // LT
      case 13: // LE
      case 14: // GT
      case 15: // GE
      case 16: // NE
      case 17: // EQ
      case 18: // PLUS
      case 19: // MINUS
      case 20: // MUL
      case 21: // DIV
      case 22: // AND
      case 23: // OR
      case 24: // NOT
      case 25: // ASSIGN
      case 26: // STRUCT
      case 27: // ID
      case 28: // CHAR
      case 29: // INT
      case 30: // FLOAT
      case 31: // WHILE
      case 32: // TYPE
      case 33: // IF
      case 34: // ELSE
      case 35: // RETURN
      case 36: // UNKNOW
      case 40: // Program
      case 41: // ExtDefList
      case 42: // ExtDef
      case 43: // ExtDecList
      case 44: // Specifier
      case 45: // StructSpecifier
      case 46: // VarDec
      case 47: // FunDec
      case 48: // VarList
      case 49: // ParamDec
      case 50: // CompSt
      case 51: // StmtList
      case 52: // Stmt
      case 53: // DefList
      case 54: // Def
      case 55: // DecList
      case 56: // Dec
      case 57: // Exp
      case 58: // Args
        yylhs.value.build< Compiler::ASTNode* > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 98 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Program", yylhs.location.begin.line);
          driver.setRoot(yylhs.value.as< Compiler::ASTNode* > ());
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 706 "parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 105 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("ExtDefList", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 715 "parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 109 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("ExtDefList", yylhs.location.begin.line); 
      }
#line 723 "parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 112 "parser.y" // lalr1.cc:859
    {
          std::cout << "Please check by yourself" << endl;
          driver.setErrorFlag();
          driver.appendErrorMsg(1, std::string("Please check by yourself"), yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Error", yylhs.location.begin.line);
      }
#line 734 "parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 120 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("ExtDef", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 743 "parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 124 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("ExtDef", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 752 "parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 128 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("ExtDef", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 761 "parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 132 "parser.y" // lalr1.cc:859
    {
          std::cout << "Missing semicolon ';'" << std::endl;
          driver.setErrorFlag();
          driver.appendErrorMsg(1, std::string("Missing semicolon ';'"), yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Error", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > ());
      }
#line 773 "parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 142 "parser.y" // lalr1.cc:859
    {
          std::cout << "Missing semicolon ';'" << std::endl;
          driver.setErrorFlag();
          driver.appendErrorMsg(1, std::string("Missing semicolon ';'"), yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Error", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[1].value.as< Compiler::ASTNode* > ());
      }
#line 785 "parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 151 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("ExtDecList", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 794 "parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 155 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("ExtDecList", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 803 "parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 161 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Specifier", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 812 "parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 165 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Specifier", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 821 "parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 171 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("StructSpecifier", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(5, yystack_[4].value.as< Compiler::ASTNode* > (), yystack_[3].value.as< Compiler::ASTNode* > (), yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 830 "parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 175 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("StructSpecifier", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 839 "parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 181 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("VarDec", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 848 "parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 185 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("VarDec", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(4, yystack_[3].value.as< Compiler::ASTNode* > (), yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 857 "parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 189 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("UNKNOW_VarDec", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 866 "parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 195 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("FunDec", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(4, yystack_[3].value.as< Compiler::ASTNode* > (), yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 875 "parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 199 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("FunDec", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 884 "parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 203 "parser.y" // lalr1.cc:859
    {
        std::cout << "Missing closing parenthesis ')'" << endl;
        driver.setErrorFlag();
        driver.appendErrorMsg(1, std::string("Missing closing parenthesis ')'"), yylhs.location.begin.line);
        yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Error", yylhs.location.begin.line);
        yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > ());
      }
#line 896 "parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 210 "parser.y" // lalr1.cc:859
    {
        std::cout << "Missing closing parenthesis ')'" << std::endl;
        driver.setErrorFlag();
        driver.appendErrorMsg(1, std::string("Missing closing parenthesis ')'"), yylhs.location.begin.line);
        yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Error", yylhs.location.begin.line);
        yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[3].value.as< Compiler::ASTNode* > (), yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > ());
      }
#line 908 "parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 217 "parser.y" // lalr1.cc:859
    {
        std::cout << "Missing specifier" << std::endl;
        driver.setErrorFlag();
        driver.appendErrorMsg(1, std::string("Missing specifier"), yylhs.location.begin.line);
        yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Error", yylhs.location.begin.line);
        yylhs.value.as< Compiler::ASTNode* > ()->addChild(4, yystack_[4].value.as< Compiler::ASTNode* > (), yystack_[3].value.as< Compiler::ASTNode* > (), yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > ());
      }
#line 920 "parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 226 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("VarList", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 929 "parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 230 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("VarList", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 938 "parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 236 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("ParamDec", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 947 "parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 242 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("CompSt", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(4, yystack_[3].value.as< Compiler::ASTNode* > (), yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 956 "parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 248 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("StmtList", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 965 "parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 252 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("StmtList", yylhs.location.begin.line); 
      }
#line 973 "parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 257 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Stmt", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 982 "parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 261 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Stmt", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 991 "parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 265 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Stmt", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1000 "parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 269 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Stmt", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(5, yystack_[4].value.as< Compiler::ASTNode* > (), yystack_[3].value.as< Compiler::ASTNode* > (), yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1009 "parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 273 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Stmt", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(7, yystack_[6].value.as< Compiler::ASTNode* > (), yystack_[5].value.as< Compiler::ASTNode* > (), yystack_[4].value.as< Compiler::ASTNode* > (), yystack_[3].value.as< Compiler::ASTNode* > (), yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1018 "parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 277 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Stmt", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(5, yystack_[4].value.as< Compiler::ASTNode* > (), yystack_[3].value.as< Compiler::ASTNode* > (), yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1027 "parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 281 "parser.y" // lalr1.cc:859
    {
        driver.setErrorFlag();
        driver.appendErrorMsg(1, std::string("Missing semicolon ';'"), yylhs.location.begin.line);
        std::cout << "Missing semicolon ';'" << std::endl;
        yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Error", yylhs.location.begin.line);
        yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[1].value.as< Compiler::ASTNode* > ());
      }
#line 1039 "parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 288 "parser.y" // lalr1.cc:859
    {
        driver.setErrorFlag();
        driver.appendErrorMsg(1, std::string("Missing semicolon ';'"), yylhs.location.begin.line);
        std::cout << "Missing semicolon ';'" << std::endl;
        yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Error", yylhs.location.begin.line);
        yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > ());
      }
#line 1051 "parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 297 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("DefList", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1060 "parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 301 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("DefList", yylhs.location.begin.line); 
      }
#line 1068 "parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 306 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Def", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1077 "parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 310 "parser.y" // lalr1.cc:859
    {
          driver.setErrorFlag();
          driver.appendErrorMsg(1, std::string("Missing semicolon ';'"), yystack_[0].location.begin.line);
          std::cout << "Missing semicolon ';'" << std::endl;
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Error", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > ());
      }
#line 1089 "parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 319 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("DecList", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1098 "parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 323 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("DecList", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1107 "parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 329 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Dec", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1116 "parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 333 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Dec", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1125 "parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 339 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1134 "parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 343 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1143 "parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 347 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1152 "parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 351 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1161 "parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 355 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1170 "parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 359 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1179 "parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 363 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1188 "parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 367 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1197 "parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 371 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1206 "parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 375 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1215 "parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 379 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1224 "parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 383 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1233 "parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 387 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1242 "parser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 391 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("UNKNOW_Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1251 "parser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 395 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1260 "parser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 399 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1269 "parser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 403 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1278 "parser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 407 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(4, yystack_[3].value.as< Compiler::ASTNode* > (), yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1287 "parser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 411 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1296 "parser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 423 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(4, yystack_[3].value.as< Compiler::ASTNode* > (), yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1305 "parser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 427 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1314 "parser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 431 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1323 "parser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 435 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1332 "parser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 439 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1341 "parser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 443 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1350 "parser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 447 "parser.y" // lalr1.cc:859
    {
          driver.setErrorFlag();
          std::cout << "Missing closing parenthesis ')'" << endl;
          driver.appendErrorMsg(1, std::string("Missing closing parenthesis ')'"), yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Error_Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[3].value.as< Compiler::ASTNode* > (), yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > ());
      }
#line 1362 "parser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 454 "parser.y" // lalr1.cc:859
    {
          driver.setErrorFlag();
          std::cout << "Missing closing parenthesis ')'" << endl;
          driver.appendErrorMsg(1, std::string("Missing closing parenthesis ')'"), yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Error_Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(2, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > ());
      }
#line 1374 "parser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 461 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("UNKNOW_Exp", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1383 "parser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 467 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Args", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(3, yystack_[2].value.as< Compiler::ASTNode* > (), yystack_[1].value.as< Compiler::ASTNode* > (), yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1392 "parser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 471 "parser.y" // lalr1.cc:859
    {
          yylhs.value.as< Compiler::ASTNode* > () = new ASTNode("Args", yylhs.location.begin.line);
          yylhs.value.as< Compiler::ASTNode* > ()->addChild(1, yystack_[0].value.as< Compiler::ASTNode* > ());
      }
#line 1401 "parser.cpp" // lalr1.cc:859
    break;


#line 1405 "parser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
   Parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
   Parser ::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char  Parser ::yypact_ninf_ = -108;

  const signed char  Parser ::yytable_ninf_ = -5;

  const short int
   Parser ::yypact_[] =
  {
      51,  -108,   -22,  -108,    11,  -108,    51,   102,  -108,    13,
    -108,  -108,  -108,  -108,    71,  -108,     3,    23,    76,    46,
     181,  -108,  -108,    78,   -19,    46,  -108,   -19,    74,    46,
    -108,  -108,   100,   -19,    15,    96,   104,  -108,  -108,   113,
      -4,     9,   101,  -108,  -108,   107,   108,  -108,  -108,    46,
    -108,   128,   128,   128,   111,  -108,  -108,  -108,   118,   120,
     128,  -108,  -108,   124,   113,    48,   128,  -108,  -108,   -19,
    -108,  -108,   155,    43,    43,    98,   128,   128,    75,  -108,
    -108,  -108,   128,    97,  -108,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   280,
    -108,  -108,  -108,  -108,   230,    53,   180,   205,  -108,  -108,
     255,  -108,   349,   349,   349,   349,   349,   349,    99,    99,
      43,    43,   330,   305,   280,  -108,   128,  -108,  -108,   113,
     113,  -108,  -108,  -108,   105,   113,  -108
  };

  const unsigned char
   Parser ::yydefact_[] =
  {
       0,     5,     0,    13,     0,     2,     0,     0,    14,    16,
       1,     3,    10,     7,    17,    19,     0,    11,     0,    40,
       0,     9,     6,     0,     0,    40,     8,     0,     0,    40,
      22,    21,     0,     0,     0,    26,     0,    17,    12,    30,
      45,     0,    43,    15,    39,     0,    27,    23,    20,     0,
      18,     0,     0,     0,    68,    71,    69,    70,     0,     0,
       0,    74,    32,     0,    30,     0,     0,    42,    41,     0,
      24,    25,     0,    62,    63,     0,     0,     0,     0,    28,
      29,    37,     0,     0,    31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
      44,    61,    73,    65,    76,     0,     0,     0,    38,    33,
       0,    67,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    48,    49,    47,    60,     0,    72,    64,     0,
       0,    66,    75,    36,    34,     0,    35
  };

  const short int
   Parser ::yypgoto_[] =
  {
    -108,  -108,   127,  -108,   112,     7,  -108,   -21,  -108,   114,
    -108,   132,    81,  -107,     4,  -108,    82,  -108,   -51,    27
  };

  const signed char
   Parser ::yydefgoto_[] =
  {
      -1,     4,     5,     6,    16,    27,     8,    17,    18,    34,
      35,    62,    63,    64,    28,    29,    41,    42,    65,   105
  };

  const short int
   Parser ::yytable_[] =
  {
      72,    73,    74,    23,    21,     9,    40,     7,    37,    78,
      67,    10,    46,     7,    22,    99,    47,    15,    19,    48,
      68,    66,   133,   134,   104,   106,   107,    33,   136,    39,
      23,   110,    24,    44,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,    40,    81,
      82,    -4,     1,    83,   127,    82,    33,   128,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,     2,    97,    20,   104,   108,     2,     3,    98,
      43,    25,    82,     3,    98,    83,   109,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,   102,
      97,    51,   103,    12,    45,    49,    82,    36,    70,    83,
      69,    98,    50,    13,    75,    23,    51,    52,    25,    93,
      94,    76,    53,    77,   111,    54,    55,    56,    57,    14,
      79,    51,    52,    11,    61,    98,    38,    53,    15,   135,
      54,    55,    56,    57,    58,    80,    59,    52,    60,    61,
      26,   100,    53,   132,     0,    54,    55,    56,    57,   101,
       0,     0,    82,    71,    61,    83,     0,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     0,
      97,     0,    30,     0,   129,    31,     0,    82,     0,     0,
      83,    98,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,     0,    97,     0,     2,    32,   130,
       0,     0,    82,     3,     0,    83,    98,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     0,
      97,     0,     0,     0,     0,     0,     0,    82,     0,   126,
      83,    98,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,     0,    97,     0,     0,     0,     0,
       0,     0,    82,   131,     0,    83,    98,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     0,
      97,     0,     0,     0,     0,     0,     0,    82,     0,     0,
      83,    98,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,     0,    97,     0,     0,     0,     0,
       0,     0,    82,     0,     0,    83,    98,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,     0,     0,
      83,    98,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,     0,     0,     0,     0,    82,     0,     0,    83,
       0,     0,     0,     0,     0,     0,    98,    91,    92,    93,
      94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    98
  };

  const short int
   Parser ::yycheck_[] =
  {
      51,    52,    53,     7,     1,    27,    27,     0,    27,    60,
       1,     0,    33,     6,    11,    66,     1,    36,     5,     4,
      11,    25,   129,   130,    75,    76,    77,    20,   135,    25,
       7,    82,     9,    29,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    69,     1,
       7,     0,     1,    10,     1,     7,    49,     4,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    26,    25,     3,   126,     1,    26,    32,    36,
       6,     5,     7,    32,    36,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,     1,
      25,     3,     4,     1,     4,     9,     7,    29,     1,    10,
       9,    36,     8,    11,     3,     7,     3,    19,     5,    20,
      21,     3,    24,     3,    27,    27,    28,    29,    30,    27,
       6,     3,    19,     6,    36,    36,    24,    24,    36,    34,
      27,    28,    29,    30,    31,    64,    33,    19,    35,    36,
      18,    69,    24,   126,    -1,    27,    28,    29,    30,     4,
      -1,    -1,     7,    49,    36,    10,    -1,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,     1,    -1,     4,     4,    -1,     7,    -1,    -1,
      10,    36,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    25,    -1,    26,    27,     4,
      -1,    -1,     7,    32,    -1,    10,    36,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,     9,
      10,    36,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,     7,     8,    -1,    10,    36,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,    -1,
      10,    36,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,     7,    -1,    -1,    10,    36,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,    -1,
      10,    36,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,     7,    -1,    -1,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36
  };

  const unsigned char
   Parser ::yystos_[] =
  {
       0,     1,    26,    32,    40,    41,    42,    44,    45,    27,
       0,    41,     1,    11,    27,    36,    43,    46,    47,     5,
       3,     1,    11,     7,     9,     5,    50,    44,    53,    54,
       1,     4,    27,    44,    48,    49,    29,    27,    43,    53,
      46,    55,    56,     6,    53,     4,    46,     1,     4,     9,
       8,     3,    19,    24,    27,    28,    29,    30,    31,    33,
      35,    36,    50,    51,    52,    57,    25,     1,    11,     9,
       1,    48,    57,    57,    57,     3,     3,     3,    57,     6,
      51,     1,     7,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    25,    36,    57,
      55,     4,     1,     4,    57,    58,    57,    57,     1,    11,
      57,    27,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,     9,     1,     4,     4,
       4,     8,    58,    52,    52,    34,    52
  };

  const unsigned char
   Parser ::yyr1_[] =
  {
       0,    39,    40,    41,    41,    41,    42,    42,    42,    42,
      42,    43,    43,    44,    44,    45,    45,    46,    46,    46,
      47,    47,    47,    47,    47,    48,    48,    49,    50,    51,
      51,    52,    52,    52,    52,    52,    52,    52,    52,    53,
      53,    54,    54,    55,    55,    56,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    58,    58
  };

  const unsigned char
   Parser ::yyr2_[] =
  {
       0,     2,     1,     2,     0,     1,     3,     2,     3,     3,
       2,     1,     3,     1,     1,     5,     2,     1,     4,     1,
       4,     3,     3,     4,     5,     3,     1,     2,     4,     2,
       0,     2,     1,     3,     5,     7,     5,     2,     3,     2,
       0,     3,     3,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     4,     3,     4,     3,     1,     1,
       1,     1,     4,     3,     1,     3,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  Parser ::yytname_[] =
  {
  "END", "error", "$undefined", "LP", "RP", "LC", "RC", "LB", "RB",
  "COMMA", "DOT", "SEMI", "LT", "LE", "GT", "GE", "NE", "EQ", "PLUS",
  "MINUS", "MUL", "DIV", "AND", "OR", "NOT", "ASSIGN", "STRUCT", "ID",
  "CHAR", "INT", "FLOAT", "WHILE", "TYPE", "IF", "ELSE", "RETURN",
  "UNKNOW", "LOWER_ELSE", "UMINUS", "$accept", "Program", "ExtDefList",
  "ExtDef", "ExtDecList", "Specifier", "StructSpecifier", "VarDec",
  "FunDec", "VarList", "ParamDec", "CompSt", "StmtList", "Stmt", "DefList",
  "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   Parser ::yyrline_[] =
  {
       0,    98,    98,   105,   109,   112,   120,   124,   128,   132,
     142,   151,   155,   161,   165,   171,   175,   181,   185,   189,
     195,   199,   203,   210,   217,   226,   230,   236,   242,   248,
     252,   257,   261,   265,   269,   273,   277,   281,   288,   297,
     301,   306,   310,   319,   323,   329,   333,   339,   343,   347,
     351,   355,   359,   363,   367,   371,   375,   379,   383,   387,
     391,   395,   399,   403,   407,   411,   423,   427,   431,   435,
     439,   443,   447,   454,   461,   467,   471
  };

  // Print the state stack on the debug stream.
  void
   Parser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   Parser ::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 16 "parser.y" // lalr1.cc:1167
} //  Compiler 
#line 1912 "parser.cpp" // lalr1.cc:1167
#line 477 "parser.y" // lalr1.cc:1168


void Compiler::Parser::error(const location &loc, const std::string &msg) 
{
    /* fprintf(out, "Error type B at Line %d: %s\n", loc.begin.line, s); */
    cout << "Error type B at line " << loc.begin.line << ": " << msg << "\n";
}
 /* void SYNError(const char *s, int line)
{
    fprintf(out, "Error type B at Line %d: %s\n", line, s);
} */

/* void yyerror(const char *s){
    fprintf(out, "syntax error: must be recovered \n");
    fprintf(out, "Error type B at Line %d: %s\n", yylloc.first_line, s);
    yyerrok;
} */

/* void initiate() {
    yycolno = 1;
    yylineno = 1;
    yytext = "";
    yyleng = 0;
    error = 0;
    root = NULL;
}  */

/* int main(int argc, char **argv){
    if(argc == 1) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(-1);
    } else {
        for (int i = 1; i < argc; ++ i) {
            initiate();
            int name_len = strlen(argv[i]);
            char *out_name = (char *)malloc(name_len + 1);
            strcpy(out_name, argv[i]);
            out_name[name_len - 3] = 'o';
            out_name[name_len - 2] = 'u';
            out_name[name_len - 1] = 't';
            out_name[name_len] = '\0';
            char buf[1024];
            int len;
            FILE *fp;
            if(!(fp = fopen(argv[i],"r")))
            {
                perror("fail to read");
                exit (1) ;
            }
            out = fopen(out_name, "w");
            yyrestart(fp);
            yyparse();
            if(!error)
                dfsPrint(root, 0);
            fclose(fp);
            fclose(out);
        }
    }
    return 0;
} */
