#include <thread>
#include <vector>

using namespace std;

class Matrice
{
    public:
    //les donnes de matrice
    vector <vector<int>> DataMatrice;

    //resultat de produit M1xM2
    vector <vector<int>> resultat;

    //la valeur de la matrice carree // par defaut 3
    int n = 3;



    void initialiser(){
        //initialiser les elements de la matrice
        for (int i=0; i<n; i++) {
			vector<int> ligne;
			for (int j=0; j<n; j++) {
			 ligne.push_back(0);
			}

			 DataMatrice.push_back(ligne);
		}

		//initialiser la matrice qui stoke le resultat

		for (int i=0; i<n; i++) {
			vector<int> ligne;
			for (int j=0; j<n; j++) {
			 ligne.push_back(0);
			}

			 resultat.push_back(ligne);
		}

    }


    //Remplissage
    void Remplissage(){
        cout << "Entrez votre matrice: " << endl;
        cout << "Entrez la valeur de n : " << endl;
        cin >> n;

        for(int i=0; i<n; i++){
				for(int j =0; j<n ; j++){
				    cout << "Element : [" << i << "] ["<< j << "] >" << " ";
					cin >> DataMatrice[i][j];
			}
		}
    }

    //Affichage Matrice
    void  AffichageMatrice(){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout <<  "element [" << i << "]" << "[" << j << "] = "<<DataMatrice[i][j] << endl;
            }
            cout <<endl;
        }
    }

    //AffichageResultat
    void  AffichageResultat(){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout <<  "[" << i << "]" << "[" << j << "] = "<<resultat[i][j] << " ";
            }
            cout <<endl;
        }
    }

    //Methode 1 //Start
    void CalculProduitParSequentielle(Matrice *m2){
          for (int i=0;i<n;i++)
        	{
		        for (int j=0;j<n;j++)
		        {
		        	for (int k=0;k<n;k++)
			        {
			    	resultat[i][j]=DataMatrice[i][k]*m2->DataMatrice[k][j]+resultat[i][j];
		        	}
		        }
	        }
        cout << "Resultat par methode Sequentielle : " << endl;
        AffichageResultat();
        cout << endl;

    }

    //Methode 1 //End


    //Methode 2 //Start

    //calcul produit i et j
    void Produitpij(int i,int j,Matrice *m2)
    {
        for (int k=0;k<n;k++){
            resultat[i][j]=DataMatrice[i][k]*m2->DataMatrice[k][j]+resultat[i][j];
        }
    }


    void CalculProduitParValeur(Matrice *m2){

         //nombre de thread nb_thread_par_element = n*n // un thread pour chaque produit des elements
         int nb_thread_par_element = n*n;
         thread threadVAL[nb_thread_par_element];
        for (int i=0;i<n;i++){
		  for (int j=0;j<n;j++){
		    int index = i+j;
		    threadVAL[index]= std::thread(&Matrice::Produitpij,this,i,j,m2);
            threadVAL[index].join();
		  }
	   }

        cout << "Resultat par methode de calcul par chaque element: " << endl;
        AffichageResultat();
        cout << endl;

    }
    //Methode 2 //End


    //Methode 3 //Start

    //calcul produit du block
    void CalculBlock(int i,Matrice *m2)
    {
        for (int j=0;j<n;j++){
            for (int k=0;k<n;k++){

			    	resultat[i][j]=DataMatrice[i][k]*m2->DataMatrice[k][j]+resultat[i][j];

                }
            }
    }

    //calcul produit de tout les blocks
    void CalculProduitParBlock(Matrice *m2)
    {

        thread threadBLK[n];
		for (int i=0;i<n;i++)
		 {
		        	threadBLK[i]= std::thread(&Matrice::CalculBlock,this,i,m2);
                    threadBLK[i].join();
		}

        cout << "Resultat par methode de calcul par chaque block: " << endl;
        AffichageResultat();
        cout << endl;
    }
    //Methode 3 //End


};

int main(){

    Matrice mat1;
    mat1.initialiser();
    mat1.Remplissage();


    Matrice mat2;
    mat2.initialiser();
    mat2.Remplissage();

    //calcule par Produit Seauentielle - Methode 1
    mat1.CalculProduitParSequentielle(&mat2);

    //calcule par Produit element - Methode 2
    //mat1.CalculProduitParValeur(&mat2);

    //calcule par Produit block - Methode 3
   // mat1.CalculProduitParBlock(&mat2);


	return 0 ;
}
