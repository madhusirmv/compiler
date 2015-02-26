#ifndef _NODE_H
#define _NODE_H

#include <stdio.h>
#include <stdbool.h>

struct type;

#define MAX_IDENTIFIER_LENGTH               31

#define MAX_STR_LENGTH                     509

#define NODE_NUMBER                          0
#define NODE_IDENTIFIER                      1
#define NODE_BINARY_OPERATION                2
#define NODE_EXPRESSION_STATEMENT            3
#define NODE_STATEMENT_LIST                  4
/*added this one*/
#define NODE_STRING                          5
#define NODE_UNARY_OPERATION                 6
#define NODE_FUNCTION_CALL                   7 
#define NODE_COMMA_LIST                      8 
#define NODE_CAST                            9
#define NODE_TERNARY_OPERATION              10
#define NODE_TYPE                           11
#define NODE_DECL                           12
#define NODE_POINTERS                       13
#define NODE_POINTER_DECLARATOR             14
#define NODE_FUCNTION_DECLARATOR            15
#define NODE_ARRAY_DECLARATOR               16
#define NODE_PARAMETER_DECL                 17
#define NODE_TYPE_NAME                      18
#define NODE_LABELED_STATEMENT              19
#define NODE_COMPOUND                       20
#define NODE_CONDITIONAL                    21
#define NODE_OPERATOR                       22

struct result {
  struct type *type;
  struct ir_operand *ir_operand;
};

struct node {
  int kind;
  int line_number;
  struct ir_section *ir;
  union {
    struct {
      unsigned long value;
      bool overflow;
      struct result result;
      int type;
    } number;

    struct {
      char name[MAX_IDENTIFIER_LENGTH + 1];
      struct symbol *symbol;
    } identifier;

    struct {
      char text[MAX_STR_LENGTH + 1];
      int len;
    } string;

    struct {
      int operation;
      struct node *left_operand;
      struct node *right_operand;
      struct result result;
    } binary_operation;

    struct {
      int operation;
      struct node *operand;
      struct result result;
    } unary_operation;

    struct {
      struct node *type;
      struct node *cast;
    } cast;

    struct {
      struct node *expression;
      struct node *args;
    } function_node;

    struct {
      struct node *first;
      struct node *second;
    } comma_list;

    struct{
      struct node *type;
      struct node *cast;
    } function_call;

    struct{
      struct node *log_expr;
      struct node *expr;
      struct node *cond_expr;
    } ternary_operation;

    struct {
      int sign;
      int type;
    } type;

    struct {
      struct node *type;
      struct node *init_decl_list;
    } decl;

    struct {
      struct node *pointers;
    } pointers;

    struct {
      struct node *list;
      struct node *declarator;
    } pointer_declarator;

    struct {
      struct node *dir_dec;
      struct node *params;
    } function_declarator;

    struct {
      struct node *dir_dec;
      struct node *constant;
    } array_declarator; 

    struct {
      struct node *id;
      struct node *statement;
    } labeled_statement;

    struct {
      struct node *type;
      struct node *declarator;
    } parameter_decl;

    struct {
      struct node *type;
      struct node *declarator;
    } type_name;

    struct {
      struct node *statement_list;
    } compound;

    struct {
      struct node *expr;
      struct node *then_statement;
      struct node *else_statement;
    } conditional;

    struct {
      int operation;
    } operation;

    struct {
      struct node *expression;
    } expression_statement;
    struct {
      struct node *init;
      struct node *statement;
    } statement_list;
  } data;
};

/* Binary operations */
#define OP_ASTERISK                       0
#define OP_SLASH                          1
#define OP_PLUS                           2
#define OP_MINUS                          3
#define OP_EQUAL                          4
#define OP_AMPERSAND                      5
#define OP_PLUS_EQUAL                     6
#define OP_MINUS_EQUAL                    7
#define OP_ASTERISK_EQUAL                 8
#define OP_SLASH_EQUAL                    9
#define OP_PERCENT_EQUAL                 10 
#define OP_LESS_LESS_EQUAL               11
#define OP_GREATER_GREATER_EQUAL         12
#define OP_AMPERSAND_EQUAL               13
#define OP_CARET_EQUAL                   14
#define OP_VBAR_EQUAL                    15
#define OP_PERCENT                       16
#define OP_LESS_LESS                     17
#define OP_GREATER_GREATER               18
#define OP_LESS                          19
#define OP_LESS_EQUAL                    20
#define OP_GREATER                       21
#define OP_GREATER_EQUAL                 22
#define OP_EQUAL_EQUAL                   23
#define OP_EXCLAMATION_EQUAL             24
#define OP_VBAR                          25
#define OP_CARET                         26
#define OP_AMPERSAND_AMPERSAND           27
#define OP_VBAR_VBAR                     28
#define OP_PLUS_PLUS                     29
#define OP_MINUS_MINUS                   30


/* Unary operations */
/* #define ASTERISK                       0 */
#define OP_EXCLAMATION                    1
/* #define PLUS                           2 */
/* #define MINUS                          3 */
#define OP_TILDE                          4
#define OP_AMPERSAND                      5

/* Type specifiers */
#define TP_CHAR                           0
#define TP_SHORT                          1
#define TP_INT                            2
#define TP_LONG                           3
#define TP_VOID                           4
#define TP_UNSIGNED                       5
#define TP_SIGNED                         6


/* Constructors */
struct node *node_number(char *text);
struct node *node_identifier(char *text, int length);
struct node *node_statement_list(struct node *list, struct node *item);
struct node *node_binary_operation(int operation, struct node *left_operand,
                                   struct node *right_operand);
struct node *node_expression_statement(struct node *expression);
struct node *node_statement_list(struct node *init, struct node *statement);

/*added this one*/
struct node *node_string(char *text, int len);
struct node *node_unary_operation(int operation, struct node *operand);
struct node *node_function_call(struct node *expression, struct node *args);
struct node *node_comma_list(struct node *first, struct node *second);
struct node *node_cast(struct node *type, struct node *cast);
struct node *node_type(int sign, int type);
struct node *node_ternary_operation(struct node *log_expr, struct node *expr, struct node * cond_expr);
struct node *node_decl(struct node *type, struct node *init_decl_list);
struct node *node_pointers(struct node *pointers);
struct node *node_pointer_declarator(struct node *pointer_list, struct node *dir_dec);
struct node *node_function_declarator(struct node *dir_dec, struct node *params);
struct node *node_array_declarator(struct node *dir_dec, struct node *constant);
struct node *node_parameter_decl(struct node *type, struct node *declarator);
struct node *node_type_name(struct node *type, struct node *declarator);
struct node *node_labeled_statement(struct node *id, struct node *statement);
struct node *node_compound(struct node *statement_list);
struct node *node_conditional(struct node *expr, struct node *st1, struct node *st2);
struct node *node_operator(int op);

struct result *node_get_result(struct node *expression);

void node_print_statement_list(FILE *output, struct node *statement_list);

#endif
