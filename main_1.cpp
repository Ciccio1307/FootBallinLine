#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <climits>
#include <cmath>

#define DIM 10

using namespace std;

template <class T>
class AbstractVec
{
    T **data;
protected:
    int max_size;
    int read_size;
    int write_size;

    T *getL(int index)
    {
        T *temp = nullptr;

        if (index < max_size)
            temp = data[index];

        return temp;
    }
    bool exist(int index)
    {
        // T* temp=nullptr;

        if (index < max_size)
            return false;

        if (data[index])
            return true;
        else
            return false;
    }

    void set(int i, T x)
    {
        if (i < max_size)
            data[i] = x;
    }


  

public:
  void shuffle()
    {
        for (int i = 0; i < max_size; i++)
        {
            if (data[i])
            {
                for (int k = i; k < max_size; k++)
                {
                    if (data[k])
                    {
                        T *temp;
                        temp = data[i];
                        data[i] = data[k];
                        data[k] = temp;
                    }
                }
            }
        }
    }
    AbstractVec(int max_size)
    {
        data = new T *[max_size];
        for (int i = 0; i < max_size; i++)
        {
            data[i] = nullptr;
        }
        read_size = 0;
        write_size = 0;
        max_size = max_size;
    }
    int len()
    {
        int cont = 0;
        for (int i = 0; i < max_size; i++)
        {
            if (data[i])
                cont++;
        }
        return cont;
    }

    virtual T *next() = 0;
    virtual bool insert(T x) = 0;
virtual ostream& put(ostream & os)
{
os<<"Class = "<<typeid(*this).name()<<" , max_size "<<max_size <<" , vec[ ";
for(int i=0; i<max_size; i++)
{
    if(data[i])
    {
        os<<*data[i]<<" ";

    }else{
        os<<" ";
    }
}
os<<" ] . len()= "<<len();
return os;

}


};

template <class T>
class PlainVec : public AbstractVec<T>
{

public:
    PlainVec(int max_size) : AbstractVec<T>(max_size) {}

    T *next()
    {
        T *val = nullptr;
        if (AbstractVec<T>::read_index < AbstractVec<T>::max_size - 1)
        {
            val = AbstractVec<T>::get(AbstractVec<T>::read_index++);
        }
        return val;
    }

    bool insert(T x)
    {
        bool ris = false;
        if (AbstractVec<T>::write_index < AbstractVec<T>::max_size - 1)
        {
           AbstractVec<T>:: set(x, AbstractVec<T>::write_index++);

            ris = true;
        }
        return ris;
    }

    ostream& put(ostream& os) {
            AbstractVec<T>::put(os);
            return os;
        }

};

template <class T>
class CircularVec : public AbstractVec<T>
{
    int cycles;

public:
    int getCycles() { return cycles; }
    CircularVec(int max_size) : AbstractVec<T>(max_size)
    {
        cycles = 0;
    }

    T *next()
    {
        T *val = nullptr;
        if (AbstractVec<T>::read_index < AbstractVec<T>::max_size - 1)
        {
            T *val = AbstractVec<T>::get(AbstractVec<T>::read_index++);
            if (AbstractVec<T>::read_index == AbstractVec<T>::max_size)
            {
                AbstractVec<T>::read_index = 0;
                cycles++;
            }
        }
        return val;
    }

    bool insert(T x)
    {
        bool ris = false;
        if (AbstractVec<T>::write_index < AbstractVec<T>::max_size - 1)
        {
            AbstractVec<T>::set(x, AbstractVec<T>::write_index++);

            ris = true;

            if (AbstractVec<T>::write_index == AbstractVec<T>::max_size)
            {
                AbstractVec<T>::write_index = 0;
                cycles++;
            }
        }

        return ris;
    }
    ostream& put(ostream& os) {
            AbstractVec<T>::put(os);
            os << ", cycles=" << cycles;
            return os;
        }
};

template<class T>
ostream& operator<<(ostream& os, AbstractVec<T>& obj) {
    return obj.put(os);
}

int main() {
    srand(424242);

    AbstractVec<int>* vec[DIM];

    for(int i=0; i<DIM; i++) {
        int size = rand()%16+5;
        if(rand()%2){
            vec[i] = new PlainVec<int>(size);
        } else {
            vec[i] = new CircularVec<int>(size);
        }
    }
    
    for(int i = 0; i < DIM; i++) {
        cout << *vec[i] << endl;
    }
}