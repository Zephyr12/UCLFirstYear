import Parse

number = oneOf ['0'..'9']
alpha = oneOf (['a'..'z'] ++ ['A'..'Z'])
anyChar = oneOf ['\0'..'\127']

bool = (sequential "true" <|> sequential "false") <#> "Bool"
int = oneOrMore number <#> "Int"
real = oneOrMore number <+> Literal '.' <+> oneOrMore number <#> "Real"
char = Ignore (Literal '\'') <+> (optional (Literal '\\') <+> anyChar) <+> Ignore (Literal '\'') <#> "Char"
string = Ignore (Literal '"') <+> zeroOrMore strChr <+> Ignore (Literal '"') <#> "String"
    where strChr = oneOf (['\32'..'\33'] ++ ['\35'..'\91'] ++ ['\93'..'\127']) <|> sequential "\\\\" <|> sequential "\\\""

delimitedList del item = item <?> zeroOrMore (Ignore del <?> item <+> optional whitespace) <|> Empty

list = Ignore (Literal '[') <?> delimitedList (Ignore (Literal ',')) atom <?> Ignore (Literal ']') <#> "List"
tuple = Ignore (Literal '(') <?> delimitedList (Ignore (Literal ',')) atom <?> Ignore (Literal ')') <#> "Tuple"

literal = bool <|> int <|> char <|> string <|> real <|>  tuple <|> list

method = Literal 'm'
new = Literal 'n'
ident = nonDigit <+> zeroOrMore(nonDigit <|> number) <#> "Ident"
    where nonDigit = oneOf (['a'..'z']++['A'..'Z']++['_'])
accessor = ident <+> oneOrMore(Ignore (Literal '.') <+> ident) <#> "Accessor"
call =  ident <?> tuple
    <|> accessor <?> tuple 
    <|> Ignore (Literal '(') <?> expression <?> Ignore (Literal ')') <?> tuple <#> "Call"

atom = ident <|> literal <|> accessor <|> call
factor = ((atom <|> Ignore (Literal '(') <?> expression <?> Ignore (Literal ')')) 
    <?> zeroOrMore (Ignore (Literal '^') <?> expression <#> "Exponent")) <#> "Factor"
term = factor <?> zeroOrMore (oneOf ['*','/'] <?> factor <#> "Succ-Factors") <#> "Term"
expression = term <?> zeroOrMore (oneOf ['+', '-'] <?> term <#> "Succ-Term") <#> "Expression"
