#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<typeinfo>
using namespace std;

template <typename T>
class Player{
    
    char name;
    char lname;
    int age;

    public:
        Player(char n, char ln, int a):name(n), lname(ln), age(a){}
        char getName(){return name;}
        char getLastName(){return lname;}
        int getAge(){return age;}
        void setName(char ng){name=ng;}
        void setLastName(char cg){lname=cg;}
        void setAge(int a){age=a;}
        virtual int GetAction() = 0;
        virtual void put_count() = 0;
        virtual void StampaGiocatore() = 0;
        virtual ostream& print (ostream& os){
            os<<"Class="<<typeid(*this).name();
            return os;
        }
        /*operator[](){

        }*/

};

template<typename T>
class Def:public Player<T>{

    int defend;
    static int count_def;

    public:

        Def(char n, char ln, int a):Player<T>(n, ln, a){
            count_def++;
            defend = (rand() % a) + (int)(n+ln)/2;
        }
        void put_count()override{
        	cout<<"Numero oggetti DEF creati: "<<count_def<<endl;
		}
        int GetAction()override{
            return defend;
        }
        void StampaGiocatore()override{
            cout<<"Nome: "<<this->getName()<<endl;
            cout<<"Cognome: "<<this->getLastName()<<endl;
            cout<<"Eta': "<<this->getAge()<<endl;
        }
        ostream& print (ostream& os)override{
            Player<T>::print(os);
            os<<"\nNome: "<<this->getName();
            os<<", Cognome: "<<this->getLastName();
            os<<", Eta': "<<this->getAge()<<endl;
            return os;
        }
};

template <typename T>
int Def<T> :: count_def = 0;  //azzero il contatore 

template<typename T>
class Atk:public Player<T>{

    int attack;
    static int count_atk;

    public:

        Atk(char n, char ln, int a):Player<T>(n, ln, a){
            count_atk++;
            if(a%2 == 0)
                attack = (rand() % a);
            else
                attack = 10 + (rand() % (int)(n*ln)/2);
        }
        void put_count()override{
        	cout<<"Numero oggetti ATK creati: "<<count_atk<<endl;
		}
        int GetAction()override{
            return attack;
        }
        void StampaGiocatore()override{
            cout<<"Nome: "<<this->getName()<<endl;
            cout<<"Cognome: "<<this->getLastName()<<endl;
            cout<<"Eta': "<<this->getAge()<<endl;
        }
        ostream& print (ostream& os)override{
            Player<T>::print(os);
            os<<"\nNome: "<<this->getName();
            os<<", Cognome: "<<this->getLastName();
            os<<", Eta': "<<this->getAge()<<endl;
            return os;
        }
};

template <typename T>
int Atk<T> :: count_atk = 0;  //azzero il contatore

template <typename T>
ostream& operator<< (ostream& os, Player<T>& p){
    return p.print(os);
}

int main(){

    const int DIM = 10;

    srand(time(NULL));

    //Creo la prima squadra
    Player<int>* team1[DIM]; 
    char S[10]= {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'l'};
    char n;
    char ln;
    int w; //età
    for(int i=0; i<DIM; i++)
    {
        n = S[rand()%10];
        ln = S[rand()%10];
        w = rand()%41 +20;  //genero valori di età ragionevoli
        if(i%2 == 0)
            team1[i] = new Def<int> (n, ln, w);
        else
            team1[i] = new Atk<int> (n, ln, w);
    }
    
    for(int i=0; i<DIM; i++)
        cout<<i<<") "<<*team1[i]<<endl;
    
    if(typeid(*team1[0]) == typeid(Def<int>))
	    	team1[0]->put_count();  //Confermo la creazione di 5 def
	if(typeid(*team1[1]) == typeid(Atk<int>)) //Confermo la creazione di 5 atk
	    	team1[1]->put_count();

//----------------------------------------------------------------

    Player<int>* team2[DIM];
    //Creo la seconda squadra
    for(int i=0; i<DIM; i++)
    {
        n = S[rand()%10];
        ln = S[rand()%10];
        w = rand()%41 +20;  //genero valori di età ragionevoli
        if(i%2 == 0)
            team2[i] = new Def<int> (n, ln, w);
        else
            team2[i] = new Atk<int> (n, ln, w);
    }
    
    for(int i=0; i<DIM; i++)
        cout<<i<<") "<<*team2[i]<<endl;

//---------------------------------------------------------------------------

    double sum_atk = 0.0;
    double sum_def = 0.0;
    for(int i=0; i<DIM; i++)
    {
        if(typeid(*team1[i]) == typeid(Atk<int>))
            sum_atk += static_cast<Atk<int>*>(team1[i])->GetAction();
        else
            sum_def += static_cast<Def<int>*>(team1[i])->GetAction();
    }
    cout<<"Avg Atk Team1: "<<sum_atk/5<<endl;
    cout<<"Avg Def Team1: "<<sum_def/5<<endl;
//------------------------------------------------------------------------------
    for(int i=0; i<DIM; i++)
    {
        if(typeid(*team2[i]) == typeid(Atk<int>))
            sum_atk += static_cast<Atk<int>*>(team2[i])->GetAction();
        else
            sum_def += static_cast<Def<int>*>(team2[i])->GetAction();
    }
    cout<<"\nAvg Atk Team2: "<<sum_atk/5<<endl;
    cout<<"Avg Def Team2: "<<sum_def/5<<endl;

    cout<<"\nInizia il match!"<<endl;
    int chose = rand()%DIM;
    int attack;
    int defend;
    unsigned short goal1 = 0;
    unsigned short goal2 = 0;
    while(goal1 < 3 || goal2 < 3)
    {
        chose = rand()%DIM; 
        attack = static_cast<Atk<int>*>(team1[chose])->GetAction();
        defend = static_cast<Def<int>*>(team2[chose])->GetAction();
        if(attack > defend)
            goal1++;
        else
            goal2++;   
    }
    
    if(goal1 > goal2)
        cout<<"Team1 vince con "<<goal1<<" goals"<<endl;
    else
        cout<<"Team2 vince con "<<goal2<<" goals"<<endl;
}