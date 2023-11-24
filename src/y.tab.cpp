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
#line 1 "parser.yacc"

#include <stdio.h>
#include "TeaplAst.h"

extern A_pos pos;
extern A_program root;

extern int yylex(void);
extern "C"{
extern void yyerror(char *s); 
extern int  line,col;
extern int  yywrap();
}


#line 87 "y.tab.cpp"

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

#include "y.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ADD = 3,                        /* ADD  */
  YYSYMBOL_SUB = 4,                        /* SUB  */
  YYSYMBOL_MUL = 5,                        /* MUL  */
  YYSYMBOL_DIV = 6,                        /* DIV  */
  YYSYMBOL_LT = 7,                         /* LT  */
  YYSYMBOL_LE = 8,                         /* LE  */
  YYSYMBOL_GT = 9,                         /* GT  */
  YYSYMBOL_GE = 10,                        /* GE  */
  YYSYMBOL_EQ = 11,                        /* EQ  */
  YYSYMBOL_NE = 12,                        /* NE  */
  YYSYMBOL_AND = 13,                       /* AND  */
  YYSYMBOL_OR = 14,                        /* OR  */
  YYSYMBOL_NOT = 15,                       /* NOT  */
  YYSYMBOL_COLON = 16,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 17,                 /* SEMICOLON  */
  YYSYMBOL_RIGHTARR = 18,                  /* RIGHTARR  */
  YYSYMBOL_ASSIGN = 19,                    /* ASSIGN  */
  YYSYMBOL_DOT = 20,                       /* DOT  */
  YYSYMBOL_COMMA = 21,                     /* COMMA  */
  YYSYMBOL_LPAR = 22,                      /* LPAR  */
  YYSYMBOL_RPAR = 23,                      /* RPAR  */
  YYSYMBOL_LSQR = 24,                      /* LSQR  */
  YYSYMBOL_RSQR = 25,                      /* RSQR  */
  YYSYMBOL_LBRA = 26,                      /* LBRA  */
  YYSYMBOL_RBRA = 27,                      /* RBRA  */
  YYSYMBOL_BREAK = 28,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 29,                  /* CONTINUE  */
  YYSYMBOL_WHILE = 30,                     /* WHILE  */
  YYSYMBOL_IF = 31,                        /* IF  */
  YYSYMBOL_ELSE = 32,                      /* ELSE  */
  YYSYMBOL_RETURN = 33,                    /* RETURN  */
  YYSYMBOL_FN = 34,                        /* FN  */
  YYSYMBOL_STRUCT = 35,                    /* STRUCT  */
  YYSYMBOL_LET = 36,                       /* LET  */
  YYSYMBOL_INT = 37,                       /* INT  */
  YYSYMBOL_ID = 38,                        /* ID  */
  YYSYMBOL_NUM = 39,                       /* NUM  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_Program = 41,                   /* Program  */
  YYSYMBOL_ProgramElementList = 42,        /* ProgramElementList  */
  YYSYMBOL_ProgramElement = 43,            /* ProgramElement  */
  YYSYMBOL_FnDeclStmt = 44,                /* FnDeclStmt  */
  YYSYMBOL_CodeBlockStmt = 45,             /* CodeBlockStmt  */
  YYSYMBOL_ReturnStmt = 46,                /* ReturnStmt  */
  YYSYMBOL_CallStmt = 47,                  /* CallStmt  */
  YYSYMBOL_WhileStmt = 48,                 /* WhileStmt  */
  YYSYMBOL_IfStmt = 49,                    /* IfStmt  */
  YYSYMBOL_FnDef = 50,                     /* FnDef  */
  YYSYMBOL_CodeBlockStmtList = 51,         /* CodeBlockStmtList  */
  YYSYMBOL_ParamDecl = 52,                 /* ParamDecl  */
  YYSYMBOL_FnDecl = 53,                    /* FnDecl  */
  YYSYMBOL_StructDef = 54,                 /* StructDef  */
  YYSYMBOL_VarDeclList = 55,               /* VarDeclList  */
  YYSYMBOL_VarDeclStmt = 56,               /* VarDeclStmt  */
  YYSYMBOL_VarDef = 57,                    /* VarDef  */
  YYSYMBOL_VarDefArray = 58,               /* VarDefArray  */
  YYSYMBOL_VarDefScalar = 59,              /* VarDefScalar  */
  YYSYMBOL_VarDecl = 60,                   /* VarDecl  */
  YYSYMBOL_VarDeclArray = 61,              /* VarDeclArray  */
  YYSYMBOL_VarDeclScalar = 62,             /* VarDeclScalar  */
  YYSYMBOL_AssignStmt = 63,                /* AssignStmt  */
  YYSYMBOL_LeftVal = 64,                   /* LeftVal  */
  YYSYMBOL_RightVal = 65,                  /* RightVal  */
  YYSYMBOL_BoolUnit = 66,                  /* BoolUnit  */
  YYSYMBOL_ComExpr = 67,                   /* ComExpr  */
  YYSYMBOL_BoolExpr = 68,                  /* BoolExpr  */
  YYSYMBOL_BoolUOpExpr = 69,               /* BoolUOpExpr  */
  YYSYMBOL_BoolBiOpExpr = 70,              /* BoolBiOpExpr  */
  YYSYMBOL_ArithExpr = 71,                 /* ArithExpr  */
  YYSYMBOL_ArithUExpr = 72,                /* ArithUExpr  */
  YYSYMBOL_ArithBiOpExpr = 73,             /* ArithBiOpExpr  */
  YYSYMBOL_ExprUnit = 74,                  /* ExprUnit  */
  YYSYMBOL_MemberExpr = 75,                /* MemberExpr  */
  YYSYMBOL_ArrayExpr = 76,                 /* ArrayExpr  */
  YYSYMBOL_IndexExpr = 77,                 /* IndexExpr  */
  YYSYMBOL_FnCall = 78,                    /* FnCall  */
  YYSYMBOL_RightValList = 79,              /* RightValList  */
  YYSYMBOL_Type = 80                       /* Type  */
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
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   192

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  173

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   152,   152,   159,   164,   169,   173,   177,   181,   185,
     191,   197,   201,   205,   209,   213,   217,   221,   225,   229,
     235,   239,   245,   251,   257,   261,   267,   273,   277,   282,
     287,   293,   297,   303,   309,   313,   318,   323,   327,   333,
     337,   343,   350,   356,   360,   366,   372,   378,   384,   388,
     392,   398,   402,   408,   412,   416,   423,   427,   431,   435,
     439,   443,   450,   454,   460,   468,   472,   478,   482,   488,
     494,   498,   502,   506,   514,   518,   522,   526,   530,   534,
     538,   545,   551,   557,   561,   567,   573,   577,   582,   587,
     591
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
  "\"end of file\"", "error", "\"invalid token\"", "ADD", "SUB", "MUL",
  "DIV", "LT", "LE", "GT", "GE", "EQ", "NE", "AND", "OR", "NOT", "COLON",
  "SEMICOLON", "RIGHTARR", "ASSIGN", "DOT", "COMMA", "LPAR", "RPAR",
  "LSQR", "RSQR", "LBRA", "RBRA", "BREAK", "CONTINUE", "WHILE", "IF",
  "ELSE", "RETURN", "FN", "STRUCT", "LET", "INT", "ID", "NUM", "$accept",
  "Program", "ProgramElementList", "ProgramElement", "FnDeclStmt",
  "CodeBlockStmt", "ReturnStmt", "CallStmt", "WhileStmt", "IfStmt",
  "FnDef", "CodeBlockStmtList", "ParamDecl", "FnDecl", "StructDef",
  "VarDeclList", "VarDeclStmt", "VarDef", "VarDefArray", "VarDefScalar",
  "VarDecl", "VarDeclArray", "VarDeclScalar", "AssignStmt", "LeftVal",
  "RightVal", "BoolUnit", "ComExpr", "BoolExpr", "BoolUOpExpr",
  "BoolBiOpExpr", "ArithExpr", "ArithUExpr", "ArithBiOpExpr", "ExprUnit",
  "MemberExpr", "ArrayExpr", "IndexExpr", "FnCall", "RightValList", "Type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-143)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-51)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      75,  -143,   -27,    -8,    -2,    50,  -143,    75,  -143,  -143,
      -7,  -143,  -143,    23,    35,    -1,    46,  -143,  -143,    51,
    -143,  -143,  -143,  -143,  -143,     4,    48,    48,   -13,    56,
    -143,  -143,  -143,    98,   107,    79,   119,    45,   121,     4,
    -143,  -143,  -143,  -143,   123,  -143,  -143,    80,  -143,  -143,
     129,    15,   125,  -143,   139,   134,  -143,  -143,   143,   138,
    -143,  -143,    81,    81,    83,    81,  -143,    81,   120,  -143,
      24,   147,  -143,  -143,   104,  -143,  -143,   124,  -143,  -143,
     145,    82,    92,  -143,    81,  -143,  -143,    81,   127,    55,
    -143,   -13,   128,   148,    48,  -143,    81,   152,    33,   145,
      84,    83,  -143,  -143,   100,    85,  -143,    81,    81,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,   149,
     146,   154,  -143,  -143,  -143,   150,  -143,   151,   -13,  -143,
    -143,   -13,   155,   156,  -143,  -143,  -143,   104,   104,   153,
     153,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,    81,
    -143,  -143,  -143,   157,  -143,   158,     4,     4,  -143,   -13,
     159,   160,   161,  -143,    81,  -143,   140,   162,   164,  -143,
       4,   165,  -143
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     9,     0,     0,     0,     0,     2,     4,     7,     8,
       0,     6,     5,     0,     0,     0,     0,    40,    39,     0,
      44,    43,     1,     3,    10,    29,    36,    36,     0,     0,
      38,    37,    19,     0,     0,     0,     0,     0,    50,    28,
      16,    13,    15,    14,     0,    11,    12,     0,    49,    48,
       0,     0,     0,    30,    35,     0,    89,    90,    46,     0,
      18,    17,     0,     0,     0,     0,    21,     0,    74,    75,
       0,     0,    63,    53,    52,    55,    62,    51,    80,    67,
      68,    79,    78,    77,    88,    27,    26,     0,     0,     0,
      22,     0,     0,    32,    36,    33,     0,     0,     0,     0,
       0,     0,    69,    64,     0,     0,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    87,
       0,     0,    81,    84,    83,     0,    46,     0,     0,    34,
      42,     0,     0,     0,    68,    54,    76,    65,    66,    70,
      71,    72,    73,    56,    57,    58,    59,    60,    61,    88,
      85,    47,    82,     0,    31,    45,    29,    29,    86,     0,
       0,     0,     0,    45,    88,    23,    24,     0,     0,    41,
      29,     0,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -143,  -143,   167,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,   -31,  -143,  -143,  -143,   -24,    59,  -143,  -143,  -143,
     174,  -143,  -143,  -143,   -25,   -32,   114,  -143,   -50,  -143,
    -143,   -58,  -143,  -143,   -36,   -23,   -21,  -143,   -19,  -142,
     -90
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    39,    40,    41,    42,    43,
       9,    44,    52,    10,    11,    53,    45,    16,    17,    18,
      54,    20,    21,    46,    70,   119,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,   125,    83,   120,
      58
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,   126,    48,    55,    49,    71,    50,   158,    85,   105,
      24,    13,    98,   100,    47,    28,    48,   104,    49,    25,
      50,    32,   167,    29,    56,    57,    99,    99,   102,    99,
      14,    91,    33,    34,    35,    36,    15,    37,   154,    92,
       4,   155,    38,   105,    88,    26,   107,   108,    89,    64,
      22,   139,   140,   141,   142,   121,   132,   137,   138,    12,
      65,    27,    66,    30,   130,   134,    12,    67,    31,   163,
     129,    99,    99,   134,   134,   134,   134,   143,   144,   145,
     146,   147,   148,    68,    69,    64,    51,    64,   109,   110,
     111,   112,     1,   123,   124,    59,    65,   107,   108,    87,
      88,    62,   -49,    67,    89,   101,   -49,   133,   136,     2,
       3,     4,   -48,   107,   108,    60,   -48,   107,   108,    68,
      69,    68,    69,   135,    61,   161,   162,   109,   110,   111,
     112,    47,    47,    48,    48,    49,    49,    50,    50,   171,
     -50,    63,    84,    84,   -50,    47,    90,    48,    93,    49,
      86,    50,   113,   114,   115,   116,   117,   118,   111,   112,
      94,    95,    96,    97,   106,   122,   128,   127,   131,   150,
     149,   151,   168,   159,    23,   152,   153,   160,    19,   103,
       0,   156,   157,     0,     0,   164,     0,   165,   166,   169,
     170,     0,   172
};

static const yytype_int16 yycheck[] =
{
      25,    91,    25,    27,    25,    37,    25,   149,    39,    67,
      17,    38,    62,    63,    39,    16,    39,    67,    39,    26,
      39,    17,   164,    24,    37,    38,    62,    63,    64,    65,
      38,    16,    28,    29,    30,    31,    38,    33,   128,    24,
      36,   131,    38,   101,    20,    22,    13,    14,    24,     4,
       0,   109,   110,   111,   112,    87,    23,   107,   108,     0,
      15,    26,    17,    17,    96,   101,     7,    22,    17,   159,
      94,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,    38,    39,     4,    38,     4,     3,     4,
       5,     6,    17,    38,    39,    39,    15,    13,    14,    19,
      20,    22,    20,    22,    24,    22,    24,    23,    23,    34,
      35,    36,    20,    13,    14,    17,    24,    13,    14,    38,
      39,    38,    39,    23,    17,   156,   157,     3,     4,     5,
       6,   156,   157,   156,   157,   156,   157,   156,   157,   170,
      20,    22,    22,    22,    24,   170,    17,   170,    23,   170,
      27,   170,     7,     8,     9,    10,    11,    12,     5,     6,
      21,    27,    19,    25,    17,    38,    18,    39,    16,    23,
      21,    17,    32,    16,     7,    25,    25,    19,     4,    65,
      -1,    26,    26,    -1,    -1,    26,    -1,    27,    27,    27,
      26,    -1,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    17,    34,    35,    36,    41,    42,    43,    44,    50,
      53,    54,    56,    38,    38,    38,    57,    58,    59,    60,
      61,    62,     0,    42,    17,    26,    22,    26,    16,    24,
      17,    17,    17,    28,    29,    30,    31,    33,    38,    45,
      46,    47,    48,    49,    51,    56,    63,    64,    75,    76,
      78,    38,    52,    55,    60,    55,    37,    38,    80,    39,
      17,    17,    22,    22,     4,    15,    17,    22,    38,    39,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    78,    22,    51,    27,    19,    20,    24,
      17,    16,    24,    23,    21,    27,    19,    25,    68,    74,
      68,    22,    74,    66,    68,    71,    17,    13,    14,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    65,
      79,    65,    38,    38,    39,    77,    80,    39,    18,    55,
      65,    16,    23,    23,    74,    23,    23,    68,    68,    71,
      71,    71,    71,    74,    74,    74,    74,    74,    74,    21,
      23,    17,    25,    25,    80,    80,    26,    26,    79,    16,
      19,    51,    51,    80,    26,    27,    27,    79,    32,    27,
      26,    51,    27
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      44,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      46,    46,    47,    48,    49,    49,    50,    51,    51,    51,
      52,    53,    53,    54,    55,    55,    55,    56,    56,    57,
      57,    58,    59,    60,    60,    61,    62,    63,    64,    64,
      64,    65,    65,    66,    66,    66,    67,    67,    67,    67,
      67,    67,    68,    68,    69,    70,    70,    71,    71,    72,
      73,    73,    73,    73,    74,    74,    74,    74,    74,    74,
      74,    75,    76,    77,    77,    78,    79,    79,    79,    80,
      80
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       3,     2,     2,     7,     7,    11,     4,     2,     1,     0,
       1,     7,     5,     5,     3,     1,     0,     3,     3,     1,
       1,    10,     5,     1,     1,     6,     3,     4,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     1,     1,     2,     3,     3,     1,     1,     2,
       3,     3,     3,     3,     1,     1,     3,     1,     1,     1,
       1,     3,     4,     1,     1,     4,     3,     1,     0,     1,
       1
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
  case 2: /* Program: ProgramElementList  */
#line 153 "parser.yacc"
{  
  root = A_Program((yyvsp[0].programElementList));
  (yyval.program) = A_Program((yyvsp[0].programElementList));
}
#line 1282 "y.tab.cpp"
    break;

  case 3: /* ProgramElementList: ProgramElement ProgramElementList  */
#line 160 "parser.yacc"
{
  (yyval.programElementList) = A_ProgramElementList((yyvsp[-1].programElement), (yyvsp[0].programElementList));
}
#line 1290 "y.tab.cpp"
    break;

  case 4: /* ProgramElementList: %empty  */
#line 164 "parser.yacc"
{
  (yyval.programElementList) = NULL;
}
#line 1298 "y.tab.cpp"
    break;

  case 5: /* ProgramElement: VarDeclStmt  */
#line 170 "parser.yacc"
{
  (yyval.programElement) = A_ProgramVarDeclStmt((yyvsp[0].varDeclStmt)->pos, (yyvsp[0].varDeclStmt));
}
#line 1306 "y.tab.cpp"
    break;

  case 6: /* ProgramElement: StructDef  */
#line 174 "parser.yacc"
{
  (yyval.programElement) = A_ProgramStructDef((yyvsp[0].structDef)->pos, (yyvsp[0].structDef));
}
#line 1314 "y.tab.cpp"
    break;

  case 7: /* ProgramElement: FnDeclStmt  */
#line 178 "parser.yacc"
{
  (yyval.programElement) = A_ProgramFnDeclStmt((yyvsp[0].fnDeclStmt)->pos, (yyvsp[0].fnDeclStmt));
}
#line 1322 "y.tab.cpp"
    break;

  case 8: /* ProgramElement: FnDef  */
#line 182 "parser.yacc"
{
  (yyval.programElement) = A_ProgramFnDef((yyvsp[0].fnDef)->pos, (yyvsp[0].fnDef));
}
#line 1330 "y.tab.cpp"
    break;

  case 9: /* ProgramElement: SEMICOLON  */
#line 186 "parser.yacc"
{
  (yyval.programElement) = A_ProgramNullStmt((yyvsp[0].pos));
}
#line 1338 "y.tab.cpp"
    break;

  case 10: /* FnDeclStmt: FnDecl SEMICOLON  */
#line 192 "parser.yacc"
{
  (yyval.fnDeclStmt)=A_FnDeclStmt((yyvsp[-1].fnDecl)->pos,(yyvsp[-1].fnDecl));
}
#line 1346 "y.tab.cpp"
    break;

  case 11: /* CodeBlockStmt: VarDeclStmt  */
#line 198 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockVarDeclStmt((yyvsp[0].varDeclStmt)->pos, (yyvsp[0].varDeclStmt));
}
#line 1354 "y.tab.cpp"
    break;

  case 12: /* CodeBlockStmt: AssignStmt  */
#line 202 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockAssignStmt((yyvsp[0].assignStmt)->pos, (yyvsp[0].assignStmt));
}
#line 1362 "y.tab.cpp"
    break;

  case 13: /* CodeBlockStmt: CallStmt  */
#line 206 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockCallStmt((yyvsp[0].callStmt)->pos, (yyvsp[0].callStmt));
}
#line 1370 "y.tab.cpp"
    break;

  case 14: /* CodeBlockStmt: IfStmt  */
#line 210 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockIfStmt((yyvsp[0].ifStmt)->pos, (yyvsp[0].ifStmt));
}
#line 1378 "y.tab.cpp"
    break;

  case 15: /* CodeBlockStmt: WhileStmt  */
#line 214 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockWhileStmt((yyvsp[0].whileStmt)->pos, (yyvsp[0].whileStmt));
}
#line 1386 "y.tab.cpp"
    break;

  case 16: /* CodeBlockStmt: ReturnStmt  */
#line 218 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockReturnStmt((yyvsp[0].returnStmt)->pos, (yyvsp[0].returnStmt));
}
#line 1394 "y.tab.cpp"
    break;

  case 17: /* CodeBlockStmt: CONTINUE SEMICOLON  */
#line 222 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockContinueStmt((yyvsp[-1].pos));
}
#line 1402 "y.tab.cpp"
    break;

  case 18: /* CodeBlockStmt: BREAK SEMICOLON  */
#line 226 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockBreakStmt((yyvsp[-1].pos));
}
#line 1410 "y.tab.cpp"
    break;

  case 19: /* CodeBlockStmt: SEMICOLON  */
#line 230 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockNullStmt((yyvsp[0].pos));
}
#line 1418 "y.tab.cpp"
    break;

  case 20: /* ReturnStmt: RETURN RightVal SEMICOLON  */
#line 236 "parser.yacc"
{
  (yyval.returnStmt)=A_ReturnStmt((yyvsp[-2].pos), (yyvsp[-1].rightVal));
}
#line 1426 "y.tab.cpp"
    break;

  case 21: /* ReturnStmt: RETURN SEMICOLON  */
#line 240 "parser.yacc"
{
  (yyval.returnStmt)=A_ReturnStmt((yyvsp[-1].pos), NULL);
}
#line 1434 "y.tab.cpp"
    break;

  case 22: /* CallStmt: FnCall SEMICOLON  */
#line 246 "parser.yacc"
{
  (yyval.callStmt)=A_CallStmt((yyvsp[-1].fnCall)->pos, (yyvsp[-1].fnCall));
}
#line 1442 "y.tab.cpp"
    break;

  case 23: /* WhileStmt: WHILE LPAR BoolExpr RPAR LBRA CodeBlockStmtList RBRA  */
#line 252 "parser.yacc"
{
  (yyval.whileStmt)=A_WhileStmt((yyvsp[-6].pos), (yyvsp[-4].boolExpr), (yyvsp[-1].codeBlockStmtList));
}
#line 1450 "y.tab.cpp"
    break;

  case 24: /* IfStmt: IF LPAR BoolExpr RPAR LBRA CodeBlockStmtList RBRA  */
#line 258 "parser.yacc"
{
  (yyval.ifStmt)=A_IfStmt((yyvsp[-6].pos), (yyvsp[-4].boolExpr), (yyvsp[-1].codeBlockStmtList), NULL);
}
#line 1458 "y.tab.cpp"
    break;

  case 25: /* IfStmt: IF LPAR BoolExpr RPAR LBRA CodeBlockStmtList RBRA ELSE LBRA CodeBlockStmtList RBRA  */
#line 262 "parser.yacc"
{
  (yyval.ifStmt)=A_IfStmt((yyvsp[-10].pos), (yyvsp[-8].boolExpr), (yyvsp[-5].codeBlockStmtList), (yyvsp[-1].codeBlockStmtList));
}
#line 1466 "y.tab.cpp"
    break;

  case 26: /* FnDef: FnDecl LBRA CodeBlockStmtList RBRA  */
#line 268 "parser.yacc"
{
  (yyval.fnDef) = A_FnDef((yyvsp[-3].fnDecl)->pos, (yyvsp[-3].fnDecl), (yyvsp[-1].codeBlockStmtList));
}
#line 1474 "y.tab.cpp"
    break;

  case 27: /* CodeBlockStmtList: CodeBlockStmt CodeBlockStmtList  */
#line 274 "parser.yacc"
{
  (yyval.codeBlockStmtList) = A_CodeBlockStmtList((yyvsp[-1].codeBlockStmt), (yyvsp[0].codeBlockStmtList));
}
#line 1482 "y.tab.cpp"
    break;

  case 28: /* CodeBlockStmtList: CodeBlockStmt  */
#line 278 "parser.yacc"
{
  (yyval.codeBlockStmtList) = A_CodeBlockStmtList((yyvsp[0].codeBlockStmt), NULL);
}
#line 1490 "y.tab.cpp"
    break;

  case 29: /* CodeBlockStmtList: %empty  */
#line 282 "parser.yacc"
{
  (yyval.codeBlockStmtList) = NULL;
}
#line 1498 "y.tab.cpp"
    break;

  case 30: /* ParamDecl: VarDeclList  */
#line 288 "parser.yacc"
{
  (yyval.paramDecl)=A_ParamDecl((yyvsp[0].varDeclList));
}
#line 1506 "y.tab.cpp"
    break;

  case 31: /* FnDecl: FN ID LPAR ParamDecl RPAR RIGHTARR Type  */
#line 294 "parser.yacc"
{
  (yyval.fnDecl)=A_FnDecl((yyvsp[-6].pos),(yyvsp[-5].tokenId)->id, (yyvsp[-3].paramDecl), (yyvsp[0].type));
}
#line 1514 "y.tab.cpp"
    break;

  case 32: /* FnDecl: FN ID LPAR ParamDecl RPAR  */
#line 298 "parser.yacc"
{
  (yyval.fnDecl)=A_FnDecl((yyvsp[-4].pos),(yyvsp[-3].tokenId)->id, (yyvsp[-1].paramDecl), NULL);
}
#line 1522 "y.tab.cpp"
    break;

  case 33: /* StructDef: STRUCT ID LBRA VarDeclList RBRA  */
#line 304 "parser.yacc"
{
  (yyval.structDef)=A_StructDef((yyvsp[-4].pos), (yyvsp[-3].tokenId)->id, (yyvsp[-1].varDeclList));
}
#line 1530 "y.tab.cpp"
    break;

  case 34: /* VarDeclList: VarDecl COMMA VarDeclList  */
#line 310 "parser.yacc"
{
  (yyval.varDeclList) = A_VarDeclList((yyvsp[-2].varDecl), (yyvsp[0].varDeclList));
}
#line 1538 "y.tab.cpp"
    break;

  case 35: /* VarDeclList: VarDecl  */
#line 314 "parser.yacc"
{
  (yyval.varDeclList)= A_VarDeclList((yyvsp[0].varDecl), NULL);
}
#line 1546 "y.tab.cpp"
    break;

  case 36: /* VarDeclList: %empty  */
#line 318 "parser.yacc"
{
  (yyval.varDeclList)=NULL;
}
#line 1554 "y.tab.cpp"
    break;

  case 37: /* VarDeclStmt: LET VarDecl SEMICOLON  */
#line 324 "parser.yacc"
{
  (yyval.varDeclStmt) = A_VarDeclStmt((yyvsp[-2].pos), (yyvsp[-1].varDecl));
}
#line 1562 "y.tab.cpp"
    break;

  case 38: /* VarDeclStmt: LET VarDef SEMICOLON  */
#line 328 "parser.yacc"
{
  (yyval.varDeclStmt) = A_VarDefStmt((yyvsp[-2].pos), (yyvsp[-1].varDef));
}
#line 1570 "y.tab.cpp"
    break;

  case 39: /* VarDef: VarDefScalar  */
#line 334 "parser.yacc"
{
  (yyval.varDef)=A_VarDef_Scalar((yyvsp[0].varDefScalar)->pos, (yyvsp[0].varDefScalar));
}
#line 1578 "y.tab.cpp"
    break;

  case 40: /* VarDef: VarDefArray  */
#line 338 "parser.yacc"
{
  (yyval.varDef)=A_VarDef_Array((yyvsp[0].varDefArray)->pos, (yyvsp[0].varDefArray));
}
#line 1586 "y.tab.cpp"
    break;

  case 41: /* VarDefArray: ID LSQR NUM RSQR COLON Type ASSIGN LBRA RightValList RBRA  */
#line 344 "parser.yacc"
{
  (yyval.varDefArray)=A_VarDefArray((yyvsp[-9].tokenId)->pos,(yyvsp[-9].tokenId)->id,(yyvsp[-7].tokenNum)->num, (yyvsp[-4].type), (yyvsp[-1].rightValList));

}
#line 1595 "y.tab.cpp"
    break;

  case 42: /* VarDefScalar: ID COLON Type ASSIGN RightVal  */
#line 351 "parser.yacc"
{
  (yyval.varDefScalar)=A_VarDefScalar((yyvsp[-4].tokenId)->pos, (yyvsp[-4].tokenId)->id, (yyvsp[-2].type) ,(yyvsp[0].rightVal));
}
#line 1603 "y.tab.cpp"
    break;

  case 43: /* VarDecl: VarDeclScalar  */
#line 357 "parser.yacc"
{
  (yyval.varDecl)=A_VarDecl_Scalar((yyvsp[0].varDeclScalar)->pos, (yyvsp[0].varDeclScalar));
}
#line 1611 "y.tab.cpp"
    break;

  case 44: /* VarDecl: VarDeclArray  */
#line 361 "parser.yacc"
{
  (yyval.varDecl)=A_VarDecl_Array((yyvsp[0].varDeclArray)->pos, (yyvsp[0].varDeclArray));
}
#line 1619 "y.tab.cpp"
    break;

  case 45: /* VarDeclArray: ID LSQR NUM RSQR COLON Type  */
#line 367 "parser.yacc"
{
  (yyval.varDeclArray)=A_VarDeclArray((yyvsp[-5].tokenId)->pos, (yyvsp[-5].tokenId)->id, (yyvsp[-3].tokenNum)->num, (yyvsp[0].type));
}
#line 1627 "y.tab.cpp"
    break;

  case 46: /* VarDeclScalar: ID COLON Type  */
#line 373 "parser.yacc"
{
  (yyval.varDeclScalar)=A_VarDeclScalar((yyvsp[-2].tokenId)->pos, (yyvsp[-2].tokenId)->id, (yyvsp[0].type));
}
#line 1635 "y.tab.cpp"
    break;

  case 47: /* AssignStmt: LeftVal ASSIGN RightVal SEMICOLON  */
#line 379 "parser.yacc"
{
  (yyval.assignStmt)=A_AssignStmt((yyvsp[-3].leftVal)->pos,(yyvsp[-3].leftVal),(yyvsp[-1].rightVal));
}
#line 1643 "y.tab.cpp"
    break;

  case 48: /* LeftVal: ArrayExpr  */
#line 385 "parser.yacc"
{
  (yyval.leftVal)=A_ArrExprLVal((yyvsp[0].arrayExpr)->pos, (yyvsp[0].arrayExpr));
}
#line 1651 "y.tab.cpp"
    break;

  case 49: /* LeftVal: MemberExpr  */
#line 389 "parser.yacc"
{
  (yyval.leftVal)=A_MemberExprLVal((yyvsp[0].memberExpr)->pos, (yyvsp[0].memberExpr));
}
#line 1659 "y.tab.cpp"
    break;

  case 50: /* LeftVal: ID  */
#line 393 "parser.yacc"
{
  (yyval.leftVal)=A_IdExprLVal((yyvsp[0].tokenId)->pos, (yyvsp[0].tokenId)->id);
}
#line 1667 "y.tab.cpp"
    break;

  case 51: /* RightVal: ArithExpr  */
#line 399 "parser.yacc"
{
  (yyval.rightVal)=A_ArithExprRVal((yyvsp[0].arithExpr)->pos,(yyvsp[0].arithExpr));
}
#line 1675 "y.tab.cpp"
    break;

  case 52: /* RightVal: BoolExpr  */
#line 403 "parser.yacc"
{
  (yyval.rightVal)=A_BoolExprRVal((yyvsp[0].boolExpr)->pos,(yyvsp[0].boolExpr));
}
#line 1683 "y.tab.cpp"
    break;

  case 53: /* BoolUnit: ComExpr  */
#line 409 "parser.yacc"
{
  (yyval.boolUnit)=A_ComExprUnit((yyvsp[0].comExpr)->pos, (yyvsp[0].comExpr));
}
#line 1691 "y.tab.cpp"
    break;

  case 54: /* BoolUnit: LPAR BoolExpr RPAR  */
#line 413 "parser.yacc"
{
  (yyval.boolUnit)=A_BoolExprUnit((yyvsp[-2].pos), (yyvsp[-1].boolExpr));
}
#line 1699 "y.tab.cpp"
    break;

  case 55: /* BoolUnit: BoolUOpExpr  */
#line 417 "parser.yacc"
{
  (yyval.boolUnit)=A_BoolUOpExprUnit((yyvsp[0].boolUOpExpr)->pos, (yyvsp[0].boolUOpExpr));
}
#line 1707 "y.tab.cpp"
    break;

  case 56: /* ComExpr: ExprUnit LT ExprUnit  */
#line 424 "parser.yacc"
{
  (yyval.comExpr)=A_ComExpr((yyvsp[-2].exprUnit)->pos,A_lt,(yyvsp[-2].exprUnit),(yyvsp[0].exprUnit));
}
#line 1715 "y.tab.cpp"
    break;

  case 57: /* ComExpr: ExprUnit LE ExprUnit  */
#line 428 "parser.yacc"
{
  (yyval.comExpr)=A_ComExpr((yyvsp[-2].exprUnit)->pos,A_le,(yyvsp[-2].exprUnit),(yyvsp[0].exprUnit));
}
#line 1723 "y.tab.cpp"
    break;

  case 58: /* ComExpr: ExprUnit GT ExprUnit  */
#line 432 "parser.yacc"
{
  (yyval.comExpr)=A_ComExpr((yyvsp[-2].exprUnit)->pos,A_gt,(yyvsp[-2].exprUnit),(yyvsp[0].exprUnit));
}
#line 1731 "y.tab.cpp"
    break;

  case 59: /* ComExpr: ExprUnit GE ExprUnit  */
#line 436 "parser.yacc"
{
  (yyval.comExpr)=A_ComExpr((yyvsp[-2].exprUnit)->pos,A_ge,(yyvsp[-2].exprUnit),(yyvsp[0].exprUnit));
}
#line 1739 "y.tab.cpp"
    break;

  case 60: /* ComExpr: ExprUnit EQ ExprUnit  */
#line 440 "parser.yacc"
{
  (yyval.comExpr)=A_ComExpr((yyvsp[-2].exprUnit)->pos,A_eq,(yyvsp[-2].exprUnit),(yyvsp[0].exprUnit));
}
#line 1747 "y.tab.cpp"
    break;

  case 61: /* ComExpr: ExprUnit NE ExprUnit  */
#line 444 "parser.yacc"
{
  (yyval.comExpr)=A_ComExpr((yyvsp[-2].exprUnit)->pos,A_ne,(yyvsp[-2].exprUnit),(yyvsp[0].exprUnit));
}
#line 1755 "y.tab.cpp"
    break;

  case 62: /* BoolExpr: BoolBiOpExpr  */
#line 451 "parser.yacc"
{
  (yyval.boolExpr)=A_BoolBiOp_Expr((yyvsp[0].boolBiOpExpr)->pos, (yyvsp[0].boolBiOpExpr));
}
#line 1763 "y.tab.cpp"
    break;

  case 63: /* BoolExpr: BoolUnit  */
#line 455 "parser.yacc"
{
  (yyval.boolExpr)=A_BoolExpr((yyvsp[0].boolUnit)->pos, (yyvsp[0].boolUnit));
}
#line 1771 "y.tab.cpp"
    break;

  case 64: /* BoolUOpExpr: NOT BoolUnit  */
#line 461 "parser.yacc"
{
  (yyval.boolUOpExpr)=A_BoolUOpExpr((yyvsp[-1].pos), A_not, (yyvsp[0].boolUnit));
}
#line 1779 "y.tab.cpp"
    break;

  case 65: /* BoolBiOpExpr: BoolExpr AND BoolExpr  */
#line 469 "parser.yacc"
{
  (yyval.boolBiOpExpr)=A_BoolBiOpExpr((yyvsp[-2].boolExpr)->pos,A_and,(yyvsp[-2].boolExpr),(yyvsp[0].boolExpr));
}
#line 1787 "y.tab.cpp"
    break;

  case 66: /* BoolBiOpExpr: BoolExpr OR BoolExpr  */
#line 473 "parser.yacc"
{
  (yyval.boolBiOpExpr)=A_BoolBiOpExpr((yyvsp[-2].boolExpr)->pos,A_or,(yyvsp[-2].boolExpr),(yyvsp[0].boolExpr));
}
#line 1795 "y.tab.cpp"
    break;

  case 67: /* ArithExpr: ArithBiOpExpr  */
#line 479 "parser.yacc"
{
  (yyval.arithExpr)=A_ArithBiOp_Expr((yyvsp[0].arithBiOpExpr)->pos, (yyvsp[0].arithBiOpExpr));
}
#line 1803 "y.tab.cpp"
    break;

  case 68: /* ArithExpr: ExprUnit  */
#line 483 "parser.yacc"
{
  (yyval.arithExpr) = A_ExprUnit((yyvsp[0].exprUnit)->pos, (yyvsp[0].exprUnit));
}
#line 1811 "y.tab.cpp"
    break;

  case 69: /* ArithUExpr: SUB ExprUnit  */
#line 489 "parser.yacc"
{
  (yyval.arithUExpr) = A_ArithUExpr((yyvsp[-1].pos),A_neg,(yyvsp[0].exprUnit));
}
#line 1819 "y.tab.cpp"
    break;

  case 70: /* ArithBiOpExpr: ArithExpr ADD ArithExpr  */
#line 495 "parser.yacc"
{
  (yyval.arithBiOpExpr) = A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, A_add, (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr));
}
#line 1827 "y.tab.cpp"
    break;

  case 71: /* ArithBiOpExpr: ArithExpr SUB ArithExpr  */
#line 499 "parser.yacc"
{
  (yyval.arithBiOpExpr) = A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, A_sub, (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr));
}
#line 1835 "y.tab.cpp"
    break;

  case 72: /* ArithBiOpExpr: ArithExpr MUL ArithExpr  */
#line 503 "parser.yacc"
{
  (yyval.arithBiOpExpr) = A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, A_mul, (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr));
}
#line 1843 "y.tab.cpp"
    break;

  case 73: /* ArithBiOpExpr: ArithExpr DIV ArithExpr  */
#line 507 "parser.yacc"
{
  (yyval.arithBiOpExpr) = A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, A_div, (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr));
}
#line 1851 "y.tab.cpp"
    break;

  case 74: /* ExprUnit: ID  */
#line 515 "parser.yacc"
{
  (yyval.exprUnit)=A_IdExprUnit((yyvsp[0].tokenId)->pos,(yyvsp[0].tokenId)->id);
}
#line 1859 "y.tab.cpp"
    break;

  case 75: /* ExprUnit: NUM  */
#line 519 "parser.yacc"
{
  (yyval.exprUnit)=A_NumExprUnit((yyvsp[0].tokenNum)->pos,(yyvsp[0].tokenNum)->num);
}
#line 1867 "y.tab.cpp"
    break;

  case 76: /* ExprUnit: LPAR ArithExpr RPAR  */
#line 523 "parser.yacc"
{
  (yyval.exprUnit)=A_ArithExprUnit((yyvsp[-2].pos), (yyvsp[-1].arithExpr));
}
#line 1875 "y.tab.cpp"
    break;

  case 77: /* ExprUnit: FnCall  */
#line 527 "parser.yacc"
{
  (yyval.exprUnit)=A_CallExprUnit((yyvsp[0].fnCall)->pos,(yyvsp[0].fnCall));
}
#line 1883 "y.tab.cpp"
    break;

  case 78: /* ExprUnit: ArrayExpr  */
#line 531 "parser.yacc"
{
  (yyval.exprUnit)=A_ArrayExprUnit((yyvsp[0].arrayExpr)->pos,(yyvsp[0].arrayExpr));
}
#line 1891 "y.tab.cpp"
    break;

  case 79: /* ExprUnit: MemberExpr  */
#line 535 "parser.yacc"
{
  (yyval.exprUnit)=A_MemberExprUnit((yyvsp[0].memberExpr)->pos,(yyvsp[0].memberExpr));
}
#line 1899 "y.tab.cpp"
    break;

  case 80: /* ExprUnit: ArithUExpr  */
#line 539 "parser.yacc"
{
  (yyval.exprUnit)=A_ArithUExprUnit((yyvsp[0].arithUExpr)->pos,(yyvsp[0].arithUExpr));
}
#line 1907 "y.tab.cpp"
    break;

  case 81: /* MemberExpr: LeftVal DOT ID  */
#line 546 "parser.yacc"
{
  (yyval.memberExpr)=A_MemberExpr((yyvsp[-2].leftVal)->pos, (yyvsp[-2].leftVal), (yyvsp[0].tokenId)->id);
}
#line 1915 "y.tab.cpp"
    break;

  case 82: /* ArrayExpr: LeftVal LSQR IndexExpr RSQR  */
#line 552 "parser.yacc"
{
  (yyval.arrayExpr)=A_ArrayExpr((yyvsp[-3].leftVal)->pos, (yyvsp[-3].leftVal), (yyvsp[-1].indexExpr));
}
#line 1923 "y.tab.cpp"
    break;

  case 83: /* IndexExpr: NUM  */
#line 558 "parser.yacc"
{
  (yyval.indexExpr)=A_NumIndexExpr((yyvsp[0].tokenNum)->pos, (yyvsp[0].tokenNum)->num);
}
#line 1931 "y.tab.cpp"
    break;

  case 84: /* IndexExpr: ID  */
#line 562 "parser.yacc"
{
  (yyval.indexExpr)=A_IdIndexExpr((yyvsp[0].tokenId)->pos, (yyvsp[0].tokenId)->id);
}
#line 1939 "y.tab.cpp"
    break;

  case 85: /* FnCall: ID LPAR RightValList RPAR  */
#line 568 "parser.yacc"
{
  (yyval.fnCall)=A_FnCall((yyvsp[-3].tokenId)->pos, (yyvsp[-3].tokenId)->id, (yyvsp[-1].rightValList));
}
#line 1947 "y.tab.cpp"
    break;

  case 86: /* RightValList: RightVal COMMA RightValList  */
#line 574 "parser.yacc"
{
  (yyval.rightValList)=A_RightValList((yyvsp[-2].rightVal), (yyvsp[0].rightValList));
}
#line 1955 "y.tab.cpp"
    break;

  case 87: /* RightValList: RightVal  */
#line 578 "parser.yacc"
{
  (yyval.rightValList)=A_RightValList((yyvsp[0].rightVal), NULL);
}
#line 1963 "y.tab.cpp"
    break;

  case 88: /* RightValList: %empty  */
#line 582 "parser.yacc"
{
  (yyval.rightValList)=NULL;
}
#line 1971 "y.tab.cpp"
    break;

  case 89: /* Type: INT  */
#line 588 "parser.yacc"
{
  (yyval.type)=A_NativeType((yyvsp[0].pos),A_intTypeKind);
}
#line 1979 "y.tab.cpp"
    break;

  case 90: /* Type: ID  */
#line 592 "parser.yacc"
{
  (yyval.type)=A_StructType((yyvsp[0].tokenId)->pos,(yyvsp[0].tokenId)->id);
}
#line 1987 "y.tab.cpp"
    break;


#line 1991 "y.tab.cpp"

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

#line 596 "parser.yacc"


extern "C"{
void yyerror(char * s)
{
  fprintf(stderr, "Error: %s in line %d, col %d\n",s,line,col);
}
int yywrap()
{
  return(1);
}
}
