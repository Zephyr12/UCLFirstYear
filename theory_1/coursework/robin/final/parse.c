#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

const int Fsize=50;
int no_edges;
int no_nodes;
int i;
const int cases=15;


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
            struct parser* parser;
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
    if(node){
        if (node->value){
            printf("(%c)", node->value);
        }else{
            printf("(%s", node->type);
            int i; 
            for (i = 0; i < node->num_children; i++){
                printf(" ");
                print_ast_node(node->children[i]);
            }
            printf(")");
        }
    }else{
        printf("(Fail)");
    }
}

void error(char** expected, int num_expected, char* found){
    printf("Parse Error: expected one of ");
    int i;
    for (i = 0; i < num_expected - 1; i++){
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
    p->parser.ignore.parser = ignored;
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
        ast_node* res = parse(p->parser.ignore.parser, input);
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
        int i;
        for (i = 0; i < p->parser.then.num_parsers; i++){
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
                    remaining_input = node->remaining_input;
                    int y;
                    for (y = 0; y < node->num_children; y++){
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
        int i;
        for (i = 0; i < p->parser.or.num_parsers; i++){
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
            ast_node** named_children = malloc(sizeof(ast_node*));
            named_children[0] = result;
            return new_ast_node(p->parser.named.name, '\0', named_children, 1, result->remaining_input);
        }
        return result;
    }

    if(p->type == EMPTY){
        return new_ast_node("Empty", '\0', NULL, 0, input);
    }
    return NULL;
}

void remove_empties(ast_node* node){
    int i;
    int num_empties = 0;
    for (i = 0; i < node->num_children; i++){
        if (!strcmp(node->children[i]->type, "Empty")){
            num_empties ++;
        }
    }
    ast_node** new_children = malloc(sizeof(ast_node*) * (node->num_children - num_empties));
    num_empties = 0;
    for (i = 0; i < node->num_children; i++){
        if (!strcmp(node->children[i]->type, "Empty")){
            num_empties++;
        }else{
            remove_empties(node->children[i]);
            new_children[i - num_empties] = node->children[i];
        }
    }
    node->children = new_children;
    node->num_children -= num_empties;
}

ast_node* parse_strict(parser* p, char* input){
    ast_node* result = parse(p, input);
    if(!result || strlen(result->remaining_input)){
        return NULL;
    }else{
        remove_empties(result);
        return new_ast_node("Success", '\0', &result, 1, "");
    }
}

parser* one_of(char* str){
    parser** options = malloc(sizeof(parser*) * strlen(str));
    int i;
    for (i = 0; i < (int)strlen(str); i++){
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
    or_children[0] = one_or_more(p);
    or_children[1] = empty();
    return or(or_children, 2);
}
parser* optional(parser* p){
    parser** or_children = malloc(sizeof(parser*) * 2);
    or_children[0] = p;
    or_children[1] = empty();
    return or(or_children, 2);
}

void test_parse(parser* p, char* input){
    print_ast_node(parse_strict(p, input));
    printf("\n");
}

bool edge_eq(int e1x, int e1y, int e2x, int e2y){
    return e1x == e2x && e1y == e2y;
}

bool eval(ast_node* node, int edges[][2], int num_edges, int size, int vars[3]){
    if(!strcmp(node->type, "Atomic")){
        int i;
        for (i = 0; i < num_edges; i ++){
            if (edge_eq(
                    edges[i][0], edges[i][1],
                    vars[node->children[0]->value - 'x'], vars[node->children[1]->value - 'x']
                    )){
                return 1;
            }

        }
        return 0;
    }
    if(!strcmp(node->type, "Negated")){
        return !eval(node->children[0], edges, num_edges, size, vars);
    }
    if(!strcmp(node->type, "Binary Connective")){
        bool a = eval(node->children[0], edges, num_edges, size, vars);
        bool b = eval(node->children[2], edges, num_edges, size, vars);
        switch(node->children[1]->value){
            case 'v':
                return a || b;
                break;
            case '^':
                return a && b;
                break;
            case '>':
                return !a || b;
                break;
        }
        return 0;
    }
    if(!strcmp(node->type, "Existential")){
        int i;
        int new_vars[3];
        new_vars[0] = vars[0];
        new_vars[1] = vars[1];
        new_vars[2] = vars[2];
        for (i = 0; i < size; i++){
            new_vars[node->children[0]->value - 'x'] = i;
            if(eval(node->children[1], edges, num_edges, size, new_vars)){
                return 1;
            }
        }
        return 0;
    }
    if(!strcmp(node->type, "Universal")){
        int i;
        int new_vars[3];
        new_vars[0] = vars[0];
        new_vars[1] = vars[1];
        new_vars[2] = vars[2];
        for (i = 0; i < size; i++){
            new_vars[node->children[0]->value - 'x'] = i;
            if(!eval(node->children[1], edges, num_edges, size, new_vars)){
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int sln_eval(parser* p, char* input, int edges[][2], int size, int vars[3]){
    return eval(parse_strict(p, input)->children[0], edges, no_edges, size, vars);
}

int sln_parse(parser* p, char* input){
    ast_node* result = parse_strict(p, input);
    if(result){
        result = result->children[0];
        if (!strcmp(result->type, "Atomic")){
            return 1;
        }
        if (!strcmp(result->type, "Negated")){
            return 2;
        }
        if (!strcmp(result->type, "Binary Connective")){
            return 3;
        }
        if (!strcmp(result->type, "Existential")){
            return 4;
        }
        if (!strcmp(result->type, "Universal")){
            return 5;
        }
        return 6;
    }else{
        return 0;
    }
}

int main(void){
    parser* formula = NULL;
    parser* var = one_of("xyz");
    parser* bin_con = one_of("v^>");

    parser** atomic_children = malloc(5*(sizeof(parser*)));
    atomic_children[0] = ignore(literal('X'));
    atomic_children[1] = ignore(literal('['));
    atomic_children[2] = var;
    atomic_children[3] = var;
    atomic_children[4] = ignore(literal(']'));
    parser* atomic = named("Atomic", then(atomic_children, 5));

    parser** negated_children = malloc(2*(sizeof(parser*)));
    negated_children[0] = ignore(literal('-'));
    parser* negated = named("Negated", then(negated_children, 2));
    
    parser** binary_connective_children = malloc(5*(sizeof(parser)));
    binary_connective_children[0] = ignore(literal('('));
    binary_connective_children[2] = bin_con;
    binary_connective_children[4] = ignore(literal(')'));
    parser* binary_connective = named("Binary Connective", then(binary_connective_children, 5));
    
    parser** existential_children = malloc(3*(sizeof(parser)));
    existential_children[0] = ignore(literal('E'));
    existential_children[1] = var;
    parser* existential = named("Existential", then(existential_children, 3));

    parser** universal_children = malloc(3*(sizeof(parser)));
    universal_children[0] = ignore(literal('A'));
    universal_children[1] = var;
    parser* universal = named("Universal", then(universal_children, 3));

    parser** formula_children = malloc(5*(sizeof(parser*)));
    formula_children[0] = atomic;
    formula_children[1] = negated;
    formula_children[2] = binary_connective;
    formula_children[3] = existential;
    formula_children[4] = universal;

    formula = or(formula_children, 5);

    existential_children[2] = formula;
    universal_children[2] = formula;
    negated_children[1] = formula;
    binary_connective_children[1] = formula;
    binary_connective_children[3] = formula;

    char *name=malloc(Fsize); /*create space for the formula*/
    FILE *fp, *fpout;
     
    /* reads from input.txt, writes to output.txt*/
    if ((fp=fopen("input.txt","r"))==NULL){
        printf("Error opening file");
        exit(1);
    }
    if ((fpout=fopen("output.txt","w"))==NULL){
        printf("Error opening file");
        exit(1);
    }

    int j;
    for(j=0;j<cases;j++){
        fscanf(fp, "%s %d %d",name,&no_nodes,&no_edges);/*read number of nodes, number of edges*/
        int edges[no_edges][2];  /*Store edges in 2D array*/

        for(i=0;i<no_edges;i++){
            fscanf(fp, "%d%d", &edges[i][0], &edges[i][1]);
        }/*read all the edges*/

        /*Assign variables x, y, z to nodes */
        int W[3];
        /*Store variable values in array
        value of x in V[0]
        value of y in V[1]
        value of z in V[2] */
        for(i=0;i<3;i++){
            fscanf(fp, "%d", &W[i]);
        }
        int p = sln_parse(formula, name);
        switch(p){
            case 0: 
                fprintf(fpout,"%s is not a formula.  ", name);break;
            case 1: 
                fprintf(fpout,"%s is an atomic formula.  ",name);break;
            case 2:
                fprintf(fpout,"%s is a negated formula.  ",name);break;
            case 3:
                fprintf(fpout,"%s is a binary connective formula.  ", name);break;
            case 4:
                fprintf(fpout,"%s is an existential formula.  ",name);break;
            case 5:
                fprintf(fpout,"%s is a universal formula.  ",name);break;
            default:
                fprintf(fpout,"%s is not a formula.  ",name);break;
        }

        /*Now check if formula is true in the graph with given variable assignment. */
        if (sln_parse(formula, name) != 0){
            if (sln_eval(formula, name, edges, no_nodes,  W)==1){
                fprintf(fpout,"The formula %s is true in G under W\n", name);
            }
            else{
                fprintf(fpout,"The formula %s is false in G under W\n", name);
            }
        }
    }



    fclose(fp);
    fclose(fpout);
    free(name);
        
    return 0;
}
