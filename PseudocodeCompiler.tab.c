/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "PseudocodeCompiler.y"

  #include<stdio.h>
  #include <stdlib.h>
  #include<string.h>
  #include<ctype.h>
  #define YYSTYPE double /* double type for YACC stack */
  char lexema[255];
  void yyerror(char *);
  int yylex();
  int IsReservedWord(char[], int);

#line 83 "PseudocodeCompiler.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    VAR = 258,                     /* VAR  */
    INTCONST = 259,                /* INTCONST  */
    DOUBLECONST = 260,             /* DOUBLECONST  */
    STRINGCONST = 261,             /* STRINGCONST  */
    PLUS = 262,                    /* PLUS  */
    MINUS = 263,                   /* MINUS  */
    TIMES = 264,                   /* TIMES  */
    DIVIDE = 265,                  /* DIVIDE  */
    EQUALS = 266,                  /* EQUALS  */
    PERCENT = 267,                 /* PERCENT  */
    UMINUS = 268,                  /* UMINUS  */
    COMMA = 269,                   /* COMMA  */
    LPAREN = 270,                  /* LPAREN  */
    RPAREN = 271,                  /* RPAREN  */
    LBRACKET = 272,                /* LBRACKET  */
    RBRACKET = 273,                /* RBRACKET  */
    LESSTHAN = 274,                /* LESSTHAN  */
    LESSEQUAL = 275,               /* LESSEQUAL  */
    GREATERTHAN = 276,             /* GREATERTHAN  */
    GREATEREQUAL = 277,            /* GREATEREQUAL  */
    EQUALITY = 278,                /* EQUALITY  */
    NOTEQUALITY = 279,             /* NOTEQUALITY  */
    INT = 280,                     /* INT  */
    DOUBLE = 281,                  /* DOUBLE  */
    INPUT = 282,                   /* INPUT  */
    OUTPUT = 283,                  /* OUTPUT  */
    SUBROUTINE = 284,              /* SUBROUTINE  */
    ENDSUBROUTINE = 285,           /* ENDSUBROUTINE  */
    RETURN = 286,                  /* RETURN  */
    IF = 287,                      /* IF  */
    THEN = 288,                    /* THEN  */
    ELSE = 289,                    /* ELSE  */
    ENDIF = 290,                   /* ENDIF  */
    WHILE = 291,                   /* WHILE  */
    DO = 292,                      /* DO  */
    ENDWHILE = 293,                /* ENDWHILE  */
    FOR = 294,                     /* FOR  */
    TO = 295,                      /* TO  */
    ENDFOR = 296                   /* ENDFOR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VAR = 3,                        /* VAR  */
  YYSYMBOL_INTCONST = 4,                   /* INTCONST  */
  YYSYMBOL_DOUBLECONST = 5,                /* DOUBLECONST  */
  YYSYMBOL_STRINGCONST = 6,                /* STRINGCONST  */
  YYSYMBOL_PLUS = 7,                       /* PLUS  */
  YYSYMBOL_MINUS = 8,                      /* MINUS  */
  YYSYMBOL_TIMES = 9,                      /* TIMES  */
  YYSYMBOL_DIVIDE = 10,                    /* DIVIDE  */
  YYSYMBOL_EQUALS = 11,                    /* EQUALS  */
  YYSYMBOL_PERCENT = 12,                   /* PERCENT  */
  YYSYMBOL_UMINUS = 13,                    /* UMINUS  */
  YYSYMBOL_COMMA = 14,                     /* COMMA  */
  YYSYMBOL_LPAREN = 15,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 16,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 17,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 18,                  /* RBRACKET  */
  YYSYMBOL_LESSTHAN = 19,                  /* LESSTHAN  */
  YYSYMBOL_LESSEQUAL = 20,                 /* LESSEQUAL  */
  YYSYMBOL_GREATERTHAN = 21,               /* GREATERTHAN  */
  YYSYMBOL_GREATEREQUAL = 22,              /* GREATEREQUAL  */
  YYSYMBOL_EQUALITY = 23,                  /* EQUALITY  */
  YYSYMBOL_NOTEQUALITY = 24,               /* NOTEQUALITY  */
  YYSYMBOL_INT = 25,                       /* INT  */
  YYSYMBOL_DOUBLE = 26,                    /* DOUBLE  */
  YYSYMBOL_INPUT = 27,                     /* INPUT  */
  YYSYMBOL_OUTPUT = 28,                    /* OUTPUT  */
  YYSYMBOL_SUBROUTINE = 29,                /* SUBROUTINE  */
  YYSYMBOL_ENDSUBROUTINE = 30,             /* ENDSUBROUTINE  */
  YYSYMBOL_RETURN = 31,                    /* RETURN  */
  YYSYMBOL_IF = 32,                        /* IF  */
  YYSYMBOL_THEN = 33,                      /* THEN  */
  YYSYMBOL_ELSE = 34,                      /* ELSE  */
  YYSYMBOL_ENDIF = 35,                     /* ENDIF  */
  YYSYMBOL_WHILE = 36,                     /* WHILE  */
  YYSYMBOL_DO = 37,                        /* DO  */
  YYSYMBOL_ENDWHILE = 38,                  /* ENDWHILE  */
  YYSYMBOL_FOR = 39,                       /* FOR  */
  YYSYMBOL_TO = 40,                        /* TO  */
  YYSYMBOL_ENDFOR = 41,                    /* ENDFOR  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_stmt_list = 43,                 /* stmt_list  */
  YYSYMBOL_simple_stmt = 44,               /* simple_stmt  */
  YYSYMBOL_if_stmt = 45,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 46,                /* while_stmt  */
  YYSYMBOL_for_stmt = 47,                  /* for_stmt  */
  YYSYMBOL_array_decl_stmt = 48,           /* array_decl_stmt  */
  YYSYMBOL_var_decl_stmt = 49,             /* var_decl_stmt  */
  YYSYMBOL_var_list = 50,                  /* var_list  */
  YYSYMBOL_assig_stmt = 51,                /* assig_stmt  */
  YYSYMBOL_input_stmt = 52,                /* input_stmt  */
  YYSYMBOL_output_stmt = 53,               /* output_stmt  */
  YYSYMBOL_return_stmt = 54,               /* return_stmt  */
  YYSYMBOL_function_header = 55,           /* function_header  */
  YYSYMBOL_function_stmt = 56,             /* function_stmt  */
  YYSYMBOL_exp_fun_call = 57,              /* exp_fun_call  */
  YYSYMBOL_arg_list = 58,                  /* arg_list  */
  YYSYMBOL_expr_list = 59,                 /* expr_list  */
  YYSYMBOL_array_index = 60,               /* array_index  */
  YYSYMBOL_exp = 61,                       /* exp  */
  YYSYMBOL_term = 62,                      /* term  */
  YYSYMBOL_exp_arit = 63,                  /* exp_arit  */
  YYSYMBOL_term_arit1 = 64,                /* term_arit1  */
  YYSYMBOL_term_arit2 = 65,                /* term_arit2  */
  YYSYMBOL_term_arit3 = 66                 /* term_arit3  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    27,    27,    28,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    41,    42,    44,    46,    48,    49,
      51,    52,    53,    54,    56,    57,    59,    60,    61,    62,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    77,    78,    80,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "VAR", "INTCONST",
  "DOUBLECONST", "STRINGCONST", "PLUS", "MINUS", "TIMES", "DIVIDE",
  "EQUALS", "PERCENT", "UMINUS", "COMMA", "LPAREN", "RPAREN", "LBRACKET",
  "RBRACKET", "LESSTHAN", "LESSEQUAL", "GREATERTHAN", "GREATEREQUAL",
  "EQUALITY", "NOTEQUALITY", "INT", "DOUBLE", "INPUT", "OUTPUT",
  "SUBROUTINE", "ENDSUBROUTINE", "RETURN", "IF", "THEN", "ELSE", "ENDIF",
  "WHILE", "DO", "ENDWHILE", "FOR", "TO", "ENDFOR", "$accept", "stmt_list",
  "simple_stmt", "if_stmt", "while_stmt", "for_stmt", "array_decl_stmt",
  "var_decl_stmt", "var_list", "assig_stmt", "input_stmt", "output_stmt",
  "return_stmt", "function_header", "function_stmt", "exp_fun_call",
  "arg_list", "expr_list", "array_index", "exp", "term", "exp_arit",
  "term_arit1", "term_arit2", "term_arit3", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-34)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     175,    32,     4,     5,    21,    79,    79,    79,    79,    28,
      26,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   175,   -34,    25,    79,    35,    30,    47,    42,   -34,
      56,    42,   -34,    30,   -34,    73,   -34,   -34,   -34,    79,
      79,   -34,   -34,    -4,    84,    88,   120,   -34,   -34,    -4,
      -6,   -12,    23,   -34,   -34,   130,    79,    -4,    71,    60,
      90,   110,    63,   -34,    57,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,   175,   175,   124,   -34,
      -4,   -34,    -3,   -34,    19,   -34,    58,    14,   -34,    84,
      84,    88,    88,    88,    88,   120,   120,   -34,   -34,   -34,
     115,   145,   175,   -34,    96,   141,    98,   -34,   121,    79,
     -34,    79,   -34,   175,   -34,   -34,    95,   -34,   -34,   113,
     -34,   -34,    -4,    -4,   160,   -34,   142,   156,   -34,   -34,
     -34
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     7,     8,     9,     5,     6,     4,    11,    10,
      13,     0,    12,     0,     0,     0,    22,     0,    21,    19,
       0,    20,    18,    26,    27,    66,    63,    64,    65,     0,
       0,    68,    67,    28,    47,    52,    55,    59,    61,    29,
       0,     0,     0,     1,     3,     0,     0,    24,     0,     0,
       0,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      25,    44,     0,    23,     0,    37,     0,     0,    62,    45,
      46,    48,    50,    49,    51,    53,    54,    56,    57,    58,
       0,     0,     0,    32,     0,     0,     0,    33,     0,     0,
      36,     0,    35,     0,    14,    16,     0,    38,    39,     0,
      30,    31,    43,    42,     0,    17,     0,     0,    15,    40,
      41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -34,   -16,    -9,   -34,   -34,   -34,   -34,   -34,   164,   159,
     -34,   -34,   -34,   -34,   -34,   -34,    91,   -34,     0,     8,
      87,    41,    93,   -33,   -34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    10,    11,    12,    13,    14,    15,    16,    28,    17,
      18,    19,    20,    21,    22,    41,   106,    86,    42,    43,
      44,    45,    46,    47,    48
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      23,    54,    29,    32,    34,    55,    63,    26,    26,    23,
      23,    65,    66,   103,    49,    50,    51,    65,    66,    65,
      66,    23,   104,   105,    33,    77,    53,    76,   111,     1,
     112,     1,    57,    27,    30,   107,    56,    65,    66,    58,
      97,    98,    99,    24,   104,   105,    54,    25,    64,    25,
      59,     2,     3,     4,     5,    23,    60,     6,     7,    61,
     100,   101,     8,    78,    80,     9,    35,    36,    37,    38,
      87,    39,   109,    88,   110,    82,    23,    23,    40,    85,
      65,    66,    35,    36,    37,    38,   116,    39,    62,    81,
      25,    54,    54,    83,    40,    71,    72,   124,     1,   117,
      23,    23,    23,    67,    68,    69,    70,    54,    91,    92,
      93,    94,   119,    23,   120,    54,    23,   122,     1,   123,
       2,     3,     4,     5,    23,    84,     6,     7,   102,    73,
      74,     8,    75,     1,     9,   119,   125,   121,   126,   127,
       2,     3,     4,     5,   118,   129,     6,     7,     1,   113,
     114,     8,    89,    90,     9,     2,     3,     4,     5,   130,
      79,     6,     7,     1,    95,    96,     8,    31,    52,     9,
       2,     3,     4,     5,     0,   108,     6,     7,     1,     0,
       0,     8,     0,   115,     9,     2,     3,     4,     5,     0,
       0,     6,     7,     0,     0,   128,     8,     0,     0,     9,
       2,     3,     4,     5,     0,     0,     6,     7,     0,     0,
       0,     8,     0,     0,     9
};

static const yytype_int8 yycheck[] =
{
       0,    10,     2,     3,     4,    21,    39,     3,     3,     9,
      10,    23,    24,    16,     6,     7,     8,    23,    24,    23,
      24,    21,    25,    26,     3,    37,     0,    33,    14,     3,
      16,     3,    24,    29,    29,    16,    11,    23,    24,     4,
      73,    74,    75,    11,    25,    26,    55,    17,    40,    17,
       3,    25,    26,    27,    28,    55,    14,    31,    32,     3,
      76,    77,    36,    40,    56,    39,     3,     4,     5,     6,
      62,     8,    14,    16,    16,    15,    76,    77,    15,    16,
      23,    24,     3,     4,     5,     6,   102,     8,    15,    18,
      17,   100,   101,     3,    15,     7,     8,   113,     3,     3,
     100,   101,   102,    19,    20,    21,    22,   116,    67,    68,
      69,    70,    14,   113,    16,   124,   116,   109,     3,   111,
      25,    26,    27,    28,   124,    15,    31,    32,     4,     9,
      10,    36,    12,     3,    39,    14,    41,    16,    25,    26,
      25,    26,    27,    28,     3,     3,    31,    32,     3,    34,
      35,    36,    65,    66,    39,    25,    26,    27,    28,     3,
      30,    31,    32,     3,    71,    72,    36,     3,     9,    39,
      25,    26,    27,    28,    -1,    84,    31,    32,     3,    -1,
      -1,    36,    -1,    38,    39,    25,    26,    27,    28,    -1,
      -1,    31,    32,    -1,    -1,    35,    36,    -1,    -1,    39,
      25,    26,    27,    28,    -1,    -1,    31,    32,    -1,    -1,
      -1,    36,    -1,    -1,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    25,    26,    27,    28,    31,    32,    36,    39,
      43,    44,    45,    46,    47,    48,    49,    51,    52,    53,
      54,    55,    56,    60,    11,    17,     3,    29,    50,    60,
      29,    50,    60,     3,    60,     3,     4,     5,     6,     8,
      15,    57,    60,    61,    62,    63,    64,    65,    66,    61,
      61,    61,    51,     0,    44,    43,    11,    61,     4,     3,
      14,     3,    15,    65,    61,    23,    24,    19,    20,    21,
      22,     7,     8,     9,    10,    12,    33,    37,    40,    30,
      61,    18,    15,     3,    15,    16,    59,    61,    16,    62,
      62,    63,    63,    63,    63,    64,    64,    65,    65,    65,
      43,    43,     4,    16,    25,    26,    58,    16,    58,    14,
      16,    14,    16,    34,    35,    38,    43,     3,     3,    14,
      16,    16,    61,    61,    43,    41,    25,    26,    35,     3,
       3
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    43,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    45,    45,    46,    47,    48,    48,
      49,    49,    50,    50,    51,    51,    52,    52,    53,    54,
      55,    55,    55,    55,    56,    57,    57,    57,    58,    58,
      58,    58,    59,    59,    60,    61,    61,    61,    62,    62,
      62,    62,    62,    63,    63,    63,    64,    64,    64,    64,
      65,    65,    66,    66,    66,    66,    66,    66,    66
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     7,     5,     6,     2,     2,
       2,     2,     1,     3,     3,     3,     2,     2,     2,     2,
       6,     6,     5,     5,     3,     4,     4,     3,     2,     2,
       4,     4,     3,     3,     4,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     1,     3,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 24: /* assig_stmt: VAR EQUALS exp  */
#line 56 "PseudocodeCompiler.y"
                           { yyval = yyvsp[0]; }
#line 1314 "PseudocodeCompiler.tab.c"
    break;

  case 28: /* output_stmt: OUTPUT exp  */
#line 61 "PseudocodeCompiler.y"
                        { printf("VALOR -> %g\n", yyvsp[0]); }
#line 1320 "PseudocodeCompiler.tab.c"
    break;

  case 47: /* exp: term  */
#line 84 "PseudocodeCompiler.y"
          { yyval = yyvsp[0]; }
#line 1326 "PseudocodeCompiler.tab.c"
    break;

  case 52: /* term: exp_arit  */
#line 89 "PseudocodeCompiler.y"
               { yyval = yyvsp[0]; }
#line 1332 "PseudocodeCompiler.tab.c"
    break;

  case 53: /* exp_arit: exp_arit PLUS term_arit1  */
#line 90 "PseudocodeCompiler.y"
                                   { yyval = yyvsp[-2] + yyvsp[0]; }
#line 1338 "PseudocodeCompiler.tab.c"
    break;

  case 54: /* exp_arit: exp_arit MINUS term_arit1  */
#line 91 "PseudocodeCompiler.y"
                                    { yyval = yyvsp[-2] - yyvsp[0]; }
#line 1344 "PseudocodeCompiler.tab.c"
    break;

  case 55: /* exp_arit: term_arit1  */
#line 92 "PseudocodeCompiler.y"
                     { yyval = yyvsp[0]; }
#line 1350 "PseudocodeCompiler.tab.c"
    break;

  case 56: /* term_arit1: term_arit1 TIMES term_arit2  */
#line 93 "PseudocodeCompiler.y"
                                        { yyval = yyvsp[-2] * yyvsp[0]; }
#line 1356 "PseudocodeCompiler.tab.c"
    break;

  case 57: /* term_arit1: term_arit1 DIVIDE term_arit2  */
#line 94 "PseudocodeCompiler.y"
                                         { yyval = yyvsp[-2] / yyvsp[0]; }
#line 1362 "PseudocodeCompiler.tab.c"
    break;

  case 58: /* term_arit1: term_arit1 PERCENT term_arit2  */
#line 95 "PseudocodeCompiler.y"
                                          { yyval = (int)yyvsp[-2] % (int)yyvsp[0]; }
#line 1368 "PseudocodeCompiler.tab.c"
    break;

  case 59: /* term_arit1: term_arit2  */
#line 96 "PseudocodeCompiler.y"
                       { yyval = yyvsp[0]; }
#line 1374 "PseudocodeCompiler.tab.c"
    break;

  case 60: /* term_arit2: MINUS term_arit2  */
#line 97 "PseudocodeCompiler.y"
                                          { yyval = -yyvsp[0]; }
#line 1380 "PseudocodeCompiler.tab.c"
    break;

  case 61: /* term_arit2: term_arit3  */
#line 98 "PseudocodeCompiler.y"
                       { yyval = yyvsp[0]; }
#line 1386 "PseudocodeCompiler.tab.c"
    break;

  case 62: /* term_arit3: LPAREN exp RPAREN  */
#line 99 "PseudocodeCompiler.y"
                              { yyval = yyvsp[-1]; }
#line 1392 "PseudocodeCompiler.tab.c"
    break;


#line 1396 "PseudocodeCompiler.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 106 "PseudocodeCompiler.y"


void yyerror(char *msg) {
  printf("error: %s", msg);
}

int IsReservedWord(char lexema[], int default_token) {
  //strcmp considera mayusculas y minusculas
  //strcasecmp ignora mayusculas de minusculas
  if(strcmp(lexema,"ENTERO") == 0) return INT;
  if(strcmp(lexema,"DECIMAL") == 0) return DOUBLE;
  if(strcmp(lexema,"ENTRADA") == 0) return INPUT;
  if(strcmp(lexema,"SALIDA") == 0) return OUTPUT;
  if(strcmp(lexema,"SUBRUTINA") == 0) return SUBROUTINE;
  if(strcmp(lexema,"FINSUBRUTINA") == 0) return ENDSUBROUTINE;
  if(strcmp(lexema,"DEVOLVER") == 0) return RETURN;
  if(strcmp(lexema,"SI") == 0) return IF;
  if(strcmp(lexema,"ENTONCES") == 0) return THEN;
  if(strcmp(lexema,"SINO") == 0) return ELSE;
  if(strcmp(lexema,"FINSI") == 0) return ENDIF;
  if(strcmp(lexema,"MIENTRAS") == 0) return WHILE;
  if(strcmp(lexema,"HACER") == 0) return DO;
  if(strcmp(lexema,"FINMIENTRAS") == 0) return ENDWHILE;
  if(strcmp(lexema,"PARA") == 0) return FOR;
  if(strcmp(lexema,"HASTA") == 0) return TO;
  if(strcmp(lexema,"FINPARA") == 0) return ENDFOR;
  return default_token;
}

int yylex() {
  char c;
  while(1) {
    c = getchar();

    if(isspace(c)) continue;

    if(c == '+') return PLUS;
    if(c == '-') return MINUS;
    if(c == '*') return TIMES;
    if(c == '/') return DIVIDE;
    if(c == '=') return EQUALS;
    if(c == '%') return PERCENT;

    if(c == '<') return LESSTHAN;
    if(c == '>') return GREATERTHAN;

    char LESS_EQUAL[] = "<=";
    if(c == LESS_EQUAL[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == LESS_EQUAL[j] && j < 2);
      if(j == 2) {
        ungetc(c, stdin);
        lexema[i] = '\0';
        return LESSEQUAL;
      }
    }

    char GREATER_EQUAL[] = ">=";
    if(c == GREATER_EQUAL[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == GREATER_EQUAL[j] && j < 2);
      if(j == 2) {
        ungetc(c, stdin);
        lexema[i] = '\0';
        return GREATEREQUAL;
      }
    }

    char EQUALITYT[] = "==";
    if(c == EQUALITYT[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == EQUALITYT[j] && j < 2);
      if(j == 2) {
        ungetc(c, stdin);
        lexema[i] = '\0';
        return EQUALITY;
      }
    }

    char NOTEQUALITYT[] = "<>";
    if(c == NOTEQUALITYT[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == NOTEQUALITYT[j] && j < 2);
      if(j == 2) {
        ungetc(c, stdin);
        lexema[i] = '\0';
        return NOTEQUALITY;
      }
    }

    if(c == '(') return LPAREN;
    if(c == ')') return RPAREN;
    if(c == '[') return LBRACKET;
    if(c == ']') return RBRACKET;

    if(c == ',') return COMMA;

    if(c == 34) {
      int i = 0;
      do {
        lexema[i++] = c;
        c = getchar();
      } while(c != 34);
      if(c == 34) {
        lexema[i++] = c;
        c = getchar();
      }
      ungetc(c, stdin);
      lexema[i] = '\0';
      return STRINGCONST;
    }

    if(isalpha(c) || c == '_'){
      int i = 0;
      do {
        lexema[i++] = c;
        c = getchar();
      } while(isalnum(c) || c == '_');
      ungetc(c, stdin);
      lexema[i] = '\0';
      return IsReservedWord(lexema, VAR);
    }

    if(isdigit(c)) {
      int i = 0;
      do {
        lexema[i++] = c;
        c = getchar();
      } while(isdigit(c));
      if(c == '.') {
        lexema[i++] = c;
        c = getchar();
        if(isdigit(c)) {
          do {
            lexema[i++] = c;
            c = getchar();
          } while(isdigit(c));
          ungetc(c, stdin);
          lexema[i] = '\0';
          yylval = atof(lexema);
          return DOUBLECONST;
        }
        ungetc(c, stdin);
        lexema[i] = '\0';
        yylval = atof(lexema);
        return DOUBLECONST;
      }
      ungetc(c, stdin);
      lexema[i] = '\0';
      yylval = atoi(lexema);
      return INTCONST;
    }

    return c;
  }
}

int main() {
  return yyparse();
  // if(!yyparse()) printf("cadena valida\n");
  // else printf("\ncadena invalida\n");
  // return 0;
}
