#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

typedef struct parser{
    enum {
        LITERAL,
        IGNORE,
        THEN,
        OR,
        NAMED,
        EMPTY
    } type;
    union {
        struct {
            char lit;
        } literal;
        struct {
            struct parser* p;
        } ignore;
        struct {
            struct parser** parsers;
            int num_parsers;
        } then;
        struct {
            struct parser** parsers;
            int num_parsers;
        } or;
        struct {
            char* name;
            struct parser* parser;
        } named;
        struct {} empty;
    } parser;
}parser;

typedef struct ast_node{
    char* type;
    char value;
    struct ast_node** children;
    int num_children;
    char* remaining_input;
} ast_node;

ast_node* new_ast_node(
        char* type,
        char value,
        ast_node** children,
        int num_children,
        char* remaining_input){
    ast_node *ptr = malloc(sizeof(ast_node));
    ptr->type = type;
    ptr->value = value;
    ptr->children = children;
    ptr->num_children = num_children;
    ptr->remaining_input = remaining_input;
    return ptr;
}

void print_ast_node(ast_node* node){
    if (node->value){
        printf("(%c)", node->value);
    }else{
        printf("(%s", node->type);
        for (int i = 0; i < node->num_children; i++){
            printf(" ");
            print_ast_node(node->children[i]);
        }
        printf(")");
    }
}

void error(char** expected, int num_expected, char* found){
    printf("Parse Error: expected one of ");
    for (int i = 0; i < num_expected - 1; i++){
        printf("%s|", expected[i]);
    }
    printf("%s found %s\n", expected[num_expected-1], found);
    exit(1);
}

parser* empty(){
    parser *p = malloc(sizeof(parser));
    p->type = EMPTY;
    return p;
}

parser* literal(char a){
    parser *p = malloc(sizeof(parser));
    p->type = LITERAL;
    p->parser.literal.lit = a;
    return p;
}

parser* ignore(parser* ignored){
    parser *p = malloc(sizeof(parser));
    p->type = IGNORE;
    p->parser.ignore.p = ignored;
    return p;
}

parser* named(char* name, parser* named_parser){
    parser *p = malloc(sizeof(parser));
    p->type = NAMED;
    p->parser.named.name = name;
    p->parser.named.parser = named_parser;
    return p;
}

parser* or(parser** parsers, int num_parsers){
    parser *p = malloc(sizeof(parser));
    p->type = OR;
    p->parser.or.parsers = parsers;
    p->parser.or.num_parsers = num_parsers;
    return p;
}

parser* then(parser** parsers, int num_parsers){
    parser *p = malloc(sizeof(parser));
    p->type = THEN;
    p->parser.then.parsers = parsers;
    p->parser.then.num_parsers = num_parsers;
    return p;
}

ast_node* parse(parser* p, char* input){
    if(p->type == LITERAL){
        if (*input == p->parser.literal.lit){
            return new_ast_node("Literal", *input, NULL, 0, input+1);
        }else{
            return NULL;
        }
    }
    if(p->type == IGNORE){
        ast_node* res = parse(p, input);
        if (res){
            return new_ast_node("Empty", '\0', NULL, 0, res->remaining_input);
        }else{
            return NULL;
        }
    }

    if(p->type == THEN){
        ast_node** results = malloc(sizeof(ast_node*) * p->parser.then.num_parsers); 
        char* remaining_input = input;
        int current_extra_nodes = 0;
        int num_nodes = 0;
        for (int i = 0; i < p->parser.then.num_parsers; i++){
            parser* sub_parser = p->parser.then.parsers[i];
            ast_node* node = parse(sub_parser, remaining_input);
            if(node){
                if(strcmp(node->type, "Group") != 0){
                    results[i+current_extra_nodes] = node;
                    remaining_input = node->remaining_input;
                    num_nodes++;
                }else{
                    current_extra_nodes += node->num_children;
                    results = realloc(results, sizeof(ast_node*) * (p->parser.then.num_parsers+current_extra_nodes));
                    for (int y = 0; y < node->num_children; y++){
                        if(node->children[y]){
                            results[i+y] = node->children[y];
                            num_nodes++;
                        }else{
                            return NULL;
                        }
                    }
                }
            } else{
                return NULL;
            }
        }
        return new_ast_node("Group", '\0', results, num_nodes, remaining_input);
    }

    if(p->type == OR){

        for (int i = 0; i < p->parser.or.num_parsers; i++){
            parser* sub_parser = p->parser.or.parsers[i];
            ast_node* maybe = parse(sub_parser, input);
            if(maybe){
                return maybe;
            }
        }
        return NULL;
    }

    if(p->type == NAMED){
        ast_node* result = parse(p->parser.named.parser, input);
        if(!result){
            return NULL;
        }
        if(!strcmp(result->type, "Group")){
            result->type = p->parser.named.name;
        }else {
            return new_ast_node(p->parser.named.name, '\0', &result, 1, result->remaining_input);
        }
        return result;
    }

    if(p->type == EMPTY){
        return new_ast_node("Empty", '\0', NULL, 0, input);
    }
    return NULL;
}

parser* one_of(char* str){
    parser** options = malloc(sizeof(parser*) * strlen(str));
    for (int i = 0; i < (int)strlen(str); i++){
        options[i] = literal(str[i]);
    }
    return or(options, strlen(str));
}

parser* one_or_more(parser* p){
    parser** then_children = malloc(sizeof(parser*) * 2);
    then_children[0] = p;
    then_children[1] = NULL;
    parser* rest = then(then_children, 2);

    parser** or_children = malloc(sizeof(parser*) * 2);
    or_children[0] = rest;
    or_children[1] = p;
    parser* choice = or(or_children, 2);

    choice->parser.or.parsers[0]->parser.then.parsers[1] = choice;
    return choice;
}

parser* zero_or_more(parser* p){
    parser** or_children = malloc(sizeof(parser*) * 2);
    or_children[0] = p;
    or_children[1] = empty();
    return or(or_children, 2);
}

int main(void){
    parser* test = zero_or_more(one_of("0123456789"));
    return 0;
}
