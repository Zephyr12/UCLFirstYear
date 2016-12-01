import System.IO
import System.Environment
import Parse

digit = oneOf ['0'..'9']
char = oneOf (['a'..'z'] ++ ['A'..'Z'])
ident = oneOrMore char <#> "Ident"

number = optional (Literal '-') <+> oneOrMore digit <+> optional (Literal '.' <+> oneOrMore digit) <#> "Number"
factor = ((ident <|> number <|> Ignore (Literal '(') <?> expression <?> Ignore (Literal ')')) <?> zeroOrMore (Ignore (Literal '^') <?> expression <#> "Exponent")) <#> "Factor"
term = factor <?> zeroOrMore (oneOf ['*','/'] <?> factor <#> "Succ-Factors") <#> "Term"
expression = term <?> zeroOrMore (oneOf ['+', '-'] <?> term <#> "Succ-Term") <#> "Expression"

declaration = (ident <?> Ignore (sequential "<-") <?> expression <#> "Declaration")
assignment = (ident <?> Ignore (sequential "<<") <?> expression <#> "Assignment")
output = (Ignore (sequential "->") <?> expression <#> "Output")
for = (Ignore(sequential "for ") <?> ident <?> Ignore(sequential "<-") <?> expression <?> Ignore (Literal ',') <?> expression <?> Ignore(sequential "...") <?> expression <?> Ignore (Literal '(') <\> program <\> Ignore (Literal ')') 
    <|> Ignore(sequential "for ") <?> ident <?> Ignore(sequential "<-") <?> expression <?> Ignore(sequential "...") <?> expression <?> Ignore (Literal '(') <\> program <\> Ignore (Literal ')')) <#> "For"
statement = assignment <|> output <|> for <|> declaration

newline = Ignore (oneOrMore (Literal ';' <|> Literal '\n' <|> sequential "\r\n"))
program = statement <?> zeroOrMore (newline <?> statement) <?> optional newline <#> "Program"




eval :: ParseResult Char -> String
eval (Success (child:[])) = eval child
eval (Fail) = error "Parse Failed"
eval (Parsing "Number" _ digits _) = show (read (map extractValues digits) :: Double)
    where extractValues (Parsing "Literal" (Just v) _ _) = v
eval (Parsing "Ident" _ chars _) = map extractValues chars
    where extractValues (Parsing "Literal" (Just v) _ _) = v

eval (Parsing "Factor" _ (factor:exponent:[]) _) = "pow(" ++ eval factor ++ "," ++ eval exponent ++ ")"
eval (Parsing "Factor" _ (atom@(Parsing "Expression" _ _ _):[]) _) = "(" ++ eval atom ++ ")"
eval (Parsing "Factor" _ (atom:[]) _) = eval atom

eval (Parsing "Exponent" _ (expression:[]) _) = eval expression

eval (Parsing "Term" _ (factor:succFactors) _) = eval factor ++ foldl (++) "" (map eval succFactors)
eval (Parsing "Succ-Factors" _ ((Parsing "Literal" (Just op) [] _):factor:[]) _) = op : eval factor

eval (Parsing "Expression" _ (term:succTerms) _) = eval term ++ foldl (++) "" (map eval succTerms)
eval (Parsing "Succ-Term" _ ((Parsing "Literal" (Just op) [] _):term:[]) _) = op : eval term

eval (Parsing "Assignment" _ (ident : expression : []) _) = eval ident ++ " = " ++ eval expression ++ ";\n"
eval (Parsing "Declaration" _ (ident : expression : []) _) = "double " ++ eval ident ++ " = " ++ eval expression ++ ";\n"
eval (Parsing "Output" _ (expression:[]) _) = "printf(\"%f\\n\", " ++ eval expression ++ ");\n"
eval (Parsing "For" _ (iterIdent:lower:next:upper:program:[]) _) = "for(double " ++ eval iterIdent ++ " = " ++ eval lower ++ "; " ++ eval iterIdent ++ " < " ++ eval upper ++ "; " ++ eval iterIdent ++ " += (" ++ eval next ++ ") - (" ++ eval lower ++ ")){\n" ++ eval program ++ "}\n"
eval (Parsing "For" _ (iterIdent:lower:upper:program:[]) _) = "for(double " ++ eval iterIdent ++ " = " ++ eval lower ++ "; " ++ eval iterIdent ++ " <= " ++ eval upper ++ "; " ++ eval iterIdent ++ " += 1){\n" ++ eval program ++ "}\n"

eval (Parsing "Program" _ (statement:program) _) = eval statement ++ foldl (++) "" (map eval program)

main = getArgs >>= \args -> readFile (args!!0) >>= \source -> putStr ("#include <math.h> \n #include<stdio.h>\nint main (void){\n" ++ (eval (parseStrict program source)) ++ "return 0;\n}")
