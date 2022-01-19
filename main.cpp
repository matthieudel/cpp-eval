#include "graph.cpp"



int main(){

    std::vector<std::string> Villes {"Paris", "Lyon", "Marseille", "Londres", "Bordeaux", "New-York", "Toulouse"};      //On initialise un graph list
    std::unordered_map<std::string, std::vector<Arete>> Chemins { {"Paris", {Arete("Paris", 775, "Marseille"), Arete("Paris", 470, "Londres"), Arete("Paris", 584, "Bordeaux") }}, 
                                                                 {"Lyon", {Arete("Lyon", 466, "Paris"), Arete("Lyon", 317, "Marseille"), Arete("Lyon", 553, "Bordeaux")}}, 
                                                                 {"Marseille", {Arete("Marseille", 775, "Paris"), Arete("Marseille", 404, "Toulouse")}},
                                                                 {"Bordeaux", {Arete("Bordeaux", 645, "Marseille"), Arete("Bordeaux", 553, "Lyon"), Arete("Bordeaux", 245, "Toulouse")} } ,
                                                                 {"Londres", {Arete("Londres", 470, "Paris")}},
                                                                 {"Toulouse", {Arete("Toulouse", 679, "Paris"), Arete("Toulouse", 541, "Lyon"), Arete("Toulouse", 404, "Marseille")}} };

    Graph_list test(Villes, Chemins);
    test.print();                       //test du print list
    cout << '\n';

    std::vector<std::string> sommets {"Paris", "Lyon", "Marseille"};            //On initialise un graph mat
    std::vector<float> soustab {numeric_limits<float>::infinity(),numeric_limits<float>::infinity(),numeric_limits<float>::infinity()};
    std::vector<std::vector<float>> mat {soustab, soustab, soustab};
    mat[0][1] = 500;
    mat[0][2] = 800;
    mat[1][0] = 500;
    mat[2][0] = 800;
    mat[2][1] = 400;
    Graph_mat g1(sommets, mat);

    g1.print();                             //test du print mat
    cout << '\n';
    Graph_mat test2 = test.list_to_mat();   //test de la fonction de conversion list -> mat
    test2.print();
    cout << '\n';


    Graph_list g;
    g = file_to_graph_list();       //test de la question 2 : file -> list
    g.print();
    cout << '\n';

    Graph_mat gr;
    gr = file_to_graph_mat();       //test de la question 2 : -> file -> mat
    gr.print();
    cout << '\n';


    test.Deep_first_search_rec_graph_list();    //test de la question 3 : parcours en profondeur récurssif
    cout << '\n';


    test.print();                   //test de la question 4
    cout << '\n' ;
    cout << "résultats du parcours en profondeur à partir d'un graph list puis d'un graph mat : " << '\n';
    cout << '\n' ;
    test.Deep_first_search_graph_list();
    cout << '\n' ;
    test2.Deep_firts_search_graph_mat();
    cout << '\n' ;


    cout << "résultats du parcours en largeur à partir de Paris pour un graph list puis d'un graph mat : " << '\n';         //test de la question 5
    cout << '\n' ;
    test.Breadth_first_search_graph_list(0, "Paris");   //(donc la ville de départ n'est pas print mais on la connait)
    cout << '\n' ;
    test2.Breadth_first_search_graph_mat(0, "Paris");
    cout << '\n' ;
    cout << "résultats du parcours avec un nombre de niveaux limité, ici 2 : " << '\n';
    cout << '\n' ;
    test.Breadth_first_search_graph_list(2, "Paris");
    cout << '\n' ;


    test.Dijkstra("Londres", "Toulouse");       //test de la question 6
    cout << '\n';
    test.Dijkstra("Paris", "New-York");
    cout << '\n';


    test2.Floyd_Warshall(); //test de la question 7
    cout << '\n';


    return 0;
}       //le main marche pas dans ce fichier mais ca marche si je le colle dans graph.cpp pourquoi ???
