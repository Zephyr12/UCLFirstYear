module Parse where

import Data.List

data ParseResult a = Success [ParseResult a] | Parsing String (Maybe a) [ParseResult a] [a] | Fail 
data Parser a = Or (Parser a) (Parser a) | Then (Parser a) (Parser a) | Literal a | Named String (Parser a) | Empty

(<|>) :: (Parser a) -> (Parser a) -> (Parser a)
a <|> b = Or a b
infixl 5 <|>

(<+>) :: (Parser a) -> (Parser a) -> (Parser a)
a <+> b = Then a b
infixl 6 <+>

(<#>) :: (Parser a) -> [Char] -> (Parser a)
parser <#> name = Named name parser
infixl 0 <#>

parse :: (Eq a) => (Parser a) -> [a] -> (ParseResult a)
parse (Or a b) input = case ((parse a input),(parse b input)) of
    (a@(Parsing _ _ _ _), _) -> a
    (Fail,b@(Parsing _ _ _ _)) -> b
    (Fail,Fail) -> Fail
  

parse (Then a b) input = case (parse a input) of
    a@(Parsing nameA valueA resultA remainingInput) -> (case (parse b remainingInput) of
        --b@(Parsing nameB valueB resultB finalInput) -> (Parsing "Group" Nothing ((Parsing nameA valueA [] finalInput):resultB) finalInput)
        b@(Parsing nameB valueB resultB finalInput) -> 
            if (length resultA == 0 || valueA == Nothing) then 
                (Parsing "Group" Nothing ([a,b]) finalInput)
             else 
                (Parsing "Group" Nothing (resultA ++ [(Parsing nameB valueB resultB finalInput)]) finalInput)
        Fail -> Fail -- (Parsing "Group" Nothing ((Parsing nameA valueA resultA remainingInput):resultA) [])
        )
    Fail -> Fail

parse (Literal needle) (x:xs)
    | needle == x = Parsing "Literal" (Just x) [] xs
    | otherwise = Fail
parse (Literal _) [] = Fail 

parse (Named name parser) input = case (parse parser input) of
    parse@(Parsing _ (Just _) result remainingInput) -> Parsing name Nothing [parse] remainingInput
    parse@(Parsing _ Nothing result remainingInput) -> Parsing name Nothing result remainingInput
    Fail -> Fail

parse (Empty) input = Parsing "Empty" Nothing [] input

parseStrict parser input = case (parse parser input) of
    a@(Parsing nameA valueA resultA []) -> Success resultA
    otherwise -> Fail


instance (Show a) => Show (Parser a) where
    show (Or a b) = "(" ++ show a ++ " | " ++ show b ++ ")"
    show (Then a b) = show a ++ " " ++ show b
    show (Literal a) = show a
    show (Named a parser) =  a ++ ": (" ++ show parser ++ ")"

instance (Show a) => Show (ParseResult a) where
    show Fail = "Fail"
    show (Success tree) = "Success [\n" ++ unlines (map show tree) ++ "\n]"
    show (Parsing name (Just value) tree finalInput) = "Node " ++ name ++ ": " ++ show value ++ " [\n" ++ unlines (map show tree) ++ "\n]"
    show (Parsing name Nothing tree finalInput) = "Node " ++ name ++ ": [\n" ++ unlines (map show tree) ++ "\n]"

oneOf :: [a] -> Parser a
oneOf [] = error "Empty/Optional/Parser is not allowed"
oneOf (x:[]) = Literal x
oneOf (x:xs) = (Literal x) <|> (oneOf xs)

sequential :: [a] -> Parser a
sequential x = seq (reverse x) where
    seq [] = error "Empty sequence does not do what you think it does"
    seq (x:[]) = Literal x
    seq (x:xs) = seq xs <+> Literal x

oneOrMore parser = (parser <+> (oneOrMore parser)) <|> parser
zeroOrMore parser = oneOrMore parser <|> Empty
