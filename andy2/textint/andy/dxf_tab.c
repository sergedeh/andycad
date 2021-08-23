
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         dxfparse
#define yylex           dxflex
#define yyerror         dxferror
#define yylval          dxflval
#define yychar          dxfchar
#define yydebug         dxfdebug
#define yynerrs         dxfnerrs


/* Copy the first part of user declarations.  */


#include <malloc.h>
#define alloc _alloc
#include <stdio.h>
#include <vector>
using namespace std;


vector<CVector> dxfpvec;
CString _out,dxfcom;
CCadDoc* dxfpDoc;
CCadView *dxfpView;
CDC * dxfHdc;
bool dxfBlock=false;
CVector dxfcv;
int _token=-1;
int nbline=0,nbspline=0;
CStringArray sar;


yyerror (char* s)  /* Called by yyparse on error */
{
 // printf ("%s\n", s);
  CString f(s);
  sar.Add(_out+f);
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     HEADER_START = 258,
     HEADER_VAR = 259,
     SECTION_END = 260,
     EOL = 261,
     VAR_NAME = 262,
     VALUE = 263,
     GROUP_CODE = 264,
     TABLE_END = 265,
     TABLE_CMN_GROUP = 266,
     TABLE_START = 267,
     TABLE_ENTRY = 268,
     CLASS_ENTRY = 269,
     CLASS_START = 270,
     error2 = 271,
     BLOCK_START = 272,
     BLOCK_ENTRY = 273,
     BLOCKEND_ENTRY = 274,
     APPID_ENTRY = 275,
     BLOCK_RECORD_ENTRY = 276,
     DIMSTYLE_ENTRY = 277,
     LAYER_ENTRY = 278,
     LTYPE_ENTRY = 279,
     STYLE_ENTRY = 280,
     UCS_ENTRY = 281,
     VIEW_ENTRY = 282,
     VPORT_ENTRY = 283,
     ENTITY_CMN_GROUP = 284,
     ENTITY_START = 285,
     LINE_GROUP_CODE = 286,
     DIMENSION_ENTRY = 287,
     ALDIMENSION_ENTRY = 288,
     LRDIMENSION_ENTRY = 289,
     RDIMENSION_ENTRY = 290,
     ANDIMENSION_ENTRY = 291,
     ODIMENSION_ENTRY = 292,
     ARC_ENTRY = 293,
     CIRCLE_ENTRY = 294,
     LINE_ENTRY = 295,
     SPLINE_ENTRY = 296,
     TEXT_ENTRY = 297,
     MTEXT_ENTRY = 298,
     VIEWPORT_ENTRY = 299,
     LWPOLYLINE_ENTRY = 300,
     INSERT_ENTRY = 301
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   57

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNRULES -- Number of states.  */
#define YYNSTATES  85

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    19,    20,
      25,    26,    27,    31,    32,    37,    38,    39,    43,    44,
      45,    51,    52,    57,    59,    62,    63,    64,    68,    69,
      74,    76,    78,    80,    82,    84,    86,    88,    90,    92,
      93,    98,   100,   103,   104,   108,   109,   114,   116,   119,
     120,   124,   127,   130,   133,   136,   139,   140,   142,   144,
     146,   148,   150,   152,   154,   156,   158,   160,   161
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    -1,    48,    49,    -1,    48,    53,    -1,
      48,    57,    -1,    48,    67,    -1,    48,    78,    -1,    -1,
       3,    50,    51,     5,    -1,    -1,    -1,     4,    52,    51,
      -1,    -1,    15,    54,    55,     5,    -1,    -1,    -1,    14,
      56,    55,    -1,    -1,    -1,    12,    58,    62,     5,    59,
      -1,    -1,    13,    61,    63,    10,    -1,    60,    -1,    62,
      60,    -1,    -1,    -1,    11,    64,    66,    -1,    -1,    63,
      11,    65,    66,    -1,    20,    -1,    21,    -1,    22,    -1,
      23,    -1,    24,    -1,    25,    -1,    26,    -1,    27,    -1,
      28,    -1,    -1,    17,    68,    69,     5,    -1,    70,    -1,
      69,    70,    -1,    -1,    18,    71,    19,    -1,    -1,    18,
      72,    73,    19,    -1,    74,    -1,    73,    74,    -1,    -1,
      29,    75,    77,    -1,    32,    33,    -1,    32,    34,    -1,
      32,    35,    -1,    32,    36,    -1,    32,    37,    -1,    -1,
      38,    -1,    39,    -1,    40,    -1,    45,    -1,    41,    -1,
      44,    -1,    43,    -1,    42,    -1,    46,    -1,    76,    -1,
      -1,    30,    79,    73,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    40,    40,    41,    42,    43,    44,    45,    47,    47,
      50,    51,    51,    53,    53,    56,    57,    57,    59,    60,
      59,    64,    64,    67,    68,    70,    71,    71,    74,    74,
      77,    78,    84,    85,    96,    97,   105,   106,   107,   127,
     127,   134,   135,   136,   136,   141,   141,   152,   153,   154,
     154,   162,   163,   164,   165,   166,   167,   168,   185,   195,
     210,   230,   259,   277,   291,   303,   316,   318,   318
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "HEADER_START", "HEADER_VAR",
  "SECTION_END", "EOL", "VAR_NAME", "VALUE", "GROUP_CODE", "TABLE_END",
  "TABLE_CMN_GROUP", "TABLE_START", "TABLE_ENTRY", "CLASS_ENTRY",
  "CLASS_START", "error2", "BLOCK_START", "BLOCK_ENTRY", "BLOCKEND_ENTRY",
  "APPID_ENTRY", "BLOCK_RECORD_ENTRY", "DIMSTYLE_ENTRY", "LAYER_ENTRY",
  "LTYPE_ENTRY", "STYLE_ENTRY", "UCS_ENTRY", "VIEW_ENTRY", "VPORT_ENTRY",
  "ENTITY_CMN_GROUP", "ENTITY_START", "LINE_GROUP_CODE", "DIMENSION_ENTRY",
  "ALDIMENSION_ENTRY", "LRDIMENSION_ENTRY", "RDIMENSION_ENTRY",
  "ANDIMENSION_ENTRY", "ODIMENSION_ENTRY", "ARC_ENTRY", "CIRCLE_ENTRY",
  "LINE_ENTRY", "SPLINE_ENTRY", "TEXT_ENTRY", "MTEXT_ENTRY",
  "VIEWPORT_ENTRY", "LWPOLYLINE_ENTRY", "INSERT_ENTRY", "$accept", "input",
  "HEADER", "$@1", "HEADER_VARS", "$@2", "CLASSES", "$@3", "CLASS_ENTRIES",
  "$@4", "TABLES", "$@5", "$@6", "TABLE_ENTRY1", "$@7", "TABLE_ENTRIES",
  "TABLE_ENTRY_DATA", "$@8", "$@9", "TABLE_ENTRY_DATA1", "BLOCKS", "$@10",
  "BLOCK_ENTRIES", "BLOCK_ENTRY1", "$@11", "$@12", "ENTITY_ENTRIES",
  "ENTITY_ENTRY1", "$@13", "DIMENSION", "ENTITY_ENTRY_DATA1", "ENTITIES",
  "$@14", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    48,    48,    48,    48,    48,    50,    49,
      51,    52,    51,    54,    53,    55,    56,    55,    58,    59,
      57,    61,    60,    62,    62,    63,    64,    63,    65,    63,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    68,
      67,    69,    69,    71,    70,    72,    70,    73,    73,    75,
      74,    76,    76,    76,    76,    76,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    79,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     0,     4,
       0,     0,     3,     0,     4,     0,     0,     3,     0,     0,
       5,     0,     4,     1,     2,     0,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     2,     0,     3,     0,     4,     1,     2,     0,
       3,     2,     2,     2,     2,     2,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     8,    18,    13,    39,    67,     3,     4,
       5,     6,     7,    10,     0,    15,     0,     0,    11,     0,
      21,    23,     0,    16,     0,    43,     0,    41,    49,     0,
      47,    10,     9,    25,    19,    24,    15,    14,     0,     0,
      40,    42,    56,    68,    48,    12,    26,     0,    20,    17,
      44,     0,     0,    57,    58,    59,    61,    64,    63,    62,
      60,    65,    66,    50,     0,    22,    28,    46,    51,    52,
      53,    54,    55,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    27,     0,    29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     8,    13,    19,    31,     9,    15,    24,    36,
      10,    14,    48,    21,    33,    22,    47,    64,    83,    82,
      11,    16,    26,    27,    38,    39,    29,    30,    42,    62,
      63,    12,    17
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -55
static const yytype_int8 yypact[] =
{
     -55,     0,   -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,
     -55,   -55,   -55,     7,    -8,    -7,    -5,   -11,   -55,    15,
     -55,   -55,     3,   -55,    16,    -2,     1,   -55,   -55,    -4,
     -55,     7,   -55,    11,   -55,   -55,    -7,   -55,     4,   -11,
     -55,   -55,    -6,   -55,   -55,   -55,   -55,    -1,   -55,   -55,
     -55,   -15,    17,   -55,   -55,   -55,   -55,   -55,   -55,   -55,
     -55,   -55,   -55,   -55,    21,   -55,   -55,   -55,   -55,   -55,
     -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,
     -55,   -55,   -55,    21,   -55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -55,   -55,   -55,   -55,    -3,   -55,   -55,   -55,    19,   -55,
     -55,   -55,   -55,     9,   -55,   -55,   -55,   -55,   -55,   -54,
     -55,   -55,   -55,    30,   -55,   -55,    18,   -27,   -55,   -55,
     -55,   -55,   -55
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -46
static const yytype_int8 yytable[] =
{
       2,    43,    44,     3,    67,    20,    40,    23,    34,    65,
      66,    18,     4,    25,    28,     5,    20,     6,    28,    25,
      32,    37,    46,    50,    44,    28,    52,   -45,    45,    84,
       7,    35,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      68,    69,    70,    71,    72,    49,    41,    51
};

static const yytype_uint8 yycheck[] =
{
       0,     5,    29,     3,    19,    13,     5,    14,     5,    10,
      11,     4,    12,    18,    29,    15,    13,    17,    29,    18,
       5,     5,    11,    19,    51,    29,    32,    29,    31,    83,
      30,    22,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      33,    34,    35,    36,    37,    36,    26,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,     0,     3,    12,    15,    17,    30,    49,    53,
      57,    67,    78,    50,    58,    54,    68,    79,     4,    51,
      13,    60,    62,    14,    55,    18,    69,    70,    29,    73,
      74,    52,     5,    61,     5,    60,    56,     5,    71,    72,
       5,    70,    75,     5,    74,    51,    11,    63,    59,    55,
      19,    73,    32,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    76,    77,    64,    10,    11,    19,    33,    34,
      35,    36,    37,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    66,    65,    66
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 8:

    {_out="Catching an Header Start \n";
							 yyerror(yytext);;}
    break;

  case 9:

    {_out="Catching a Section End \n";
																				yyerror(yytext);;}
    break;

  case 11:

    {_out="Catching an Header variable \n";
							yyerror(yytext);;}
    break;

  case 13:

    {_out="Catching a Class Start \n";
							 yyerror(yytext);;}
    break;

  case 14:

    {_out="Catching a Section End \n";
																				yyerror(yytext);;}
    break;

  case 16:

    {_out="Catching a Class Entry \n";
							yyerror(yytext);;}
    break;

  case 18:

    {_out="Catching a Table Start \n";
							 yyerror(yytext);;}
    break;

  case 19:

    {_out="Catching a Table Section End \n";
							 yyerror(yytext);;}
    break;

  case 20:

    { 
			;}
    break;

  case 21:

    {_out="Catching a Table Entry \n";
							 yyerror(yytext);;}
    break;

  case 22:

    {_out="Catching a Table End \n";
							 yyerror(yytext);;}
    break;

  case 26:

    {_out="Catching a Table Common Entry Data \n";
							 yyerror(yytext);;}
    break;

  case 27:

    {_out="Catching a Table Entry Data \n";
							 yyerror(yytext);;}
    break;

  case 28:

    {_out="Catching a Table Common Entry Data \n";
							 yyerror(yytext);;}
    break;

  case 29:

    {_out="Catching a Table Entry Data \n";
							 yyerror(yytext);;}
    break;

  case 31:

    {
								string _text=dxfvs[2];
								if(!dxfBlock)
									dxfpDoc->m_objects->AddBlock(_text);
								dxfvs.clear();
					;}
    break;

  case 33:

    {
								string _text=dxfvs[2];
								int layer_status=(dxfvf[70]==4)?1:0;
								int layer_color=dxfvf[62];
								int layer_lineweight=dxfvf[370];
								string layer_linetype=dxfvs[6];
								if(!dxfBlock)
									dxfpDoc->m_objects->AddLayer(_text,layer_status,layer_color,layer_linetype,layer_lineweight);
								dxfvf.clear();
								dxfvs.clear();
					;}
    break;

  case 35:

    {
								string _text=dxfvs[2];
								float fixed_height=atof(dxfvs[40].c_str());
								float width_factor=atof(dxfvs[41].c_str());
								string _font=dxfvs[3];
								dxfpDoc->m_objects->AddTextStyle(_text,_font,fixed_height,width_factor);
								dxfvs.clear();
					;}
    break;

  case 38:

    {
								if((dxfvs[2]=="*Active")||(dxfvs[2]=="*ACTIVE"))
								{
								string _text=dxfvs[1];
								CVector vo_wcs(dxfvf[10],dxfvf[20],dxfvf[30]);
								CVector vo_dcs(dxfvf[12],dxfvf[22]);
								CVector viewdir_dcs(dxfvf[16],dxfvf[26],dxfvf[36]);
								float zoom_pc=dxfvf[72];
								CVector vo_ucs(dxfvf[110],dxfvf[120],dxfvf[130]);
								CVector vox_ucs(dxfvf[111],dxfvf[121],dxfvf[131]);
								CVector voy_ucs(dxfvf[112],dxfvf[122],dxfvf[132]);

								int paper_width=dxfvf[40];
								int paper_height=dxfvf[41];
								if(!dxfBlock)
									dxfpDoc->m_objects->AddViewport(dxfHdc,vo_wcs,vo_dcs,vo_ucs,vox_ucs,voy_ucs,zoom_pc,paper_width,paper_height);
								dxfvf.clear();
								}
					;}
    break;

  case 39:

    {
					 _token=BLOCK_START;
					_out="Catching a Block Start \n";
							 yyerror(yytext);;}
    break;

  case 40:

    {
																			if(dxfBlock) YYACCEPT;
																			_out="Catching a Block Section End \n";
																			yyerror(yytext);;}
    break;

  case 43:

    {
							dxfvs.clear();
							_out="Catching a Block Entry \n";
							 yyerror(yytext);;}
    break;

  case 44:

    {_out="Catching a Block End Entry \n";
							 yyerror(yytext);;}
    break;

  case 45:

    {
								CVector vo(atof(dxfvs[10].c_str()),atof(dxfvs[20].c_str()),atof(dxfvs[30].c_str()));
								string _text=dxfvs[2];
								string _layer=dxfvs[8];
								string _handle=dxfvs[5];
								dxfpDoc->m_objects->AddBlock2(_text,_layer,_handle,vo);
								dxfvs.clear();
			 
			 _out="Catching a Block Entry \n";
							 yyerror(yytext);;}
    break;

  case 46:

    {_out="Catching a Block End Entry\n";
							 yyerror(yytext);;}
    break;

  case 49:

    {
							 string layer_name=dxfvs[8];
                             dxfpDoc->m_objects->setCurrentLayer(layer_name);//dxfpvec);
							 dxfvs.clear();

							 _out="Catching an Entity Common Entry \n";
							 yyerror(yytext);;}
    break;

  case 50:

    {_out="Catching an Entity Entry Data \n";
							 yyerror(yytext);;}
    break;

  case 57:

    {
									CVector vo(dxfvf[10],dxfvf[20],dxfvf[30]);
									float r=dxfvf[40];
									float start_a=(dxfvf[50]*2*pi)/360;
									CVector vstart=vo+polarc(r,start_a);
									float end_a=dxfvf[51];
									end_a=(end_a<dxfvf[50])?360+end_a:end_a;
									end_a=(end_a*2*pi)/360;;
									CVector vend=vo+polarc(r,end_a);
									float angle=end_a-start_a;
									dxfpDoc->m_objects->AddArc(vo,vstart,angle);//dxfpvec);
									if(_token==BLOCK_START)
									{
									dxfpDoc->m_objects->AddToBlock();
									}
									dxfvf.clear();
					;}
    break;

  case 58:

    {
									CVector vo(dxfvf[10],dxfvf[20],dxfvf[30]);
									float r=dxfvf[40];
									dxfpDoc->m_objects->AddCircle(vo,r);//dxfpvec);
									if(_token==BLOCK_START)
									{
									dxfpDoc->m_objects->AddToBlock();
									}
									dxfvf.clear();
					;}
    break;

  case 59:

    { 
									CVector vo(dxfvf[10],dxfvf[20],dxfvf[30]);
									CVector ve(dxfvf[11],dxfvf[21],dxfvf[31]);
									vector<CVector> vg;
									vg.push_back(vo);
									vg.push_back(ve);
									dxfpDoc->m_objects->AddLine(vg);//dxfpvec);
									if(_token==BLOCK_START)
									{
									dxfpDoc->m_objects->AddToBlock();
									}
									dxfvf.clear();
								
								nbline++;
								;}
    break;

  case 60:

    { 
								int nb_cpts=dxfvf[90];
								vector<CVector> vg;
								for(int i=0;i<nb_cpts;i++)
								{
									CVector vo(vdxfvf[10][i],vdxfvf[20][i]);
									vg.push_back(vo);
								}
									vdxfvf[10].clear();
									vdxfvf[20].clear();

									dxfpDoc->m_objects->AddLine(vg);
									if(_token==BLOCK_START)
									{
									dxfpDoc->m_objects->AddToBlock();
									}
									vdxfvf.clear();
									dxfvf.clear();
								
							;}
    break;

  case 61:

    {
								int nb_cpts=dxfvf[73];
								vector<CVector> vg,vg1;
								for(int i=0;i<nb_cpts;i++)
								{
									CVector vo(vdxfvf[10][i],vdxfvf[20][i],vdxfvf[30][i]);
									vg.push_back(vo);
								}
								int nb_knts=dxfvf[72];
								vector<float> fvg;
								for(i=0;i<nb_knts;i++)
								{
									fvg.push_back(vdxfvf[40][i]);
								}
									vdxfvf[10].clear();
									vdxfvf[20].clear();
									vdxfvf[30].clear();
									vdxfvf[40].clear();
									dxfpDoc->m_objects->AddSpline2(vg,fvg,false,dxfHdc);
									if(_token==BLOCK_START)
									{
									dxfpDoc->m_objects->AddToBlock();
									}
									vdxfvf.clear();
									dxfvf.clear();
									nbspline++;
								
					
					;}
    break;

  case 62:

    {
								if(_token==ENTITY_START)
								{
								string _text=dxfvs[1];
								CVector vo_wcs(dxfvf[10],dxfvf[20],dxfvf[30]);
								CVector vo_dcs(dxfvf[12],dxfvf[22]);
								CVector viewdir_dcs(dxfvf[16],dxfvf[26],dxfvf[36]);
								float zoom_pc=dxfvf[72];
								CVector vo_ucs(dxfvf[110],dxfvf[120],dxfvf[130]);
								CVector vox_ucs(dxfvf[111],dxfvf[121],dxfvf[131]);
								CVector voy_ucs(dxfvf[112],dxfvf[122],dxfvf[132]);

								int paper_width=dxfvf[40];
								int paper_height=dxfvf[41];
								dxfpDoc->m_objects->AddViewport(dxfHdc,vo_wcs,vo_dcs,vo_ucs,vox_ucs,voy_ucs,zoom_pc,paper_width,paper_height);
								dxfvf.clear();
								}
					;}
    break;

  case 63:

    {
								string _text=dxfvs[1];
								CVector vo(dxfvf[10],dxfvf[20],dxfvf[30]);
								int attachpoint=dxfvf[71];
								dxfpDoc->m_objects->AddText(dxfHdc,vo,_text,dxfvf[40],dxfvs[7]);
								if(_token==BLOCK_START)
								{
								dxfpDoc->m_objects->AddToBlock();
								}
								dxfvf.clear();
								dxfvs.clear();
								
					
					;}
    break;

  case 64:

    {
								string _text=dxfvs[1];
								CVector vo(dxfvf[10],dxfvf[20],dxfvf[30]);
								int attachpoint=dxfvf[71];
								dxfpDoc->m_objects->AddText(dxfHdc,vo,_text,dxfvf[40],dxfvs[7]);
								if(_token==BLOCK_START)
								{
								dxfpDoc->m_objects->AddToBlock();
								}
								dxfvf.clear();
								dxfvs.clear();
					;}
    break;

  case 65:

    {
								CVector vo(atof(dxfvs[10].c_str()),atof(dxfvs[20].c_str()),atof(dxfvs[30].c_str()));
								string _text=dxfvs[2];
								CVector vscale(atof(dxfvs[41].c_str()),atof(dxfvs[42].c_str()),atof(dxfvs[43].c_str()));
								float rot_angle=atof(dxfvs[50].c_str());
								CVector col_row_count(atof(dxfvs[70].c_str()),atof(dxfvs[71].c_str()));
								CVector col_row_spacing(atof(dxfvs[44].c_str()),atof(dxfvs[45].c_str()));
								dxfpDoc->m_objects->AddBlock3(_text,rot_angle,vscale,vo,col_row_count,col_row_spacing);
								if(_token==BLOCK_START)
								{
								dxfpDoc->m_objects->AddToBlock();
								}
								dxfvs.clear();
					;}
    break;

  case 67:

    {_out="Catching an Entity Start \n";
							 yyerror(yytext);
							 _token=ENTITY_START;
						;}
    break;

  case 68:

    {_out="Catching a Block Section End \n";
														yyerror(yytext);
														_token=-1;
													 ;}
    break;



      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



       
