module Parse where

import Data.List

data ParseResult a = Success [ParseResult a] | Parsing String (Maybe a) [ParseResult a] [a] | Fail 
data Parser a = Or (Parser a) (Parser a) | Then (Parser a) (Parser a) | Literal a | Ignore (Parser a) | Named String (Parser a) | Empty

(<|>) :: (Parser a) -> (Parser a) -> (Parser a)
a <|> b = Or a b
infixl 4 <|>

(<+>) :: (Parser a) -> (Parser a) -> (Parser a)
a <+> b = Then a b
infixl 6 <+>

(<>) :: (Parser Char) -> (Parser Char) -> (Parser Char)
a <> b = a <+> Ignore whitespace <+> b
infixl 6 <>

(<#>) :: (Parser a) -> [Char] -> (Parser a)
parser <#> name = Named name parser
infixl 5 <#>

parse :: (Eq a) => (Parser a) -> [a] -> (ParseResult a)
parse (Or a b) input = case ((parse a input),(parse b input)) of
    (a@(Parsing _ _ _ _), _) -> a
    (Fail,b@(Parsing _ _ _ _)) -> b
    (Fail,Fail) -> Fail
  

parse (Then fst snd) input = case (parse fst input) of
    {-NotGroup then NotGroup
    Group then NotGroup
    NotGroup then Group
    Group then Group
    Fail-}
    a@(Parsing "Group" valueA resultA remainingInput) -> (case (parse snd remainingInput) of
        b@(Parsing "Group" valueB resultB finalInput) -> (Parsing "Group" Nothing (resultA ++ resultB) finalInput)
        b@(Parsing nameB valueB resultB finalInput) -> (Parsing "Group" Nothing (resultA ++ [b]) finalInput)
        Fail -> Fail -- (Parsing "Group" Nothing ((Parsing nameA valueA resultA remainingInput):resultA) [])
        )

    a@(Parsing nameA valueA resultA remainingInput) -> (case (parse snd remainingInput) of
        b@(Parsing "Group" valueB resultB finalInput) -> (Parsing "Group" Nothing (a:resultB) finalInput)
        b@(Parsing nameB valueB resultB finalInput) -> (Parsing "Group" Nothing ([a,b]) finalInput)
        Fail -> Fail -- (Parsing "Group" Nothing ((Parsing nameA valueA resultA remainingInput):resultA) [])
        )


    {-a@(Parsing nameA valueA resultA remainingInput) -> (case (parse b remainingInput) of
        b@(Parsing nameB valueB [] finalInput) -> (Parsing nameA Nothing (resultA ++ [b]) finalInput)
        b@(Parsing nameB valueB resultB finalInput) -> (Parsing nameA Nothing (resultA ++ resultB) finalInput)
        Fail -> Fail -- (Parsing "Group" Nothing ((Parsing nameA valueA resultA remainingInput):resultA) [])
        )
    -}
    Fail -> Fail

parse (Literal needle) (x:xs)
    | needle == x = Parsing "Literal" (Just x) [] xs
    | otherwise = Fail
parse (Literal _) [] = Fail 

parse (Named name parser) input = case (parse parser input) of
    parse@(Parsing "Group" value result remainingInput) -> Parsing name value result remainingInput
    parse@(Parsing _ value result remainingInput) -> Parsing name value [parse] remainingInput
    Fail -> Fail

parse (Empty) input = Parsing "Empty" Nothing [] input

parse (Ignore a) input = case parse a input of
    (Parsing _ _ _ remainingInput) -> Parsing "Empty" Nothing [] remainingInput
    Fail -> Fail

parseStrict parser input = case (parse parser input) of
    a@(Parsing nameA valueA resultA []) -> Success [cleanup a]
    otherwise -> Fail
    where cleanup (Parsing name value result input) = (Parsing name value [cleanup r | r@(Parsing name _ _ _) <- result, name /= "Empty"] input)


instance (Show a) => Show (Parser a) where
    show (Or a b) = "(" ++ show a ++ " | " ++ show b ++ ")"
    show (Then a b) = show a ++ " " ++ show b
    show (Literal a) = show a
    show (Named a parser) =  a ++ ": (" ++ show parser ++ ")"
    show (Ignore _) = ""

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
sequential [] = error "Empty sequentialuence does not do what you think it does"
sequential (x:[]) = Literal x
sequential (x:xs) = Literal x <+> sequential xs

oneOrMore parser = parser <+> (oneOrMore parser) <|> parser
zeroOrMore parser = oneOrMore parser <|> Empty
whitespace = oneOrMore (oneOf ['\n', '\t', ' '])
