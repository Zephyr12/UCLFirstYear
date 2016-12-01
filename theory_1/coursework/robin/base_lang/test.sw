Book
----
name: String
author: String
----
init (name: String, author: String) -> void
/
    this.name = name
    this.author = author
\
----

Main
----
name: String
fav_book: Book
age: Int
----
init (args: List) -> void
/
    this.name <- "My first program"
    this.age <- 0
    this.fav_book <- Book.new("Lord of the Rings", "JRR Tolken")
    book: Book <- Book.new("Strlit", "Strlit")
    show(book.name)
    show(this.fav_book.name)
\
----
