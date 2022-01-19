#include<iostream>
#include<unordered_map>
#include<vector>
#include<fstream>
#include<cmath>
#include<stack>
#include<queue>

class Arete{

    public :

    Arete(std::string entrant, float poids, std::string sortant);     // les aretes sont prises sous la forme (sommet entrant, poids de l'arete, sommet sortant)
    std::string getentrant() const;
    std::string getsortant() const;
    float getpoids() const;
    void print();

    private :

    std::string m_entrant;
    float m_poids;
    std::string m_sortant;

};

class Graph_mat;        //prédéfinition pour pouvoir faire une fonction qui renvoie des Graph_mat dans la classe Graph_list

class Graph_list{

    public :

    Graph_list();    
    Graph_list(std::vector<std::string> nomsommets, std::unordered_map<std::string, std::vector<Arete>> listadj);
    Graph_mat list_to_mat(); 
    Arete acces_arete(std::string s1, std::string s2);
    void print();
    void Deep_first_search_rec_graph_list();
    void Deep_first_search_graph_list();
    void Breadth_first_search_graph_list(int niveau_max, std::string depart);
    void Dijkstra(std::string s1, std::string s2);

    private :

    std::unordered_map<std::string, std::vector<Arete>> m_listadj;
    std::vector<std::string> m_nomsommets;
};

class Graph_mat{

    public :

    Graph_mat();
    Graph_mat(std::vector<std::string> nomsommets, std::vector<std::vector<float>> matadj);
    Graph_list mat_to_list();
    Arete acces_arete(std::string s1, std::string s2);
    void print();
    void Deep_firts_search_rec_graph_mat();
    void Deep_firts_search_graph_mat();
    void Breadth_first_search_graph_mat(int niveau_max, std::string depart);
    void Floyd_Warshall();

    private :

    std::vector<std::vector<float>> m_matadj;
    std::vector<std::string> m_nomsommets;

};