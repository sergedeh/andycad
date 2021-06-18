
/*  A Bison parser, made from .\andy.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse andyparse
#define yylex andylex
#define yyerror andyerror
#define yylval andylval
#define yychar andychar
#define yydebug andydebug
#define yynerrs andynerrs
#define	line	258
#define	rect	259
#define	circle	260
#define	qline	261
#define	ellipse	262
#define	arc	263
#define	spline	264
#define	MOVE	265
#define	MOVENODE	266
#define	ROTATE	267
#define	object	268
#define	num	269
#define	SCALE	270
#define	SCALE2	271
#define	ANGCOPY	272
#define	POLARCOPY	273
#define	ARRAYCOPY	274
#define	LOOKAT	275
#define	ROTATECAM	276
#define	SWIVEL	277
#define	ZOOM	278
#define	MOVECAM	279
#define	MOVETO	280
#define	MOVENODETO	281
#define	error2	282
#define	MODEL	283


#include <malloc.h>
#define alloc _alloc
#include <stdio.h>
#include <vector>
using namespace std;


vector<CVector> pvec;
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

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		102
#define	YYFLAG		-32768
#define	YYNTBASE	34

#define YYTRANSLATE(x) ((unsigned)(x) <= 283 ? yytranslate[x] : 40)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    29,     2,     2,    33,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
     2,    31,     2,    32,     2,     2,     2,     2,     2,     2,
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
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     5,     7,    11,    15,    19,    23,    27,
    31,    35,    38,    41,    45,    49,    54,    58,    63,    67,
    70,    76,    82,    90,    94,    98,   102,   105,   109,   111,
   113,   115,   117,   119,   125,   133,   137,   140,   142,   145,
   147
};

static const short yyrhs[] = {    -1,
    34,    35,     0,     0,    36,     0,     3,    37,    38,     0,
     4,    37,    37,     0,     5,    37,    14,     0,     6,    37,
    38,     0,     7,    37,    14,     0,     8,    37,    14,     0,
     9,    37,    38,     0,    10,    37,     0,    25,    37,     0,
    11,    14,    37,     0,    26,    14,    37,     0,    12,    37,
    14,    14,     0,    12,    14,    14,     0,    15,    37,    14,
    14,     0,    15,    14,    14,     0,    16,    14,     0,    17,
    14,    14,    14,    14,     0,    18,    14,    14,    14,    14,
     0,    19,    14,    14,    14,    14,    14,    14,     0,    20,
    37,    37,     0,    21,    14,    14,     0,    22,    14,    14,
     0,    24,    37,     0,    14,    29,    14,     0,    39,     0,
    37,     0,     3,     0,    28,     0,    23,     0,    30,    14,
    29,    14,    31,     0,    30,    14,    29,    14,    29,    14,
    31,     0,    14,    30,    14,     0,    32,    37,     0,    37,
     0,    37,    38,     0,    14,     0,    14,    33,    14,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    30,    31,    33,    38,    41,    49,    52,    59,    62,    65,
    72,    78,    83,    88,    94,   100,   107,   114,   121,   128,
   135,   144,   153,   164,   166,   172,   178,   183,   205,   227,
   248,   253,   258,   262,   269,   276,   284,   290,   291,   292,
   294
};

static const char * const yytname[] = {   "$","error","$undefined.","line","rect",
"circle","qline","ellipse","arc","spline","MOVE","MOVENODE","ROTATE","object",
"num","SCALE","SCALE2","ANGCOPY","POLARCOPY","ARRAYCOPY","LOOKAT","ROTATECAM",
"SWIVEL","ZOOM","MOVECAM","MOVETO","MOVENODETO","error2","MODEL","','","'<'",
"'>'","'@'","'/'","input","Line","expr","point","points","numexpr",""
};
#endif

static const short yyr1[] = {     0,
    34,    34,    35,    35,    36,    36,    36,    36,    36,    36,
    36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
    36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
    36,    36,    36,    37,    37,    37,    37,    38,    38,    39,
    39
};

static const short yyr2[] = {     0,
     0,     2,     0,     1,     3,     3,     3,     3,     3,     3,
     3,     2,     2,     3,     3,     4,     3,     4,     3,     2,
     5,     5,     7,     3,     3,     3,     2,     3,     1,     1,
     1,     1,     1,     5,     7,     3,     2,     1,     2,     1,
     3
};

static const short yydefact[] = {     1,
     0,    31,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    40,     0,     0,     0,     0,     0,     0,     0,     0,
    33,     0,     0,     0,    32,     0,     0,     2,     4,    30,
    29,     0,     0,     0,     0,     0,     0,     0,     0,    12,
     0,     0,     0,     0,     0,     0,     0,     0,    20,     0,
     0,     0,     0,     0,     0,    27,    13,     0,     0,    37,
    38,     5,     6,     7,     8,     9,    10,    11,    14,    17,
     0,    28,    36,    41,    19,     0,     0,     0,     0,    24,
    25,    26,    15,     0,    39,    16,    18,     0,     0,     0,
     0,    21,    22,     0,     0,    34,     0,     0,    23,    35,
     0,     0
};

static const short yydefgoto[] = {     1,
    28,    29,    61,    62,    31
};

static const short yypact[] = {-32768,
    55,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    10,
     2,    12,     5,    14,    15,    16,    24,    -5,    29,    30,
-32768,    -5,    -5,    32,-32768,    33,    -5,-32768,-32768,-32768,
-32768,   -17,    -5,    -5,    34,    -5,    35,    36,    -5,-32768,
    -5,     1,    37,    39,    40,    42,     9,    54,-32768,    68,
    70,    72,    -5,    74,    75,-32768,-32768,    -5,    61,-32768,
    -5,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
    77,-32768,-32768,-32768,-32768,    78,    79,    80,    81,-32768,
-32768,-32768,-32768,    82,-32768,-32768,-32768,    83,    84,    85,
   -11,-32768,-32768,    86,    87,-32768,    88,    73,-32768,-32768,
   103,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,    -1,   -25,-32768
};


#define	YYLAST		104


static const short yytable[] = {    30,
    33,    34,    35,    36,    37,    38,    39,    40,    32,    43,
    65,    48,    45,    68,    70,    42,    53,    95,    47,    96,
    56,    57,    75,    41,    26,    60,    27,    49,    50,    51,
    45,    26,    63,    27,    26,    85,    27,    52,    45,    69,
    44,    45,    54,    55,    46,    58,    59,    64,    66,    67,
    71,    80,    72,    73,   101,    74,    83,     2,     3,     4,
     5,     6,     7,     8,     9,    10,    11,    76,    12,    13,
    14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
    24,    77,    25,    78,    26,    79,    27,    81,    82,    84,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    97,
    98,    99,   102,   100
};

static const short yycheck[] = {     1,
     2,     3,     4,     5,     6,     7,     8,     9,    14,    11,
    36,    13,    30,    39,    14,    14,    18,    29,    14,    31,
    22,    23,    14,    14,    30,    27,    32,    14,    14,    14,
    30,    30,    34,    32,    30,    61,    32,    14,    30,    41,
    29,    30,    14,    14,    33,    14,    14,    14,    14,    14,
    14,    53,    14,    14,     0,    14,    58,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    14,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    14,    28,    14,    30,    14,    32,    14,    14,    29,
    14,    14,    14,    14,    14,    14,    14,    14,    14,    14,
    14,    14,     0,    31
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */


/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif



/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 3:
{ 
							while(!vi.empty())
								vi.pop();
							pvec.clear();
			;
    break;}
case 4:
{ 
							
					;
    break;}
case 5:
{
							if(pvec.size()==2)
								pDoc->m_objects->AddLine(pvec);
							cv=pvec.back();
							pvec.clear(); 
							pView->Invalidate(TRUE);
						;
    break;}
case 6:
{ 
							out+="I am drawing a rectangle\r\n";
						;
    break;}
case 7:
{ 
	                        float f1=vf.front();vf.pop();
							pDoc->m_objects->AddCircle(pvec[0],f1);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						;
    break;}
case 8:
{ 
							out+="I am drawing a qline\r\n";
						;
    break;}
case 9:
{ 
							out+="I am drawing an ellipse\r\n";
						;
    break;}
case 10:
{ 
	                        float f1=vf.front();vf.pop();
							pDoc->m_objects->AddArc(pvec[0],f1);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						;
    break;}
case 11:
{ 
							pDoc->m_objects->AddSpline(pvec);
							cv=pvec.back();
							pvec.clear();
							pView->Invalidate(TRUE);
						;
    break;}
case 12:
{
							pDoc->m_objects->Move(NULL,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;
    break;}
case 13:
{
							pDoc->m_objects->MoveTo(NULL,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;
    break;}
case 14:
{
	                        float f1=vf.front();vf.pop();
							pDoc->m_objects->Move(NULL,f1,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;
    break;}
case 15:
{
	                        float f1=vf.front();vf.pop();
							pDoc->m_objects->MoveTo(NULL,f1,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;
    break;}
case 16:
{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
							pDoc->m_objects->rotate(f1,f2,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;
    break;}
case 17:
{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->rotate(f1,f2);
							pvec.clear();
							pView->Invalidate(TRUE);
						;
    break;}
case 18:
{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->scale(f1,f2,pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
						;
    break;}
case 19:
{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->scale(f1,f2);
							pvec.clear();
							pView->Invalidate(TRUE);
						;
    break;}
case 20:
{
	                        float f1=vf.front();vf.pop();
						    pDoc->m_objects->copy2(f1);
							pvec.clear();
							pView->Invalidate(TRUE);
						;
    break;}
case 21:
{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
	                        float f3=vf.front();vf.pop();
	                        float f4=vf.front();vf.pop();
						    pDoc->m_objects->copyRSparam(NULL,f1,f2,f3,f4,false);
							pView->Invalidate(TRUE);
						;
    break;}
case 22:
{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
	                        float f3=vf.front();vf.pop();
	                        float f4=vf.front();vf.pop();
						    pDoc->m_objects->copyRSparam(NULL,f1,f2,f3,f4,true);
							pView->Invalidate(TRUE);
						;
    break;}
case 23:
{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
	                        float f3=vf.front();vf.pop();
	                        float f4=vf.front();vf.pop();
	                        float f5=vf.front();vf.pop();
	                        float f6=vf.front();vf.pop();
						    pDoc->m_objects->pastearray(NULL,true,f1,f2,f3,f4,f5,f6);
							pView->Invalidate(TRUE);
						;
    break;}
case 24:
{
						;
    break;}
case 25:
{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->rotatecam(f1,f2);
							pView->Invalidate(TRUE);
						;
    break;}
case 26:
{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
						    pDoc->m_objects->rotatecam(f1,f2,true);
							pView->Invalidate(TRUE);
						;
    break;}
case 27:
{
						    pDoc->m_objects->translatecam(pvec[0]);
							pvec.clear();
							pView->Invalidate(TRUE);
					;
    break;}
case 28:
{
	                        float f1=vf.front();vf.pop();
	                        float f2=vf.front();vf.pop();
							if(!vi.empty())
							{
							switch(vi.front())
							{
							case MODEL:
							{
							com="Command:";
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
						;
    break;}
case 29:
{
	                        float f1=vf.front();vf.pop();
							if(!vi.empty())
							{
							switch(vi.front())
							{
							case ZOOM:
							{
							com="Command:";
							pDoc->m_objects->setzoomrat(f1);
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
						;
    break;}
case 30:
{
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
							default:
							;
							}
							}
							else
								out+="No command has been entered";

					;
    break;}
case 31:
{
								com="First point:";
								pvec.clear();
					;
    break;}
case 32:
{
								com="Size of the Model Space (X,Y):";
								pvec.clear();
					;
    break;}
case 33:
{
								com="Enter a scale factor:";
						;
    break;}
case 34:
{ 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();

									pvec.push_back(CVector(f1,f2));
								;
    break;}
case 35:
{ 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
	                                float f3=vf.front();vf.pop();

									pvec.push_back(CVector(f1,f2,f3));
								;
    break;}
case 36:
{ 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									f2=(f2*pi)/180;
									CVector v = polarc(f1,f2);
									pvec.push_back(v);
								;
    break;}
case 37:
{ 
									int n=pvec.size();
									CVector v;
								    pDoc->m_objects->getfromPoint(pvec[n-1]);
									
								;
    break;}
case 41:
{ 
	                                float f1=vf.front();vf.pop();
	                                float f2=vf.front();vf.pop();
									f2=f1/f2;
									vf.push(f2);
								;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */


  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
       