
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

extern YYSTYPE dxflval;


