import Parse
import Data.Char

digit = oneOf ['0'..'9']
number = digit <+> zeroOrMore digit <+> optional (Literal '.' <+> oneOrMore digit) <#> "Number"

factor = (number <|> Ignore (Literal '(') <+> expression <+> Ignore (Literal ')') <#> "Sub-Expression") <+> (optional (Ignore (sequential "**") <+> Ignore (Literal '(') <+> statement <+> Ignore (Literal ')') <#> "Sub-Expression")) <#> "Factor"

term = factor <+> zeroOrMore (Ignore (optional whitespace) <+> oneOf (['*', '/']) <+> Ignore (optional whitespace) <+> factor <#> "SuccFactor") <#> "Term"

expression = term <+> zeroOrMore (Ignore (optional whitespace) <+> oneOf (['+', '-']) <+> Ignore (optional whitespace) <+> term <#> "SuccTerm") <#> "Expression"

statement = (Ignore (optional whitespace)) <+> expression <+> (Ignore (optional whitespace)) <#> "Statement"

eval :: (ParseResult Char) -> Double
eval (Success (expr:[])) = eval expr
eval (Fail) =  error "Parse Fail"
eval (Parsing "Statement" _ (expression:[]) _) = eval expression
eval (Parsing "Expression" _ (term:succTerms) _) = eval term + sum (map eval succTerms)
eval (Parsing "SuccTerm" _ (operation:term:[]) _) = case operation of
    Parsing "Literal" (Just '+') _ _  -> (eval term)
    Parsing "Literal" (Just '-') _ _ -> -(eval term)
eval (Parsing "Term" _ (factor:succFactors) _) = eval factor * foldl (*) 1 (map eval succFactors)
eval (Parsing "SuccFactor" _ (operation:factor:[]) _) = case operation of
    Parsing "Literal" (Just '*') _ _ -> (eval factor)
    Parsing "Literal" (Just '/') _ _ -> 1 / (eval factor)
eval (Parsing "Factor" _ (child:[]) _) = eval child
eval (Parsing "Factor" _ (factor:exponent:[]) _) = (eval factor) ** (eval exponent)
eval (Parsing "Sub-Expression" _ (child:[]) _) = eval child
eval (Parsing "Number" _ children _) = read (map extractVal children) :: Double
    where extractVal (Parsing "Literal" (Just x) [] _) = x

main = getLine >>= (\x -> putStrLn (show (eval (parseStrict statement x)))) >> main
