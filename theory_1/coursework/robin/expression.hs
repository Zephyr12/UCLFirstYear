import Parse

digit = oneOf ['0'..'9'] <#> "Digit"
number = oneOf ['1'..'9'] <+> zeroOrMore digit <#> "Number"

factor = number <|> Ignore (Literal '(') <+> expression <+> Ignore (Literal ')') <#> "Expression"

term = factor <> Ignore (Literal '*') <> term <#> "Multiply" <|> factor <> Ignore (Literal '/') <> term <#> "Divide" <|> factor <#> "Factor" 

expression = term <> Ignore (Literal '+') <> expression <#> "Add" <|> term <> Ignore (Literal '-') <> expression <#> "Subtract" <|> term <#> "Term" 
