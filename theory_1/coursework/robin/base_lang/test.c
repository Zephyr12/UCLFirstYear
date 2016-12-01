struct Sw_Obj_Book {
    Sw_Obj_String* name;
    Sw_Obj_String* author;
}

void init_Sw_Obj_Book(Sw_Obj_Book* this, Sw_Obj_String name, Sw_Obj_String author){
    this->name = name;
    this->author = author;
}

Sw_Obj_Book* new_Sw_Obj_Book(Sw_Obj_String* name, Sw_Obj_String* author){
    Sw_Obj_Book* obj = malloc(sizeof(Sw_Obj_Book));
    init_Sw_Obj_Book(obj, name, author);
    return obj;
}

struct Sw_Obj_Main {
    Sw_Obj_String* name;
    Sw_Obj_Book* fav_book;
    Sw_Obj_Int* age;
}


void init_Sw_Obj_Main(Sw_Obj_List* args){
    Sw_Obj_Book* book = new_Sw_Obj_Book(new_Sw_Obj_String("Strlit"), new_Sw_Obj_String("Strlit2"));
    show_Sw_Obj_String(book->name);
}

Sw_Obj_Main* new_Sw_Obj_Main(Sw_Obj_List* args){

}


int main(int argc, char** argv){
    new_Sw_Obj_Main(new_Sw_Obj_List(argc, argv));
    return 0;
}
