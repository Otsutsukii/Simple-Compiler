
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



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "yacc1.y"

#define _GNU_SOURCE	
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
//#include "yacc1.tab.h"
extern int nextname();
int yyerror(char* s) {
	fprintf(stderr, "%s\n", s);
}
#define STR(VAR) (#VAR)
int yylex();
FILE *yyin;
FILE *yyout;
FILE *outfile;
int yylineno;
char* integer="INT";
char* none = "none";
char* assign = "=";
char* tab="   ";
char indent[100]="";
void incIndent(){
    strcat(indent, tab);
}
void decIndent(){
    int len = strlen(indent);
    indent[len-2]='\0';
}
struct Arbre {
    struct Arbre *enfant[10000];
	int name;
    char* type_noeud;
    char* nom_expr;
    char* valeur;
    char* dataType;
    int lineNo;
    int nbr_enfants;
};
typedef struct list_f {
	struct Arbre *val;
	struct list_f *next;
}list_f;
struct list_f *listprogramme;
struct list_f *cons(struct Arbre *node, struct list_f *list) {
	struct list_f *newlist =(struct list_f*) malloc(sizeof(struct list_f));
	newlist->val = node;
	newlist->next = list;
	return newlist;
}
void freelist(struct list_f *list) {
	if (list == NULL) return;
	freelist(list->next);
	free(list);
}
struct Arbre * creation_noeud(int lineNo,char* type_noeud, char* nom_expr, char* valeur, char* dataType, int nbr_enfants, ...){
    struct Arbre * noeud = (struct Arbre*) malloc(sizeof(struct Arbre));
    noeud->type_noeud = type_noeud;
    noeud->nom_expr = nom_expr;
    noeud->valeur= valeur;
    noeud->dataType = dataType;
    noeud->lineNo = lineNo;
    noeud->nbr_enfants = nbr_enfants;
	noeud->name = 0;
    va_list ap;
    int i;
    va_start(ap, nbr_enfants);
    for (int i=0; i < nbr_enfants; i++)
	{
        noeud->enfant[i]=va_arg(ap, struct Arbre *);
    }
    va_end(ap);
    return noeud;
}
void printNode(struct Arbre *node){
	if(node == NULL){printf("NULL... \n");}
	else{
    printf("%s<Tree lineNo=\"%d\" nodeType=\"%s\" string=\"%s\" value=\"%s\" dataType=\"%s\" name= %d>\n", 
        indent,
        node->lineNo,
        node->type_noeud,
        node->nom_expr,
        node->valeur, 
        node->dataType,node->name);
    int i;
    if (node->nbr_enfants > 0){
        printf("%s< %d Child>\n", indent,node->nbr_enfants);
        incIndent();
        for (i=0;i<node->nbr_enfants;i++){
            printNode(node->enfant[i]);
        }
        decIndent();
        printf("%s</Child>\n", indent);
    }
    printf("%s</Tree>\n", indent);
}}
void printnodeDOT(struct Arbre* node,int parentName) {
	if (node == NULL){return;}
	else{
	if (node->name != 0){ //printf("%d %s\n", node->name, node->type_noeud);
							 fprintf(outfile,"%d %s\n", node->name, node->type_noeud);
							}
	if (node->nbr_enfants > 0){
	for (int i=0;i<node->nbr_enfants;i++) {
		struct Arbre* fils = node->enfant[i];
		if(fils != NULL){
			if(node->name != 0 ){
				printnodeDOT(fils,node->name);
			}
			else{
				printnodeDOT(fils,parentName);
			}
			
		}
		if(fils->name != 0 && node->name != 0){
			//printf("%d -> %d \n", node->name, fils->name);
			fprintf(outfile,"%d -> %d \n", node->name, fils->name);
		}
		else if (fils->name != 0 && node->name == 0){
			//printf("%d -> %d \n",  parentName,fils->name);
			fprintf(outfile,"%d -> %d \n",  parentName,fils->name);
		}
	}}}}
void printlistDOT(struct list_f *list) {
	if (list == NULL) return;
	printnodeDOT(list->val,0);
	printlistDOT(list->next);
}
void printlist(struct list_f *list) {
	if (list == NULL) return;
	printNode(list->val);
	printlist(list->next);
}


/* Line 189 of yacc.c  */
#line 210 "yacc1.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
     IDENTIFICATEUR = 258,
     CONSTANTE = 259,
     VOID = 260,
     INT = 261,
     FOR = 262,
     WHILE = 263,
     IF = 264,
     ELSE = 265,
     SWITCH = 266,
     CASE = 267,
     DEFAULT = 268,
     BREAK = 269,
     RETURN = 270,
     PLUS = 271,
     MOINS = 272,
     MUL = 273,
     DIV = 274,
     LSHIFT = 275,
     RSHIFT = 276,
     BAND = 277,
     BOR = 278,
     LAND = 279,
     LOR = 280,
     LT = 281,
     GT = 282,
     GEQ = 283,
     LEQ = 284,
     EQ = 285,
     NEQ = 286,
     NOT = 287,
     EXTERN = 288,
     THEN = 289,
     OP = 290,
     REL = 291
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 137 "yacc1.y"

    char* str;
    struct Arbre *ast;
	struct list_f *list;



/* Line 214 of yacc.c  */
#line 290 "yacc1.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 302 "yacc1.tab.c"

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   258

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNRULES -- Number of states.  */
#define YYNSTATES  158

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      35,    36,     2,     2,    41,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    40,
       2,    34,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    43,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    37,
      38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     9,    10,    13,    15,    19,    23,
      25,    27,    32,    39,    47,    49,    51,    55,    57,    58,
      61,    64,    66,    68,    70,    72,    75,    77,    79,    89,
      95,   101,   109,   117,   123,   128,   129,   132,   135,   139,
     143,   148,   154,   156,   161,   163,   168,   172,   176,   180,
     184,   188,   192,   196,   200,   204,   207,   209,   211,   216,
     220,   222,   223,   228,   232,   236,   240,   242,   244,   246,
     248,   250,   252,   254
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    49,    50,    -1,    49,    51,    -1,    -1,
      50,    54,    -1,    54,    -1,    55,    52,    40,    -1,    52,
      41,    53,    -1,    53,    -1,     3,    -1,    53,    42,     4,
      43,    -1,    55,     3,    35,    56,    36,    65,    -1,    33,
      55,     3,    35,    56,    36,    40,    -1,     5,    -1,     6,
      -1,    56,    41,    57,    -1,    57,    -1,    -1,     6,     3,
      -1,    58,    59,    -1,    59,    -1,    60,    -1,    61,    -1,
      63,    -1,    64,    40,    -1,    65,    -1,    66,    -1,     7,
      35,    64,    40,    71,    40,    64,    36,    59,    -1,     8,
      35,    71,    36,    59,    -1,     9,    35,    71,    36,    59,
      -1,     9,    35,    71,    36,    59,    10,    59,    -1,    11,
      35,    69,    36,    44,    62,    45,    -1,    62,    12,     4,
      46,    58,    -1,    62,    13,    46,    58,    -1,    -1,    14,
      40,    -1,    15,    40,    -1,    15,    69,    40,    -1,    67,
      34,    69,    -1,    44,    49,    58,    45,    -1,     3,    35,
      70,    36,    40,    -1,     3,    -1,    68,    42,    69,    43,
      -1,     3,    -1,    68,    42,    69,    43,    -1,    35,    69,
      36,    -1,    69,    16,    69,    -1,    69,    17,    69,    -1,
      69,    18,    69,    -1,    69,    19,    69,    -1,    69,    20,
      69,    -1,    69,    21,    69,    -1,    69,    22,    69,    -1,
      69,    23,    69,    -1,    17,    69,    -1,     4,    -1,    67,
      -1,     3,    35,    70,    36,    -1,    70,    41,    69,    -1,
      69,    -1,    -1,    32,    35,    71,    36,    -1,    71,    72,
      71,    -1,    35,    71,    36,    -1,    69,    73,    69,    -1,
      24,    -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,
      29,    -1,    30,    -1,    31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   162,   162,   165,   166,   169,   170,   173,   176,   177,
     180,   181,   184,   188,   191,   192,   195,   196,   197,   200,
     203,   204,   207,   208,   209,   210,   211,   212,   215,   216,
     219,   220,   221,   226,   232,   235,   238,   239,   240,   243,
     246,   249,   253,   257,   271,   275,   279,   280,   283,   286,
     289,   292,   295,   298,   301,   304,   305,   306,   307,   312,
     313,   314,   317,   318,   319,   320,   329,   330,   335,   336,
     337,   338,   339,   340
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFICATEUR", "CONSTANTE", "VOID",
  "INT", "FOR", "WHILE", "IF", "ELSE", "SWITCH", "CASE", "DEFAULT",
  "BREAK", "RETURN", "PLUS", "MOINS", "MUL", "DIV", "LSHIFT", "RSHIFT",
  "BAND", "BOR", "LAND", "LOR", "LT", "GT", "GEQ", "LEQ", "EQ", "NEQ",
  "NOT", "EXTERN", "'='", "'('", "')'", "THEN", "OP", "REL", "';'", "','",
  "'['", "']'", "'{'", "'}'", "':'", "$accept", "programme",
  "liste_declarations", "liste_fonctions", "declaration",
  "liste_declarateurs", "declarateur", "fonction", "type", "liste_parms",
  "parm", "liste_instructions", "instruction", "iteration", "selection",
  "selection_switch", "saut", "affectation", "bloc", "appel", "variable",
  "variable_tab", "expression", "liste_expressions", "condition",
  "binary_rel", "binary_comp", 0
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
     285,   286,   287,   288,    61,    40,    41,   289,   290,   291,
      59,    44,    91,    93,   123,   125,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    51,    52,    52,
      53,    53,    54,    54,    55,    55,    56,    56,    56,    57,
      58,    58,    59,    59,    59,    59,    59,    59,    60,    60,
      61,    61,    61,    62,    62,    62,    63,    63,    63,    64,
      65,    66,    67,    67,    68,    68,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    70,
      70,    70,    71,    71,    71,    71,    72,    72,    73,    73,
      73,    73,    73,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     1,     3,     3,     1,
       1,     4,     6,     7,     1,     1,     3,     1,     0,     2,
       2,     1,     1,     1,     1,     2,     1,     1,     9,     5,
       5,     7,     7,     5,     4,     0,     2,     2,     3,     3,
       4,     5,     1,     4,     1,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     4,     3,
       1,     0,     4,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     1,    14,    15,     0,     2,     3,     6,
       0,     0,     5,     0,    10,     0,     9,     0,     0,    18,
       7,     0,     0,    18,     0,     0,    17,    10,     8,     0,
       0,    19,     0,     0,    11,     0,     4,    12,    16,    13,
       0,    42,     0,     0,     0,     0,     0,     0,     0,     0,
      21,    22,    23,    24,     0,    26,    27,     0,     0,    61,
       0,     0,     0,     0,    36,    42,    56,     0,     0,    37,
      57,     0,    40,    20,    25,     0,     0,    60,     0,    42,
       0,     0,     0,     0,     0,     0,     0,    61,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
       0,     0,     0,     0,     0,     0,     0,    68,    69,    70,
      71,    72,    73,     0,    66,    67,     0,     0,     0,     0,
       0,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      43,    41,    59,     0,     0,    64,    65,    29,    63,    30,
      35,    58,     0,    62,     0,     0,     0,    31,     0,     0,
      32,     0,     0,     0,    28,     0,    34,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     8,    15,    16,     9,    10,    25,
      26,    49,    50,    51,    52,   145,    53,    54,    55,    56,
      70,    58,    83,    78,    84,   117,   113
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -119
static const yytype_int16 yypact[] =
{
    -119,     8,    49,  -119,  -119,  -119,    51,    49,  -119,  -119,
      36,    39,  -119,    70,    42,    66,    59,    46,    42,   104,
    -119,   118,   119,   104,   144,   -20,  -119,  -119,    59,    86,
      38,  -119,   108,   104,  -119,   113,  -119,  -119,  -119,  -119,
      80,   -25,   121,   122,   137,   138,   114,     1,   118,    19,
    -119,  -119,  -119,  -119,   161,  -119,  -119,   125,   162,    95,
     158,    58,    58,    95,  -119,    30,  -119,    95,    95,  -119,
    -119,   123,  -119,  -119,  -119,    95,    95,   214,    56,   164,
     163,   167,    58,   198,    35,   124,   169,    95,   220,   177,
      95,    95,    95,    95,    95,    95,    95,    95,  -119,   214,
     115,   168,    95,    58,    58,   148,   126,  -119,  -119,  -119,
    -119,  -119,  -119,    95,  -119,  -119,   111,    58,   111,   165,
      64,  -119,   220,   220,   160,   160,   105,   105,  -119,  -119,
     170,  -119,   214,   -11,   186,  -119,   214,  -119,  -119,   197,
    -119,  -119,   158,  -119,   111,    -1,   187,  -119,   240,   199,
    -119,   111,   200,   111,  -119,   111,   111,   111
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -119,  -119,   211,  -119,  -119,  -119,   227,   242,     0,   228,
     217,  -118,   -48,  -119,  -119,  -119,  -119,   -58,   221,  -119,
     -40,  -119,   -44,   171,   -37,  -119,  -119
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -46
static const yytype_int16 yytable[] =
{
      57,    73,    80,    71,    65,    66,    11,    13,     3,    57,
      59,   148,   149,   114,   115,    77,    32,   -44,    67,    86,
      57,    33,    41,    88,    89,    85,    42,    43,    44,   142,
      45,    99,   100,    46,    47,   156,    68,   157,   105,    14,
      48,    69,    17,    77,   150,   106,   122,   123,   124,   125,
     126,   127,   128,   129,     4,     5,     4,     5,   132,   114,
     115,    65,    66,    36,    72,    87,   133,   134,   137,   136,
     139,   116,   -44,    18,    35,    67,    57,    19,    57,    33,
     138,    23,     6,    41,   146,     4,     5,    42,    43,    44,
      81,    45,   101,    82,    46,    47,   147,   102,    65,    66,
     141,    22,    57,   154,    57,   102,    20,    21,    73,    73,
      24,    57,    67,    57,    41,    57,    57,    57,    42,    43,
      44,    27,    45,    29,    36,    46,    47,    96,    97,    34,
      68,    90,    91,    92,    93,    94,    95,    96,    97,    90,
      91,    92,    93,    94,    95,    96,    97,    31,   114,   115,
     114,   115,    36,    39,    64,    36,    60,    61,   130,    75,
     118,    79,   135,    98,    90,    91,    92,    93,    94,    95,
      96,    97,    62,    63,   107,   108,   109,   110,   111,   112,
      94,    95,    96,    97,   121,    90,    91,    92,    93,    94,
      95,    96,    97,    90,    91,    92,    93,    94,    95,    96,
      97,    74,   104,   103,    76,   119,   -44,   144,   131,   140,
     114,   115,   -45,   121,    90,    91,    92,    93,    94,    95,
      96,    97,   143,   151,   107,   108,   109,   110,   111,   112,
      90,    91,    92,    93,    94,    95,    96,    97,    92,    93,
      94,    95,    96,    97,   152,   153,   155,    40,    28,    12,
      38,    30,     0,    37,     0,     0,     0,     0,   120
};

static const yytype_int16 yycheck[] =
{
      40,    49,    60,    47,     3,     4,     6,     7,     0,    49,
      35,    12,    13,    24,    25,    59,    36,    42,    17,    63,
      60,    41,     3,    67,    68,    62,     7,     8,     9,    40,
      11,    75,    76,    14,    15,   153,    35,   155,    82,     3,
      40,    40,     3,    87,    45,    82,    90,    91,    92,    93,
      94,    95,    96,    97,     5,     6,     5,     6,   102,    24,
      25,     3,     4,    44,    45,    35,   103,   104,   116,   113,
     118,    36,    42,     3,    36,    17,   116,    35,   118,    41,
     117,    35,    33,     3,   142,     5,     6,     7,     8,     9,
      32,    11,    36,    35,    14,    15,   144,    41,     3,     4,
      36,    42,   142,   151,   144,    41,    40,    41,   156,   157,
       6,   151,    17,   153,     3,   155,   156,   157,     7,     8,
       9,     3,    11,     4,    44,    14,    15,    22,    23,    43,
      35,    16,    17,    18,    19,    20,    21,    22,    23,    16,
      17,    18,    19,    20,    21,    22,    23,     3,    24,    25,
      24,    25,    44,    40,    40,    44,    35,    35,    43,    34,
      36,     3,    36,    40,    16,    17,    18,    19,    20,    21,
      22,    23,    35,    35,    26,    27,    28,    29,    30,    31,
      20,    21,    22,    23,    36,    16,    17,    18,    19,    20,
      21,    22,    23,    16,    17,    18,    19,    20,    21,    22,
      23,    40,    35,    40,    42,    36,    42,    10,    40,    44,
      24,    25,    42,    36,    16,    17,    18,    19,    20,    21,
      22,    23,    36,    36,    26,    27,    28,    29,    30,    31,
      16,    17,    18,    19,    20,    21,    22,    23,    18,    19,
      20,    21,    22,    23,     4,    46,    46,    36,    21,     7,
      33,    23,    -1,    32,    -1,    -1,    -1,    -1,    87
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,    49,     0,     5,     6,    33,    50,    51,    54,
      55,    55,    54,    55,     3,    52,    53,     3,     3,    35,
      40,    41,    42,    35,     6,    56,    57,     3,    53,     4,
      56,     3,    36,    41,    43,    36,    44,    65,    57,    40,
      49,     3,     7,     8,     9,    11,    14,    15,    55,    58,
      59,    60,    61,    63,    64,    65,    66,    67,    68,    35,
      35,    35,    35,    35,    40,     3,     4,    17,    35,    40,
      67,    69,    45,    59,    40,    34,    42,    69,    70,     3,
      64,    32,    35,    69,    71,    71,    69,    35,    69,    69,
      16,    17,    18,    19,    20,    21,    22,    23,    40,    69,
      69,    36,    41,    40,    35,    69,    71,    26,    27,    28,
      29,    30,    31,    73,    24,    25,    36,    72,    36,    36,
      70,    36,    69,    69,    69,    69,    69,    69,    69,    69,
      43,    40,    69,    71,    71,    36,    69,    59,    71,    59,
      44,    36,    40,    36,    10,    62,    64,    59,    12,    13,
      45,    36,     4,    46,    59,    46,    58,    58
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
        case 2:

/* Line 1455 of yacc.c  */
#line 162 "yacc1.y"
    {listprogramme = (yyvsp[(2) - (2)].list); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 166 "yacc1.y"
    {(yyval.ast)=NULL;;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 169 "yacc1.y"
    {(yyval.list) = cons((yyvsp[(2) - (2)].ast), (yyvsp[(1) - (2)].list)); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 170 "yacc1.y"
    {(yyval.list) = cons((yyvsp[(1) - (1)].ast), NULL);;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 184 "yacc1.y"
    {
			char* buffer = NULL;
asprintf(&buffer, "[label=\"%s, %s\" shape=invtrapezium color=blue]", (yyvsp[(2) - (6)].str), (yyvsp[(1) - (6)].str));
								(yyval.ast)=creation_noeud(yylineno,buffer, (yyvsp[(2) - (6)].str), none, (yyvsp[(1) - (6)].str),  1,(yyvsp[(6) - (6)].ast));(yyval.ast)->name = nextname();;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 188 "yacc1.y"
    {(yyval.ast) = NULL; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 191 "yacc1.y"
    {(yyval.str)="VOID";;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 192 "yacc1.y"
    {(yyval.str)="INT";;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 195 "yacc1.y"
    {(yyval.ast) = creation_noeud(yylineno,"liste_parms", none, none, "integer",  2, (yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast));;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 196 "yacc1.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 197 "yacc1.y"
    {(yyval.ast)=NULL;;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 200 "yacc1.y"
    {(yyval.ast) = creation_noeud(yylineno,"parm", none, none, "INT",  0);;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 203 "yacc1.y"
    {int nb = (yyvsp[(1) - (2)].ast)->nbr_enfants;(yyvsp[(1) - (2)].ast)->nbr_enfants= (yyvsp[(1) - (2)].ast)->nbr_enfants+1 ;(yyvsp[(1) - (2)].ast)->enfant[nb] = (yyvsp[(2) - (2)].ast);(yyval.ast)=(yyvsp[(1) - (2)].ast);;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 204 "yacc1.y"
    { (yyval.ast) =creation_noeud(yylineno,"listes interne", none, none, none,  1,(yyvsp[(1) - (1)].ast));;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 207 "yacc1.y"
    {(yyval.ast) =(yyvsp[(1) - (1)].ast);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 208 "yacc1.y"
    {(yyval.ast) =(yyvsp[(1) - (1)].ast);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 209 "yacc1.y"
    {(yyval.ast) =(yyvsp[(1) - (1)].ast);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 210 "yacc1.y"
    {(yyval.ast) = (yyvsp[(1) - (2)].ast);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 211 "yacc1.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 212 "yacc1.y"
    {(yyval.ast) =(yyvsp[(1) - (1)].ast);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 215 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label=\"FOR\"]", none, none, "INT",  4, (yyvsp[(3) - (9)].ast),(yyvsp[(5) - (9)].ast),(yyvsp[(7) - (9)].ast),(yyvsp[(9) - (9)].ast));(yyval.ast)->name = nextname();;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 216 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label=\"WHILE\"]", none, none, none,  2, (yyvsp[(3) - (5)].ast), (yyvsp[(5) - (5)].ast));(yyval.ast)->name = nextname();;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 219 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label=\"IF\" shape=diamond]", none, none,none,  2, (yyvsp[(3) - (5)].ast),(yyvsp[(5) - (5)].ast));(yyval.ast)->name = nextname();;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 220 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label=\"IF\" shape=diamond]", none, none, none,  3, (yyvsp[(3) - (7)].ast),(yyvsp[(5) - (7)].ast),(yyvsp[(7) - (7)].ast));(yyval.ast)->name = nextname();;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 221 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label=\"SWITCH\"]", none, none, none,  1,(yyvsp[(6) - (7)].ast));(yyval.ast)->name = nextname();;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 226 "yacc1.y"
    {
			char* buffer = NULL;
			asprintf(&buffer, "[label=\"CASE %s\"]", (yyvsp[(3) - (5)].ast) );
			struct Arbre *tree =creation_noeud(yylineno,buffer, none, none,none,  1, (yyvsp[(5) - (5)].ast));tree->name = nextname();
			int nb = (yyvsp[(1) - (5)].ast)->nbr_enfants;(yyvsp[(1) - (5)].ast)->nbr_enfants= (yyvsp[(1) - (5)].ast)->nbr_enfants+1 ;(yyvsp[(1) - (5)].ast)->enfant[nb] =tree;(yyval.ast)=(yyvsp[(1) - (5)].ast);
		;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 232 "yacc1.y"
    {
			struct Arbre *tree  = creation_noeud(yylineno,"[label=\"DEFAULT\"]", none, none, none,  1, (yyvsp[(4) - (4)].ast));tree->name = nextname();
			int nb = (yyval.ast)->nbr_enfants;(yyval.ast)->nbr_enfants= (yyval.ast)->nbr_enfants+1 ;(yyval.ast)->enfant[nb] =tree;;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 235 "yacc1.y"
    { (yyval.ast) =creation_noeud(yylineno,"listes interne", none, none, none,  0); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 238 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label=\"BREAK\" shape=box]", "break", none,none,  0);(yyval.ast)->name = nextname();;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 239 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label=\"RETURN\" shape=trapezium color=blue]" , "return", none,none,  0);(yyval.ast)->name = nextname();;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 240 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label=\"RETURN\" shape=trapezium color=blue]", none, none,none,  1, (yyvsp[(2) - (3)].ast));(yyval.ast)->name = nextname();;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 243 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label=\":=\"]", (yyvsp[(1) - (3)].ast)->nom_expr, none,none,  2,(yyvsp[(1) - (3)].ast) ,(yyvsp[(3) - (3)].ast));(yyval.ast)->name =nextname();;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 246 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label=\"BLOC\"]", none, none,none,  1 ,(yyvsp[(3) - (4)].ast));(yyval.ast)->name = nextname();;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 249 "yacc1.y"
    {char* buffer = NULL;
asprintf(&buffer, "[label=\"%s\" shape=septagon]", (yyvsp[(1) - (5)].str));(yyval.ast) =creation_noeud(yylineno,buffer, none, none,none,  1,(yyvsp[(3) - (5)].ast));(yyval.ast)->name = nextname();;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 253 "yacc1.y"
    {char* buffer = NULL;
						asprintf(&buffer, "[label=\"%s\"]", (yyvsp[(1) - (1)].str));
						(yyval.ast) =creation_noeud(yylineno,buffer, (yyvsp[(1) - (1)].str), none,"var",  0);
						(yyval.ast)->name = nextname();;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 257 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label=\"TAB\"]", none, none,none, 0);(yyval.ast)->name = nextname();
										
										int nb = (yyval.ast)->nbr_enfants;(yyval.ast)->nbr_enfants= (yyval.ast)->nbr_enfants+1 ;(yyval.ast)->enfant[nb] =(yyvsp[(1) - (4)].ast);
										struct Arbre *node = (yyvsp[(1) - (4)].ast);
										for (int i=0;i<node->nbr_enfants;i++) {
											struct Arbre* fils = node->enfant[i];
											int nb = (yyval.ast)->nbr_enfants;(yyval.ast)->nbr_enfants= (yyval.ast)->nbr_enfants+1 ;(yyval.ast)->enfant[nb] =fils;
											
										}
										(yyvsp[(1) - (4)].ast)->nbr_enfants=0;
										nb = (yyval.ast)->nbr_enfants;(yyval.ast)->nbr_enfants= (yyval.ast)->nbr_enfants+1 ;(yyval.ast)->enfant[nb] =(yyvsp[(3) - (4)].ast);
										;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 271 "yacc1.y"
    {char* buffer = NULL;
						asprintf(&buffer, "[label=\"%s\"]", (yyvsp[(1) - (1)].str));
						(yyval.ast) =creation_noeud(yylineno,buffer, (yyvsp[(1) - (1)].str), none,"var",  0);
						(yyval.ast)->name = nextname();;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 275 "yacc1.y"
    {
										int nb = (yyval.ast)->nbr_enfants;(yyval.ast)->nbr_enfants= (yyval.ast)->nbr_enfants+1 ;(yyval.ast)->enfant[nb] =(yyvsp[(3) - (4)].ast);(yyval.ast)=(yyvsp[(1) - (4)].ast);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 279 "yacc1.y"
    {(yyval.ast) = (yyvsp[(2) - (3)].ast);;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 280 "yacc1.y"
    {
                                           (yyval.ast)= creation_noeud(yylineno,"[label= \"+\"]", "+", none, none,2 );(yyval.ast)->name = nextname();(yyval.ast)->enfant[0] = (yyvsp[(1) - (3)].ast);(yyval.ast)->enfant[1] = (yyvsp[(3) - (3)].ast);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 283 "yacc1.y"
    {
                                           (yyval.ast)= creation_noeud(yylineno,"[label= \"-\"]", "-", none, none,2 );(yyval.ast)->name = nextname();(yyval.ast)->enfant[0] = (yyvsp[(1) - (3)].ast);(yyval.ast)->enfant[1] = (yyvsp[(3) - (3)].ast);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 286 "yacc1.y"
    {
                                           (yyval.ast)= creation_noeud(yylineno,"[label= \"*\"]", "*", none, none,2  );(yyval.ast)->name = nextname();(yyval.ast)->enfant[0] = (yyvsp[(1) - (3)].ast);(yyval.ast)->enfant[1] = (yyvsp[(3) - (3)].ast);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 289 "yacc1.y"
    {
                                           (yyval.ast)= creation_noeud(yylineno,"[label= \"/\"]", "/", none, none,2  );(yyval.ast)->name = nextname();(yyval.ast)->enfant[0] = (yyvsp[(1) - (3)].ast);(yyval.ast)->enfant[1] = (yyvsp[(3) - (3)].ast);;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 292 "yacc1.y"
    {
                                           (yyval.ast)= creation_noeud(yylineno,"[label= \"<<\"]", "<<", none, none,2  );(yyval.ast)->name = nextname();(yyval.ast)->enfant[0] = (yyvsp[(1) - (3)].ast);(yyval.ast)->enfant[1] = (yyvsp[(3) - (3)].ast);;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 295 "yacc1.y"
    {
                                           (yyval.ast)= creation_noeud(yylineno,"[label= \">>\"]", ">>", none, none,2  );(yyval.ast)->name = nextname();(yyval.ast)->enfant[0] = (yyvsp[(1) - (3)].ast);(yyval.ast)->enfant[1] = (yyvsp[(3) - (3)].ast);;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 298 "yacc1.y"
    {
                                           (yyval.ast)= creation_noeud(yylineno,"[label= \"&\"]", "&", none, none,2  );(yyval.ast)->name = nextname();(yyval.ast)->enfant[0] = (yyvsp[(1) - (3)].ast);(yyval.ast)->enfant[1] = (yyvsp[(3) - (3)].ast);;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 301 "yacc1.y"
    {
                                           (yyval.ast)= creation_noeud(yylineno,"[label= \"|\"]", "|", none, none, 2 );(yyval.ast)->name = nextname();(yyval.ast)->enfant[0] = (yyvsp[(1) - (3)].ast);(yyval.ast)->enfant[1] = (yyvsp[(3) - (3)].ast);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 304 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label= \"-\"]", none, none,none,  1,(yyvsp[(2) - (2)].ast));(yyval.ast)->name = nextname();;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 305 "yacc1.y"
    {char* b = NULL;asprintf(&b, "[label=\"%s\"]", (yyvsp[(1) - (1)].ast));  (yyval.ast) =creation_noeud(yylineno,b,none,b,none,  0);(yyval.ast)->name = nextname();;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 306 "yacc1.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 307 "yacc1.y"
    {	char* buffer = NULL;
													asprintf(&buffer, "[label=\"%s\" shape=septagon]", (yyvsp[(1) - (4)].str));
													(yyval.ast) =creation_noeud(yylineno,buffer, none, none,none,  1,(yyvsp[(3) - (4)].ast));(yyval.ast)->name = nextname();;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 312 "yacc1.y"
    {int nb = (yyvsp[(3) - (3)].ast)->nbr_enfants;(yyvsp[(3) - (3)].ast)->nbr_enfants= (yyvsp[(3) - (3)].ast)->nbr_enfants+1 ;(yyvsp[(3) - (3)].ast)->enfant[nb] = (yyvsp[(1) - (3)].ast);(yyval.ast)=(yyvsp[(3) - (3)].ast); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 313 "yacc1.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 314 "yacc1.y"
    { (yyval.ast) = NULL; ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 317 "yacc1.y"
    { (yyval.ast) =creation_noeud(yylineno,"NOT", none, none,none,  1,(yyvsp[(3) - (4)].ast));(yyval.ast)->name = nextname();;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 319 "yacc1.y"
    { (yyval.ast) = (yyvsp[(2) - (3)].ast);;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 320 "yacc1.y"
    {int nb = (yyvsp[(2) - (3)].ast)->nbr_enfants;
											(yyvsp[(2) - (3)].ast)->nbr_enfants= (yyvsp[(2) - (3)].ast)->nbr_enfants+2 ;
											(yyvsp[(2) - (3)].ast)->enfant[nb] = (yyvsp[(1) - (3)].ast);
											(yyvsp[(2) - (3)].ast)->enfant[nb+1] = (yyvsp[(3) - (3)].ast);
											(yyval.ast)=(yyvsp[(2) - (3)].ast); 
											;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 329 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label= \"&&\"]", "&&", none,none, 0);(yyval.ast)->name = nextname();;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 330 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label= \"||\"]", "||", none,none, 0);(yyval.ast)->name = nextname();;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 335 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label= \"<\"]", "<", none,none,0);(yyval.ast)->name = nextname();;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 336 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label= \">\"]", ">", none,none, 0);(yyval.ast)->name = nextname();;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 337 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label= \">=\"]", ">=", none,none,0);(yyval.ast)->name = nextname();;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 338 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label= \"<=\"]", "<=", none,none, 0);(yyval.ast)->name = nextname();;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 339 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label= \"==\"]", "==", none,none, 0);(yyval.ast)->name = nextname();;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 340 "yacc1.y"
    {(yyval.ast) =creation_noeud(yylineno,"[label= \"!=\"]", "!=", none,none, 0);(yyval.ast)->name = nextname();;}
    break;



/* Line 1455 of yacc.c  */
#line 2148 "yacc1.tab.c"
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



/* Line 1675 of yacc.c  */
#line 342 "yacc1.y"

int name = 1;
int nextname() {
	return name++;
}
int yywrap() {}
void main(int args,char** argv)
{
	if (args > 1)
	{
    		FILE *file;
    		file = fopen(argv[1], "r");
    		if (!file)
    		{
    		    fprintf(stderr, "failed open");
        		exit(1);
    		}
    		yyin=file;
    		//printf("success open %s\n", argv[1]);
	}
	else
	{
    		printf("no input file\n");
    		exit(1);
	}
		int res = yyparse();  
		if (res != 0) exit(1);
		//printlist(listprogramme);
		outfile = fopen("file.dot", "w");
		if (outfile == NULL)
			{
				printf("Error opening file!\n");
				exit(1);
			}
		fprintf(outfile,"digraph G { \n");
		printlistDOT(listprogramme);
		fprintf(outfile,"}");
		fclose(outfile);
}




