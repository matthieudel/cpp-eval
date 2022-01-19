#include "graph.h"

using namespace std;


// Constructeurs

Arete::Arete(string entrant, float poids, string sortant) : m_entrant(entrant), m_poids(poids), m_sortant(sortant){}

Graph_list::Graph_list() : m_nomsommets(vector<string>{}), m_listadj(unordered_map<string, vector<Arete>>{}){}

Graph_list::Graph_list(vector<string> nomsommets, unordered_map<string, vector<Arete>> listadj) : m_nomsommets(nomsommets), m_listadj(listadj){}

Graph_mat::Graph_mat() : m_nomsommets(vector<string>{}), m_matadj(vector<vector<float>> {{}} ){}

Graph_mat::Graph_mat(vector<string> nomsommets, vector<vector<float>> matadj) : m_nomsommets(nomsommets), m_matadj(matadj){}

// Méthodes

string Arete::getentrant() const{
    return m_entrant;
}

string Arete::getsortant() const{
    return m_sortant;
}

float Arete::getpoids() const{
    return m_poids;
}

Arete Graph_list::acces_arete(string s1, string s2){      //Si je mets un const ca met une erreur, je ne comprends pas pourquoi !!
    vector<Arete> adjacents = m_listadj[s1]; 
    int i = 0;
    while((adjacents[i]).getsortant() != s2 ){ i +=1;};

    return adjacents[i];

}

Arete Graph_mat::acces_arete(string s1, string s2){
    int som1 = -1;
    int som2 = -1;
    int i = 0;
    while((som1 == -1) || (som2 == -1)){
        if(m_nomsommets[i] == s1){som1 = i;};
        if(m_nomsommets[i] == s2){som2 = i;};
        i +=1;
    }
      return Arete(s1, m_matadj[som1][som2], s2);
}

void Arete::print(){
    cout << "(" << m_entrant << ", " << m_poids << ", " << m_sortant << ")" << endl;
}

void Graph_list::print(){
    int i =0;
    for(i=0; i < m_nomsommets.size(); i++) {
            cout << "Les arêtes partant du sommet " << m_nomsommets[i] << " sont : " << endl ; 
            int j = 0;
            for(j=0; j < (m_listadj[m_nomsommets[i]]).size(); j++){
                (m_listadj[m_nomsommets[i]][j]).print();
            };
    };
    cout << '\n';
}

void Graph_mat::print(){        //On va transformer le graph_mat en graph_list pour utiliser la fonction précédente
    unordered_map<string, vector<Arete>> list_adj {};
    int i = 0;
    for(i=0; i < m_nomsommets.size(); i++){
        list_adj[m_nomsommets[i]] = vector<Arete> {};
    }
    int j = 0;
    for(i=0; i < m_nomsommets.size(); i++){
        for(j=0; j < m_nomsommets.size(); j++){
            if(m_matadj[i][j] != numeric_limits< float >::infinity()){                               // J'utilise un infini pour montrer qu'il n'y a pas d'arete
                (list_adj[m_nomsommets[i]]).push_back(Arete(m_nomsommets[i], m_matadj[i][j], m_nomsommets[j]));
            };
        };
    };

    (Graph_list(m_nomsommets, list_adj)).print(); // est-ce que je peux directement utiliser la fonction mat_to_list() (avec quel argument) plutot que de la copier/coller
}

Graph_list Graph_mat::mat_to_list(){
    unordered_map<string, vector<Arete>> list_adj {};
    int i = 0;
    for(i=0; i < m_nomsommets.size(); i++){
        list_adj[m_nomsommets[i]] = vector<Arete> {};
    }
    int j = 0;
    for(i=0; i < m_nomsommets.size(); i++){
        for(j=0; j < m_nomsommets.size(); j++){
            if(m_matadj[i][j] != numeric_limits< float >::infinity()){
                (list_adj[m_nomsommets[i]]).push_back(Arete(m_nomsommets[i], m_matadj[i][j], m_nomsommets[j]));
            };
        };
    };

    return Graph_list(m_nomsommets, list_adj);
}

Graph_mat Graph_list::list_to_mat(){
    vector<float> soustab(m_nomsommets.size(), numeric_limits< float >::infinity());
    vector<vector<float>> mat(m_nomsommets.size(), soustab);
    int i = 0;
    for(i=0; i < m_nomsommets.size(); i++){
        vector<Arete> adj (m_listadj[m_nomsommets[i]]);
        int j = 0;
        for(j=0; j < adj.size(); j++){
            string sortant = (adj[j]).getsortant();
            float poids = (adj[j]).getpoids();
        int k = 0;
        while((m_nomsommets[k] != sortant )&& (k < m_nomsommets.size())){ k+=1;};
            mat[i][k] = poids;
        
        };
        
    };

    return Graph_mat(m_nomsommets, mat);
}


// FIN DE LA QUESTION 1


void print_vect(std::vector<string> &input)     //Pour m'aider à visioner quand ça plante
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
}

void print_v(std::vector<Arete> &input)         //pareil
{
    for (int i = 0; i < input.size(); i++) {
        (input[i]).print();
    }
}

bool is_in_vect(string s, vector<string> v){    //Regarde si une chaine de caractere est déjà dans un vecteur (utile plus tard)
    int i = 0;
    bool bo(false);
    while((bo == false) && (i < v.size())){         //Y'a-t-il un "while(not(bo))" comme en Python ??
            if(v[i] == s){ bo = true;}
            i+=1;
    } return bo;
}

Graph_list file_to_graph_list(){
    cout << "Quel fichier voulez-vous ouvrir ? " << endl;
    string nom_fichier;
    cin >> nom_fichier;         //On demande le fichier
    cout << " " << endl;
    ifstream fichier(nom_fichier);      //On l'ouvre en mode lecture

    vector<string> stock;
    vector<Arete> stockaretes;

    if(fichier){
        string mot;
        while( (getline(fichier, mot, ' ')) || (getline(fichier, mot, '\n')) ){  //ici mon séparateur est un espace mais on peut remplacer le 3ème argument
        stock.push_back(mot);                   // CA NE MARCHE PAS SI JE CHANGE DE LIGNE DANS LE FICHIER TEXTE ET JE NE COMPRENDS PAS PQ !!!
    }
}
    else{cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;}     //Vérification qu'on a bien réussi à ouvrir le fichier

int i = 0;
while(i < (stock.size()/3)){
    stockaretes.push_back(Arete(stock[3*i], std::stoi(stock[3*i+2]), stock[3*i+1]));        //On stock les Aretes dans un conteneur
    i+=1;
}

vector<string> nomsommet;
unordered_map<std::string, std::vector<Arete>> dico;
                                                                    //Et maintenant on va créer le Graph_list
i = 0;
for(i=0; i < stockaretes.size(); i++){
    if(is_in_vect((stockaretes[i]).getentrant(), nomsommet)){               
            (dico[(stockaretes[i]).getentrant()]).push_back(stockaretes[i]);        //Si le sommet entrant est déjà dans le graph, alors on ajoute l'arete
    }
    else{
        nomsommet.push_back((stockaretes[i]).getentrant());                         // si le sommet entrant n'esr pas dans le graph, on l'ajoute a la liste des sommets et on créé une case dans le dico avec l'arete
        dico[(stockaretes[i]).getentrant()] = {stockaretes[i]};
    }
    if(is_in_vect((stockaretes[i]).getsortant(), nomsommet) == false){              //Si le sommet sortant n'est pas dans la liste des sommets on l'ajoute (pour ne pas oublier un sommet qui n'aurait aucune arete entrante)
        nomsommet.push_back((stockaretes[i]).getsortant());
        dico[(stockaretes[i]).getsortant()] = {};
            
    }
}
    return Graph_list(nomsommet, dico);
    
}

Graph_mat file_to_graph_mat(){
    Graph_list g;
    g = file_to_graph_list();       //On transforme le fichier en Graph_list
    Graph_mat gr;
    gr = g.list_to_mat();           //Et le Graph_list en Graph_mat
    return gr;
}


//J'ai pas compris l'histoire du .graph !!

// FIN DE LA QUESTION 2

bool is_in_vect_str(string s, vector<string> v){        //Fonction qui vérifie si une chaine de caractere est dans un vecteur, utile plus tard
    bool bo(false);
    int i = 0;
    while(not(bo) && ( i < v.size())){
        if(v[i] == s){bo = true;}
        i+=1;
    }
    return bo;
}

int indice(vector<string> v, string s){
    int k=0;
    while(v[k] != s){ k+=1;}
    return k;
}

void visite_sommet(string si, vector<string> *avisiter, std::unordered_map<std::string, std::vector<Arete>> adj){ //Pour parcourir le graph je créer une fonction récursive qui effectue la visite d'un sommet
                                                                                                                //La fonction se sert de l'adresse de la liste des sommets déjà visiter pour bien modifier la liste entre chaque execution ! (Sinon on reprend pas toujours la même liste !)
        int l = indice(*avisiter, si);        
        (*avisiter).erase((*avisiter).begin()+l);            //On visite si donc on l'enleve des sommets à visiter (On pourrait faire une lsite des sommets déjà visités plutôt, ça serait plus léger car on n'aurait qu'à push_back(), mais ça ne fonctionne pas dans le cas où un sommet n'est pas relié au reste, alors qu'avec la liste des sommets à visiter on peut le récupérer dedans)
        cout << si << endl ;               //On l'affiche
        vector<Arete> voisins;
        voisins = adj[si];               //On récup ses voisins
        int i=0;
        for(i=0; i < voisins.size(); i++){
            if(is_in_vect_str((voisins[i]).getsortant(), *avisiter)){       //On sélectionne les voisins qui n'ont pas encore été visités
                (voisins[i]).print();                                          //On print l'arete
                visite_sommet((voisins[i]).getsortant(), avisiter, adj);       //Et on visite les voisins
            }          
        }    
}

void Graph_list::Deep_first_search_rec_graph_list(){        // CA MARCHE PAS CA BOUCLE A L'INFINI
    vector<string> avisiter(m_nomsommets.size());       //Vect des sommets à visiter, tous au début
    copy(m_nomsommets.begin(), m_nomsommets.end(), avisiter.begin());
    while(avisiter.size() > 0){   // Ce while est NECESSAIRE si jamais un sommet n'est relié au sommet de départ par AUCUN CHEMIN (sinon il n'est pas print)
    if(avisiter.size() > 0){     //Tant qu'il reste des sommets à visiter, on les visite
        visite_sommet(avisiter[0], &avisiter, m_listadj);                               //On commence par le 1er sommet du graph mais on aurait pu ajouter un argument pour choisir où commencer
      }
    }
}

void Graph_mat::Deep_firts_search_rec_graph_mat(){
    Graph_mat graph = Graph_mat(m_nomsommets, m_matadj);        //On peut pas faire autrement ??
    Graph_list g = graph.mat_to_list();
    g.Deep_first_search_rec_graph_list();

}


// FIN DE LA QUESTION 3
// Faut partir de n'importe où, ou choisir un sommet de départ ? S'il faut il suffit de changer l'initialisation avec un argument
void Graph_list::Deep_first_search_graph_list(){
    vector<string> visites{};                           //les sommets visités, c'est pas nécessaire mais c'est pour m'aider à mis retrouver (si on veut gagner de la memoire on supprime cette ligne et la 282)
    stack<string> decouverts;                        //les sommets découverts
    decouverts.push(m_nomsommets[0]);
    vector<string> avisiter(m_nomsommets.size());       //Vect des sommets à visiter, tous au début
    copy(m_nomsommets.begin(), m_nomsommets.end(), avisiter.begin());
    int l = indice(avisiter, (m_nomsommets[0]));        
    avisiter.erase(avisiter.begin()+l);              //Le sommet qu'on met dans decouverts des le debut ne doit pas être dans avisiter sinon il sera visite 2 fois

    while((avisiter.size() > 0 ) || (decouverts.size() > 0)){  //Tant qu'il reste de sommets à visiter et à analyser, on agit
        if((decouverts.size() == 0) && (avisiter.size() != 0)){ //Au cas ou des sommets ne serait reliés par aucune arete venant de reste !!
        decouverts.push(avisiter[avisiter.size()-1]);
        avisiter.pop_back();
        }
        else{        
        string sommet = decouverts.top();                //On prend un sommet découvert
        decouverts.pop();    
        visites.push_back(sommet);              //On l'ajoute aux sommets visités
        cout << sommet << endl ;               //On le print
        vector<Arete> voisins = m_listadj[sommet];      //On regarde ses voisins
        int k =0;
        for(k=0; k < voisins.size(); k++){
            if(is_in_vect_str((voisins[k]).getsortant(), avisiter)){        //Si un voisin est dans le vect des sommets à visiter
                (voisins[k]).print();                                       //On print l'arete
                decouverts.push((voisins[k]).getsortant());            //On le met dans les sommets découverts
                int j = indice(avisiter, (voisins[k]).getsortant());        
                avisiter.erase(avisiter.begin()+j);                         //Et on le retire des sommets avisiter
                    } 
            }
        }
    }
}

void Graph_mat::Deep_firts_search_graph_mat(){
    Graph_mat graph = Graph_mat(m_nomsommets, m_matadj);
    Graph_list g = graph.mat_to_list();
    g.Deep_first_search_graph_list();
}


// FIN DE LA QUESTION 4

void rec_graph(int niveau_max, string depart, vector<string> avisiter, unordered_map<std::string, vector<Arete>> listadj){     //A lire apres le programme suivant pour mieux comprendre : on se sert de la récursiviter pour s'arreter au bon niveau
    vector<Arete> voisins = listadj[depart];

    if(niveau_max == 1){   //Le cas où on veut avoir qu'un seul niveau : on print juste les arêtes des fils (et les fils decouverts)
            
            int k =0;
            for(k=0; k < voisins.size(); k++){
            if(is_in_vect_str((voisins[k]).getsortant(), avisiter)){        
                (voisins[k]).print();                                     //Ici on print les aretes 
                cout << (voisins[k]).getsortant() << '\n';                //Ici le sommet decouvert           
                int j = indice(avisiter, (voisins[k]).getsortant());        
                avisiter.erase(avisiter.begin()+j);                         
                    } 
            }    
    }
    else{        //Le cas où on doit visiter plusieurs niveaux
        vector<string> sortants;
        int k = 0;
        for(k=0; k < voisins.size(); k++){
            if(is_in_vect_str((voisins[k]).getsortant(), avisiter)){ 
                sortants.push_back((voisins[k]).getsortant());          //On enregistre les sommets du niveau suivant pour les parcourir ensuite
                (voisins[k]).print();
                cout << (voisins[k]).getsortant() << '\n';                                                   
                int j = indice(avisiter, (voisins[k]).getsortant());        
                avisiter.erase(avisiter.begin()+j); }
    } 
    k =0;
    for(k=0; k < sortants.size(); k++){
        rec_graph(niveau_max - 1, sortants[k], avisiter, listadj);   //On s'attaque au niveau suivant, et il reste un niveau de moins à faire
    }
        }           //Dans le cas où 2 aretes entre le niveau k et k+1 sont reliées à un même nouveaux sommets k les 2 aretes sont print (et donc le nouveau sommet 2fois), je ne vois pas trop comment corriger ça

    }

void Graph_list::Breadth_first_search_graph_list(int niveau_max, string depart){ 
    vector<string> visites{};                           
    queue<string> decouverts;                        //les sommets découverts ON REMPLACE STACK PAR QUEUE
    decouverts.push(depart);
    vector<string> avisiter(m_nomsommets.size());       
    copy(m_nomsommets.begin(), m_nomsommets.end(), avisiter.begin());
    int l = indice(avisiter, (depart));        
    avisiter.erase(avisiter.begin()+l);

if((niveau_max == 0)){      //Si le niveau est 0 alors on parcours tout le graaph : simple copier coller du parcours en profondeur en remplacant la pile par une file
    while((avisiter.size() > 0 ) || (decouverts.size() > 0)){  
        if((decouverts.size() == 0) && (avisiter.size() != 0)){ //On rajoute la vérifciation de niveau max=0 car cela veut dire que l'utilisateur veut parcourir tout le graaph, si la valeur et autre alors un sommet non relié n'est pas dans la descendance de la racine donc il ne doit pas être parcouru
        string s = avisiter[avisiter.size()-1];
        decouverts.push(avisiter[avisiter.size()-1]);
        avisiter.pop_back();
        cout << s << '\n'; //On print le sommet entrant et pas d'arete car il ne provient d'aucune arete
        }
        else{        
        string sommet = decouverts.front();                
        decouverts.pop();    
        visites.push_back(sommet);              
        vector<Arete> voisins = m_listadj[sommet];      
        int k =0;
        for(k=0; k < voisins.size(); k++){
            if(is_in_vect_str((voisins[k]).getsortant(), avisiter)){        
                (voisins[k]).print();                           //On print l'arete decouverte
                cout << (voisins[k]).getsortant() << '\n';      //Et le sommet qui en sort                                
                decouverts.push((voisins[k]).getsortant());            
                int j = indice(avisiter, (voisins[k]).getsortant());        
                avisiter.erase(avisiter.begin()+j);                         
                    } 
            }
        }
    }}

else{rec_graph(niveau_max, depart, avisiter, m_listadj);}
}

void Graph_mat::Breadth_first_search_graph_mat(int niveau_max, string depart){ 
    Graph_mat graph = Graph_mat(m_nomsommets, m_matadj);
    Graph_list g = graph.mat_to_list();
    g.Breadth_first_search_graph_list(niveau_max, depart);
}

//Les programmes ne print pas le sommet de départ mais je ne pense pas que ce soit un probleme car l'utilisateur le connait puisqu'il le donne

// FIN DE LA QUESTION 5

string dist_min(vector<string> avisiter, unordered_map<string, float> distances){
    int i=0;
    float min = numeric_limits<float>::infinity();
    string som_min;
    for(i=0; i < avisiter.size(); i++){
        if(distances[avisiter[i]] < min){
            min = distances[avisiter[i]];
            som_min = avisiter[i];
        }
    }
    return som_min;
}

void Graph_list::Dijkstra(string s1, string s2){
    

    vector<string> avisiter(m_nomsommets.size());       //Vector des sommets à visiter (tous au début)
    copy(m_nomsommets.begin(), m_nomsommets.end(), avisiter.begin());

    unordered_map<string, float> distances;    //dico qui associe à chaque sommet la distance du plus court chemin actuel au sommet s1 (0 pour s1 et inf pour les autres au début)
    unordered_map<string, string> peres; //dico qui recense les pères actuel de chaque sommets (pour s1 aucun donc on met "Racine", pour les autres aucun au début donc on met "Aucun")
    int i = 0;
    for(i=0; i < m_nomsommets.size(); i++){
        if(m_nomsommets[i] != s1){
            peres[m_nomsommets[i]] = "Aucun";
            distances[m_nomsommets[i]] = numeric_limits<float>::infinity();
        }
        else{peres[m_nomsommets[i]] = "Racine";
             distances[m_nomsommets[i]] = 0;}
    }

    string min;
    bool bo(true);
    while(bo && (avisiter.size() > 0)){
        min = dist_min(avisiter, distances); //On sélectionne le sommet encore à visiter avec la distance la plus faible à s1
        if(distances[min] == numeric_limits<float>::infinity()){
            bo = false;             //Si le sommet le plus proche est inateignable c'est qu'on a fini !
        }
        else{
            vector<Arete> voisins = m_listadj[min];
            i = 0;
            for(i=0; i < voisins.size(); i++){              //On relache tous les aretes qui partent du sommet //Relacher une arete (s1,p,s2) c'est remplacer la distance a s2 par la distance à s1 + p si c'est inférieur à la distance actuelle à t2 (et actualiser le pere de t2)
                if((peres[min] != "Aucun" ) && ( (distances[min] + (voisins[i]).getpoids()) < distances[(voisins[i]).getsortant()] )){
                    distances[(voisins[i]).getsortant()] = distances[min] + (voisins[i]).getpoids();
                    peres[(voisins[i]).getsortant()] = min;
    }    
            }
            int j = indice(avisiter, min);
            avisiter.erase(avisiter.begin()+j);     //On supprime le sommet visité de avisiter

        }
    } //Ici on a visité tous les sommets visitable et on a le chemin le plus court qui part de s1 vers chaque sommet ! On était obligé d'obtenir le résultat pour chaque sommet même si seul le trajet s1 s2 nous intéresse pour être sûr de passer par tous les chemins possibles
    //Maintenant il n'y a plus qu'à print ce qui nous intéresse

    if(distances[s2] == numeric_limits<float>::infinity()){             //Si la distance obtenue est infinie c'est qu'il n'y a pas de chemin entre les 2 sommets !!
        cout << "Il n'y a pas de chemin qui relie " << s1 << " à " << s2 << '\n' ;
        cout << '\n';
    }
    else{                   //Sinon, on renvoie la distance et on remonte l'arbre des pères pour rembobiner le chemin parcouru
    cout << "La distance de " << s1 << " à " << s2 << " est : " << distances[s2] << '\n' ;
    cout << "Ce chemin s'effectue en parcourant les sommets :" << '\n';
    vector<string> parcours = {s2};
    string s = s2;
    while(s != s1){
        s = peres[s];
        parcours.push_back(s);
    }
    i = 0;
    for(i=0; i < parcours.size(); i++){
        cout << parcours[parcours.size()- i - 1] << '\n';
    }
    cout << '\n';
    }
}


// FIN DE LA QUESTION 6

void Graph_mat::Floyd_Warshall(){
    vector<vector<float>> w(m_matadj.size());       //Vector des sommets à visiter (tous au début)
    copy(m_matadj.begin(), m_matadj.end(), w.begin());
    int k=0;
    int i=0;
    int j=0;
    int n = m_nomsommets.size();
    for(k=0; k < n; k++){
        for(i=0; i < n; i++){
            for(j=0; j < n; j++){
                w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
            }
        }
    }
    i=0;
    j=0;
    for(i=0; i < n; i++){
        for(j=0; j < n; j++){
            if(i != j){     //On s'en fout se la distance d'une ville à elle même
            if(w[i][j] == numeric_limits<float>::infinity()){
                    cout << "Il n'existe pas de chemin entre " << m_nomsommets[i] << " et " << m_nomsommets[j] << '\n' ;}
            else{
                    cout << "La distance de " << m_nomsommets[i] << " à " << m_nomsommets[j] << " est : " << w[i][j] << '\n' ;}
            }
        }
    }
}
//Comment on récupére les chemins ?? Pour l'instant ça me donne juste la distance entre chaque paire !


// FIN DE LA QUESTION 7
