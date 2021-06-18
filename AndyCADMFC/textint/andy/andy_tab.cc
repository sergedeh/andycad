
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
#define yyparse         andyparse
#define yylex           andylex
#define yyerror         andyerror
#define yylval          andylval
#define yychar          andychar
#define yydebug         andydebug
#define yynerrs         andynerrs


/* Copy the first part of user declarations.  */


#include <malloc.h>
#define alloc _alloc
#include <stdio.h>
#include <vector>
using namespace std;


vector<CVector> pvec;
vector<float> fvec;
CString out,com;
CCadDoc* pDoc;
CCadView *pView;
CVector cv;


yyerror (char* s)  /* Called by yyparse on error */
{
 // printf ("%s\n", s);
  CString f(s);
  out+=f;
}
/*	|line			{
								com="First Point:";
								pvec.clear();
					}
	|spline			{
								com="First Point:";
								pvec.clear();
					}
	|rect			{
								com="First Corner:";
								pvec.clear();
					}
	|circle			{
								com="Center Point:";
								pvec.clear();
					}

	|arc			{
								com="Center Point:";
								pvec.clear();
					}
	|MODEL			{
								com="Size of the Model Space (X,Y):";
								pvec.clear();
					}

	|ZOOM		 	{
								com="Enter a scale factor:";
						}
	|numexpr ',' numexpr 	{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
							if(!vi.empty())
							{
							switch(vi.front())
							{
							case MODEL:
							{
							com="Command: ";
							pDoc->m_objects->setPage(CSize(f1,f2));
							pView->Invalidate(TRUE);
							vi.pop();
							break;
							}
							default:
							;
							}
							}
							else
								out+="No command has been entered";
						}
	|numexpr  			{
	                        float f1=vf.front();vf.pop();
							if(!vi.empty())
							{
							switch(vi.front())
							{
							case ZOOM:
							{
							com="Command: ";
							pDoc->m_objects->setzoomrat(f1);
							pView->Invalidate(TRUE);
							vi.pop();
							break;
							}
							case circle:
							{
							if(pvec.size()==1)
							{
							pDoc->m_objects->AddCircle(pvec[0],f1);
							vi.pop();
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
							}
							break;
							}
							default:
							;
							}
							}
							else
								out+="No command has been entered";
						}

	|point			{
							if(!vi.empty())
							{
							switch(vi.front())
							{
							case line:
							{
							com="Next Point:";
							pDoc->m_objects->addLine2(pvec);
							if(pvec.size()>1)
								pView->Invalidate(TRUE);
							break;
							}
							case spline:
							{
							com="Next Point:";
							pDoc->m_objects->AddSpline2(pvec);
							cv=pvec.back();
							if(pvec.size()>1)
								pView->Invalidate(TRUE);
							break;
							}
							case rect:
							{
							if(pvec.size()<1)
							{
							com="Next Corner:";
							}
							if(pvec.size()>1){
							pDoc->m_objects->AddRectangle(pvec[0],pvec[1]);
							vi.pop();
							pView->Invalidate(TRUE);
							}
							break;
							}
							case circle:
							{
							if(pvec.size()==1)
								com="Radius:";
							break;
							}
							default:
							;
							}
							}
							else
								out+="No command has been entered";

					}
						
						
						*/





/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
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
     _delete = 258,
     line = 259,
     rect = 260,
     circle = 261,
     qline = 262,
     ellipse = 263,
     arc = 264,
     spline = 265,
     spline2 = 266,
     MOVE = 267,
     MOVENODE = 268,
     ROTATE = 269,
     text = 270,
     object = 271,
     help = 272,
     num = 273,
     OFFSET = 274,
     BREAKCURVE = 275,
     SCALE = 276,
     SCALE2 = 277,
     ANGCOPY = 278,
     POLARCOPY = 279,
     ARRAYCOPY = 280,
     LOOKAT = 281,
     ROTATECAM = 282,
     SWIVEL = 283,
     ZOOM = 284,
     MOVECAM = 285,
     MOVETO = 286,
     MOVENODETO = 287,
     error2 = 288,
     MODEL = 289
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
#define YYLAST   249

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNRULES -- Number of states.  */
#define YYNSTATES  150

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    43,    45,    38,    44,     2,    42,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      37,     2,    39,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    41,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     8,    10,    13,    17,    21,
      25,    29,    33,    38,    44,    49,    53,    57,    62,    65,
      68,    72,    76,    81,    85,    90,    94,    97,   100,   104,
     111,   118,   126,   130,   134,   138,   141,   144,   146,   149,
     152,   155,   158,   161,   164,   167,   170,   173,   176,   179,
     182,   185,   188,   191,   194,   197,   200,   203,   206,   209,
     213,   219,   227,   231,   234,   236,   239,   241,   244,   246,
     248,   252,   256,   260
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    -1,    47,    48,    -1,    -1,    49,    -1,
       3,    54,    -1,     4,    51,    52,    -1,     5,    51,    51,
      -1,     6,    51,    54,    -1,     7,    51,    52,    -1,     8,
      51,    54,    -1,     9,    51,    51,    54,    -1,     9,    51,
      54,    54,    54,    -1,     9,    51,    51,    51,    -1,     9,
      51,    51,    -1,    10,    51,    52,    -1,    11,    51,    52,
      50,    -1,    12,    51,    -1,    31,    51,    -1,    13,    51,
      54,    -1,    32,    51,    54,    -1,    14,    51,    54,    54,
      -1,    14,    54,    54,    -1,    21,    51,    54,    54,    -1,
      21,    54,    54,    -1,    22,    54,    -1,    19,    54,    -1,
      20,    54,    54,    -1,    23,    51,    54,    54,    54,    54,
      -1,    24,    51,    54,    54,    54,    54,    -1,    25,    54,
      54,    54,    54,    54,    54,    -1,    26,    51,    51,    -1,
      27,    54,    54,    -1,    28,    54,    54,    -1,    30,    51,
      -1,    29,    54,    -1,    17,    -1,    17,     4,    -1,    17,
       5,    -1,    17,     6,    -1,    17,     9,    -1,    17,    10,
      -1,    17,    12,    -1,    17,    31,    -1,    17,    13,    -1,
      17,    32,    -1,    17,    14,    -1,    17,    21,    -1,    17,
      19,    -1,    17,    20,    -1,    17,    23,    -1,    17,    24,
      -1,    17,    25,    -1,    17,    26,    -1,    17,    27,    -1,
      17,    28,    -1,    17,    30,    -1,    17,    29,    -1,    35,
      53,    36,    -1,    37,    54,    38,    54,    39,    -1,    37,
      54,    38,    54,    38,    54,    39,    -1,    54,    37,    54,
      -1,    40,    51,    -1,    51,    -1,    51,    52,    -1,    54,
      -1,    54,    53,    -1,    18,    -1,    41,    -1,    54,    42,
      54,    -1,    54,    43,    54,    -1,    54,    44,    54,    -1,
      54,    45,    54,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   170,   170,   171,   173,   178,   182,   187,   194,   200,
     207,   210,   213,   220,   229,   235,   241,   247,   254,   259,
     264,   270,   276,   283,   290,   297,   304,   310,   316,   324,
     334,   344,   355,   357,   363,   369,   374,   380,   406,   412,
     418,   424,   434,   440,   446,   452,   458,   464,   473,   485,
     491,   497,   503,   509,   515,   519,   525,   531,   537,   545,
     555,   562,   570,   580,   586,   587,   588,   589,   591,   595,
     598,   604,   610,   616
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_delete", "line", "rect", "circle",
  "qline", "ellipse", "arc", "spline", "spline2", "MOVE", "MOVENODE",
  "ROTATE", "text", "object", "help", "num", "OFFSET", "BREAKCURVE",
  "SCALE", "SCALE2", "ANGCOPY", "POLARCOPY", "ARRAYCOPY", "LOOKAT",
  "ROTATECAM", "SWIVEL", "ZOOM", "MOVECAM", "MOVETO", "MOVENODETO",
  "error2", "MODEL", "'['", "']'", "'<'", "','", "'>'", "'@'", "'p'",
  "'/'", "'*'", "'-'", "'+'", "$accept", "input", "_Line", "expr", "knots",
  "point", "points", "nums", "numexpr", 0
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
     285,   286,   287,   288,   289,    91,    93,    60,    44,    62,
      64,   112,    47,    42,    45,    43
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    47,    48,    48,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    50,
      51,    51,    51,    51,    52,    52,    53,    53,    54,    54,
      54,    54,    54,    54
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     0,     1,     2,     3,     3,     3,
       3,     3,     4,     5,     4,     3,     3,     4,     2,     2,
       3,     3,     4,     3,     4,     3,     2,     2,     3,     6,
       6,     7,     3,     3,     3,     2,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       5,     7,     3,     2,     1,     2,     1,     2,     1,     1,
       3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     5,    68,    69,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,     0,     0,
      38,    39,    40,    41,    42,    43,    45,    47,    49,    50,
      48,    51,    52,    53,    54,    55,    56,    58,    57,    44,
      46,    27,     0,     0,     0,    26,     0,     0,     0,     0,
       0,     0,    36,    35,    19,     0,     0,     0,     0,     0,
       0,    63,    64,     7,     0,     8,     9,    10,    11,    15,
       0,    16,     0,    20,     0,    23,    28,     0,    25,     0,
       0,     0,    32,    33,    34,    21,    70,    71,    72,    73,
       0,    65,    62,    14,    12,     0,     0,    17,    22,    24,
       0,     0,     0,     0,    13,     0,    66,     0,     0,     0,
       0,    60,    59,    67,    29,    30,     0,     0,    31,    61
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    30,    31,   127,    92,    93,   135,    38
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -129
static const yytype_int16 yypact[] =
{
    -129,   181,  -129,   -11,    -6,    -6,    -6,    -6,    -6,    -6,
      -6,    -6,    -6,    -6,    -6,   217,   -11,   -11,    -6,   -11,
      -6,    -6,   -11,    -6,   -11,   -11,   -11,    -6,    -6,    -6,
    -129,  -129,  -129,  -129,    12,   -11,    -6,    -6,    16,    -6,
     -11,    -6,   -11,    -6,    -6,    -6,  -129,   -11,   -11,     6,
    -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,
    -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,
    -129,    12,   -16,   -11,     6,    12,   -11,   -11,   -16,    -6,
     -16,   -16,    12,  -129,  -129,   -11,   -11,   -11,   -11,   -11,
      67,  -129,    -6,  -129,   -11,  -129,    12,  -129,    12,    -6,
       6,  -129,   -32,    12,   -16,    12,    12,   -16,    12,   -16,
     -16,   -16,  -129,    12,    12,    12,    12,    12,    12,    12,
     -11,  -129,    12,  -129,    16,   -16,   -11,  -129,    12,    12,
     -16,   -16,   -16,    50,    12,   -30,   -16,   -16,   -16,   -16,
     -11,  -129,  -129,  -129,    12,    12,   -16,    23,    12,  -129
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -129,  -129,  -129,  -129,  -129,   140,   -40,  -128,    -3
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      34,    97,    32,   126,   101,   102,   142,    32,   143,     0,
       0,    49,    32,    71,    72,    74,    75,     0,     0,    78,
       0,    80,    81,    82,    32,    33,    86,    87,    88,    89,
      33,    35,    90,     0,    36,    33,     0,    96,     0,    98,
     100,     0,     0,    94,   103,   104,   105,    33,    86,    87,
      88,    89,   121,    94,    86,    87,    88,    89,    86,    87,
      88,    89,   149,     0,     0,    86,    87,    88,    89,   106,
     107,   108,     0,   109,   110,   111,     0,   113,   114,     0,
       0,     0,   115,   116,   117,   118,   119,     0,   140,   141,
       0,   122,    86,    87,    88,    89,   124,   125,     0,     0,
       0,   128,     0,     0,   129,   120,   130,   131,   132,    86,
      87,    88,    89,     0,     0,     0,     0,   133,     0,     0,
       0,     0,   134,   136,     0,     0,     0,   137,   138,   139,
       0,     0,     0,   136,   144,   145,   146,   147,     0,     0,
       0,     0,     0,   148,    37,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,     0,     0,     0,    73,     0,
      76,    77,     0,    79,     0,     0,     0,    83,    84,    85,
       0,     0,     0,     0,     0,     0,    91,     0,     0,    95,
       0,     2,     0,    99,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,    15,     0,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,     0,     0,     0,     0,     0,   112,
       0,    50,    51,    52,     0,     0,    53,    54,     0,    55,
      56,    57,     0,     0,     0,     0,    58,    59,    60,   123,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70
};

static const yytype_int16 yycheck[] =
{
       3,    41,    18,    35,    44,    45,    36,    18,   136,    -1,
      -1,    14,    18,    16,    17,    18,    19,    -1,    -1,    22,
      -1,    24,    25,    26,    18,    41,    42,    43,    44,    45,
      41,    37,    35,    -1,    40,    41,    -1,    40,    -1,    42,
      43,    -1,    -1,    37,    47,    48,    49,    41,    42,    43,
      44,    45,    92,    37,    42,    43,    44,    45,    42,    43,
      44,    45,    39,    -1,    -1,    42,    43,    44,    45,    72,
      73,    74,    -1,    76,    77,    78,    -1,    80,    81,    -1,
      -1,    -1,    85,    86,    87,    88,    89,    -1,    38,    39,
      -1,    94,    42,    43,    44,    45,    99,   100,    -1,    -1,
      -1,   104,    -1,    -1,   107,    38,   109,   110,   111,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,   120,    -1,    -1,
      -1,    -1,   125,   126,    -1,    -1,    -1,   130,   131,   132,
      -1,    -1,    -1,   136,   137,   138,   139,   140,    -1,    -1,
      -1,    -1,    -1,   146,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    18,    -1,
      20,    21,    -1,    23,    -1,    -1,    -1,    27,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    39,
      -1,     0,    -1,    43,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    17,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,    79,
      -1,     4,     5,     6,    -1,    -1,     9,    10,    -1,    12,
      13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,    99,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    17,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      48,    49,    18,    41,    54,    37,    40,    51,    54,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    54,
       4,     5,     6,     9,    10,    12,    13,    14,    19,    20,
      21,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    54,    54,    51,    54,    54,    51,    51,    54,    51,
      54,    54,    54,    51,    51,    51,    42,    43,    44,    45,
      54,    51,    51,    52,    37,    51,    54,    52,    54,    51,
      54,    52,    52,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    51,    54,    54,    54,    54,    54,    54,    54,
      38,    52,    54,    51,    54,    54,    35,    50,    54,    54,
      54,    54,    54,    54,    54,    53,    54,    54,    54,    54,
      38,    39,    36,    53,    54,    54,    54,    54,    54,    39
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
        case 4:

    { 
							while(!vi.empty())
								vi.pop();
							pvec.clear();
			;}
    break;

  case 5:

    { 
							
					;}
    break;

  case 6:

    {
	                        int f1=vf.front();vf.pop();
							pDoc->m_objects->Delete(f1);
							pView->Invalidate(TRUE);
						;}
    break;

  case 7:

    {
//							if(pvec.size()==2)
								pDoc->m_objects->AddLine(pvec);
							cv=pvec.back();
							pvec.clear(); 
							pView->Invalidate(TRUE);
						;}
    break;

  case 8:

    { 
							pDoc->m_objects->AddRectangle(pvec[0],pvec[1]);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 9:

    { 
	                        float f1=vf.front();vf.pop();
							pDoc->m_objects->AddCircle(pvec[0],f1);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 10:

    { 
							out+="I am drawing a qline\r\n";
						;}
    break;

  case 11:

    { 
							out+="I am drawing an ellipse\r\n";
						;}
    break;

  case 12:

    { 
	                        float f1=vf.front();vf.pop();
							pDoc->m_objects->AddArc(pvec[0],pvec[1],f1);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 13:

    { 
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
	                        float f3=vf.front();vf.pop();
							pDoc->m_objects->AddArc(pvec[0],f1,f2,f3);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 14:

    { 
							pDoc->m_objects->AddArc(pvec[0],pvec[1],pvec[2]);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 15:

    { 
							pDoc->m_objects->AddArc(pvec[0],pvec[1]);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 16:

    { 
							pDoc->m_objects->AddSpline(pvec);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 17:

    { 
							pDoc->m_objects->AddSpline2(pvec,fvec,false);
							cv=pvec.back();
							pvec.clear();
							fvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 18:

    {
							pDoc->m_objects->Move(NULL,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 19:

    {
							pDoc->m_objects->MoveTo(NULL,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 20:

    {
	                        float f1=vf.front();vf.pop();
							pDoc->m_objects->Move(NULL,f1,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 21:

    {
	                        float f1=vf.front();vf.pop();
							pDoc->m_objects->MoveTo(NULL,f1,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 22:

    {
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
							pDoc->m_objects->rotate(f1,f2,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 23:

    {
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->rotate(f1,f2);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 24:

    {
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->scale(f1,f2,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 25:

    {
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->scale(f1,f2);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 26:

    {
	                        float f1=vf.front();vf.pop();
						    pDoc->m_objects->copy2(f1);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 27:

    {
	                        float f1=vf.front();vf.pop();
						    pDoc->m_objects->Offset(f1);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 28:

    {			
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->AddBreak(f1,f2);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 29:

    {
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
	                        float f3=vf.front();vf.pop();
	                        float f4=vf.front();vf.pop();
						    pDoc->m_objects->copyRSparam2(NULL,f1,f2,f3,f4,false,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 30:

    {
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
	                        float f3=vf.front();vf.pop();
	                        float f4=vf.front();vf.pop();
						    pDoc->m_objects->copyRSparam2(NULL,f1,f2,f3,f4,true,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;}
    break;

  case 31:

    {
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
	                        float f3=vf.front();vf.pop();
	                        float f4=vf.front();vf.pop();
	                        float f5=vf.front();vf.pop();
	                        float f6=vf.front();vf.pop();
						    pDoc->m_objects->pastearray(NULL,true,f1,f3,f2,f4,f5,f6);
							pView->Invalidate(TRUE);
						;}
    break;

  case 32:

    {
						;}
    break;

  case 33:

    {
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->rotatecam(f1,f2);
							pView->Invalidate(TRUE);
						;}
    break;

  case 34:

    {
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->rotatecam(f1,f2,true);
							pView->Invalidate(TRUE);
						;}
    break;

  case 35:

    {
						    pDoc->m_objects->translatecam(pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
					;}
    break;

  case 36:

    {
	                        float f1=vf.front();vf.pop();
						    pDoc->m_objects->setzoomrat(f1);
							pvec.clear();
							pView->Invalidate(TRUE);
					;}
    break;

  case 37:

    {
						out+= " For more information about a specific command, type [help command-name] \r\n\r\n";
						out+= " line \t\t display a multiline object \r\n";
						out+= " rect \t\t display a rectangle object \r\n";
						out+= " circle \t\t display a circle object \r\n";
						out+= " arc \t\t display a arc object \r\n";
						out+= " spline \t\t display a spline object \r\n";
						out+= " move \t\t move an object by a vector \r\n";
						out+= " moveto \t\t move an object (its barycentre) to a specific point. \r\n";
						out+= " movenode \t move an object node by a vector \r\n";
						out+= " movenodeto \t move an object node to a specific point. \r\n";
						out+= " rotate \t\t rotate an object by an angle. \r\n";
						out+= " scale \t\t scale an object by a scaling (X,Y) factor. \r\n";
						out+= " scale2 \t\t scale an object by a unique scaling factor. \r\n";
						out+= " offset \t\t offset an object by a distance. \r\n";
						out+= " breakcurve \t\t break a curve from a distance1 to a distance 2. \r\n";
						out+= " angcopy \t\t copy an object at specific angle around a center point. \r\n";
						out+= " polarcopy \t copy an object at specific angle around a center point. \r\n";
						out+= " arraycopy \t copy an object at specific X,Y distance. \r\n";
						out+= " lookat \t\t direct the camera to look at a specific point. \r\n";
						out+= " rotatecam \t rotate the camera by a specific angle. \r\n";
						out+= " swivel \t\t swivel the camera by specific distance in X,Y. \r\n";
						out+= " movecam \t move the camera to a specific point. \r\n\r\n";
						out+= " For more informtion on tools, see the command line reference in the online help. \r\n";

					;}
    break;

  case 38:

    {
						out+= " Display a multiline object \r\n\r\n";
						out+= " line point point [point...]  \r\n\r\n";
						out+= " example 1: Draw a multiline from (0,0) to (150,0) then (500,0) \r\n\r\n";
						out+= " line <0,0> <150,150> <500,0>  \r\n\r\n";
					;}
    break;

  case 39:

    {
						out+= " Display a rectangle object \r\n\r\n";
						out+= " rect point point  \r\n\r\n";
						out+= " example 1: Draw a Rectangle from (0,0) to (500,500) \r\n\r\n";
						out+= " rect <0,0> <500,0>  \r\n\r\n";
					;}
    break;

  case 40:

    {
						out+= " Display a circle object \r\n\r\n";
						out+= " circle point radius  \r\n\r\n";
						out+= " example 1: Draw a circle with center (0,0) and radius 500 \r\n\r\n";
						out+= " circle <0,0> 500  \r\n\r\n";
					;}
    break;

  case 41:

    {
						out+= " Display an arc object \r\n\r\n";
						out+= " arc point point angle  \r\n\r\n";
						out+= " example 1: Draw an arc from (0,0) to (500,0) with 300deg \r\n\r\n";
						out+= " arc <0,0> <500,0> 300  \r\n\r\n";
						out+= " example 2: Draw an arc with passing through (0,0), (500,0) and (300,200) \r\n\r\n";
						out+= " arc <0,0> <500,0> <300,200>  \r\n\r\n";
						out+= " example 3: Draw an arc with passing through (0,0) and <500,0> \r\n\r\n";
						out+= " arc <0,0> <500,0> \r\n\r\n";
					;}
    break;

  case 42:

    {
						out+= " Display a spline object \r\n\r\n";
						out+= " spline point point [point...]  \r\n\r\n";
						out+= " example 1: Draw a spline from (0,0) to (150,300) then (500,0) \r\n\r\n";
						out+= " spline <0,0> <150,300> <500,0>  \r\n\r\n";
					;}
    break;

  case 43:

    {
						out+= " Move an object by a vector \r\n\r\n";
						out+= " move point   \r\n\r\n";
						out+= " example 1: Move a selected object by a vector (200,300) \r\n\r\n";
						out+= " move <200,300>  \r\n\r\n";
					;}
    break;

  case 44:

    {
						out+= " Move an object (its barycentre) to a specific point. \r\n\r\n";
						out+= " moveto point  \r\n\r\n";
						out+= " example 1: Move a selected object by to the point (200,300) \r\n\r\n";
						out+= " moveto <200,300>  \r\n\r\n";
					;}
    break;

  case 45:

    {
						out+= " Move an object node by a vector \r\n\r\n";
						out+= " movenode point nodenumber  \r\n\r\n";
						out+= " example 1: Move the 1st node of a selected object by a vector (200,300) \r\n\r\n";
						out+= " movenode <200,300> 1  \r\n\r\n";
					;}
    break;

  case 46:

    {
						out+= " Move an object node to a specific point. \r\n\r\n";
						out+= " movenodeto point nodenumber  \r\n\r\n";
						out+= " example 1: Move the 1st node of a selected object to the point (200,300) \r\n\r\n";
						out+= " movenodeto <200,300> 1  \r\n\r\n";
					;}
    break;

  case 47:

    {
						out+= " Rotate an object by an angle. \r\n\r\n";
						out+= " rotate point xangle yangle  \r\n\r\n";
						out+= " rotate xangle yangle  \r\n\r\n";
						out+= " example 1: rotate the selected object by 300deg \r\n\r\n";
						out+= " rotate 300 0  \r\n\r\n";
						out+= " example 2: rotate the selected object by 300deg with a center of rotation at <0,0>\r\n\r\n";
						out+= " rotate <0,0> 300 0  \r\n\r\n";
					;}
    break;

  case 48:

    {
						out+= " Scale an object by a scaling (X,Y) factor. \r\n\r\n";
						out+= " scale point xscale yscale  \r\n\r\n";
						out+= " scale xscale yscale  \r\n\r\n";
						out+= " scale2 xyscale  \r\n\r\n";
						out+= " example 1: scale the selected object by 2 \r\n\r\n";
						out+= " scale 2 1  \r\n\r\n";
						out+= " example 2: scale the selected object by 2 with a center of scale at <0,0>\r\n\r\n";
						out+= " scale <0,0> 2 1  \r\n\r\n";
						out+= " example 3: scale the selected object by 1.5 \r\n\r\n";
						out+= " scale2 1.5   \r\n\r\n";
						;}
    break;

  case 49:

    {
						out+= " Offset an object by a distance . \r\n\r\n";
						out+= " offset distance  \r\n\r\n";
						out+= " example 1: offset the selected object by 50 \r\n\r\n";
						out+= " offset 50  \r\n\r\n";
						;}
    break;

  case 50:

    {
						out+= " Breack a curve selected from a distance 1 to a distance 2 . \r\n\r\n";
						out+= " breakcurve distance1 distance2  \r\n\r\n";
						out+= " example 1: break the selected curve from 100 to 150 \r\n\r\n";
						out+= " breakcurve 100 150  \r\n\r\n";
					;}
    break;

  case 51:

    {
						out+= " Copy an object at specific angle around a center point. \r\n\r\n";
						out+= " angcopy u1 u2 u3 u4  \r\n\r\n";
						out+= " example 1: angular copy the selected object around the center <0,0> by 45deg with 4 copies \r\n\r\n";
						out+= " angcopy <0,0> 45 4 1 0  \r\n\r\n";
					;}
    break;

  case 52:

    {
						out+= " Copy an object at specific angle around a center point. \r\n\r\n";
						out+= " polarcopy u1 u2 u3 u4  \r\n\r\n";
						out+= " example 1: polar copy the selected object around the center <0,0> by 45deg with 4 copies \r\n\r\n";
						out+= " polarcopy <0,0> 45 4 1 0  \r\n\r\n";
					;}
    break;

  case 53:

    {
						out+= " Copy an object at specific X,Y distance. \r\n\r\n";
						out+= " arraycopy u1 u2 u3 u4 u5 u6  \r\n\r\n";
						out+= " example 1: array copy the selected object on 3 rows sparated by 200 units and 4 columns separated by 400 units \r\n\r\n";
						out+= " arraycopy 3 200 4 400 1 0  \r\n\r\n";
					;}
    break;

  case 54:

    {
						out+= " Direct the camera to look at a specific point. \r\n\r\n";
						out+= " lookat point  \r\n\r\n";
					;}
    break;

  case 55:

    {
						out+= " Rotate the camera by a specific angle. \r\n\r\n";
						out+= " rotatecam xangle yangle  \r\n\r\n";
						out+= " example 1: Rotate the camera by 45 deg \r\n\r\n";
						out+= " rotatecam 45 0  \r\n\r\n";
					;}
    break;

  case 56:

    {
						out+= "Swivel the camera by specific distance in X,Y. \r\n\r\n";
						out+= " swivel xangle yangle  \r\n\r\n";
						out+= " example 1: Swivel the camera by 45 deg \r\n\r\n";
						out+= " swivel 45 0  \r\n\r\n";
					;}
    break;

  case 57:

    {
						out+= " Move the camera to a specific point \r\n\r\n";
						out+= " movecam point  \r\n\r\n";
						out+= " example 1: Move the camera by the vector (200,300) \r\n\r\n";
						out+= " movecam 200 300  \r\n\r\n";
					;}
    break;

  case 58:

    {
						out+= " Zoom the camera to a specific ratio \r\n\r\n";
						out+= " zoom 1.5  \r\n\r\n";
						out+= " example 1: Zoom the camera by 2 \r\n\r\n";
						out+= " zoom 2  \r\n\r\n";
					;}
    break;

  case 59:

    { 
//	                                float f1=vf.front();vf.pop();
	//                                float f2=vf.front();vf.pop();
									while(!vf.empty())
									{
		                                float f1=vf.front();vf.pop();
										fvec.push_back(f1);
									}
								;}
    break;

  case 60:

    { 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									pvec.push_back(CVector(f1,f2));
									int n=pvec.size();
								    pDoc->m_objects->setcurrPoint(pvec[n-1]);
								;}
    break;

  case 61:

    { 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
	                                float f3=vf.front();vf.pop();
									pvec.push_back(CVector(f1,f2,f3));
									int n=pvec.size();
								    pDoc->m_objects->setcurrPoint(pvec[n-1]);
								;}
    break;

  case 62:

    { 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									f2=(f2*pi)/180;
									CVector v = polarc(f1,f2);
									pvec.push_back(v);
									int n=pvec.size();
								    pDoc->m_objects->setcurrPoint(pvec[n-1]);
								;}
    break;

  case 63:

    { 
									int n=pvec.size();
									CVector v;
								    pDoc->m_objects->getfromPoint(pvec);
								    pDoc->m_objects->setcurrPoint(pvec[n-1]);									
								;}
    break;

  case 68:

    { 
	                //                float f1=vf.front();vf.pop();
						//			vf.push(f1);
								;}
    break;

  case 69:

    {
									vf.push(pi);
								;}
    break;

  case 70:

    { 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									f2=f1/f2;
									vf.push(f2);
								;}
    break;

  case 71:

    { 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									f2=f1*f2;
									vf.push(f2);
								;}
    break;

  case 72:

    { 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									f2=f1-f2;
									vf.push(f2);
								;}
    break;

  case 73:

    { 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									f2=f1+f2;
									vf.push(f2);
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



       
