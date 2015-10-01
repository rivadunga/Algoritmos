#include <queue>
#include <iostream>
using namespace std;

int max(int x,int y){
    if(x > y)
        return x;
    return y;
}
template<class T>class NodoArbolBinario{
    public:
        T element;
        int altura;
        NodoArbolBinario<T>* izq;
        NodoArbolBinario<T>* der;
        NodoArbolBinario<T>* padre;
        NodoArbolBinario<T>(){
            izq = NULL;
            der = NULL;
            padre = NULL;
        }
        int numChildren(){
            int r = 1;
            if(izq != NULL){
                r += izq->numChildren();
            }
            if(der != NULL){
                r += der->numChildren();
            }
            return r;
        }
};
template<class T> class ArbolBinarioEnlazado{
    protected:
        int cont;
        NodoArbolBinario<T>* raiz;
        int busca(T element,NodoArbolBinario<T>* actual){
            if(actual->element == element)
                return 1;
            if(actual->izq == NULL && actual->der == NULL)
                return 0;
            if(actual->izq == NULL && actual->der != NULL)
                return busca(element,actual->der);
            if(actual->izq != NULL && actual->der == NULL)
                return busca(element,actual->izq);
            return busca(element,actual->izq) | busca(element,actual->der);
        }
        int altura(NodoArbolBinario<T>* a){
            if(a == NULL)
                return 0;
            return max(altura(a->der),altura(a->izq))+1;
        }
    public:
        void imprimirLevelOrder(){
       		if(raiz != NULL){
		        queue<NodoArbolBinario<T>*> cola;
		        cola.push(raiz);
		        while(!cola.empty()){
		            cout << cola.front()->element << " " << cola.front()->altura << " ";
		            if(cola.front()->izq != NULL){
		            	cola.push(cola.front()->izq);
                    }
		            if(cola.front()->der != NULL){
		            	cola.push(cola.front()->der);
		            }
		            cola.pop();
		            cout<<"\n";
		        }
            }
            cout << "\n";
        }
        ArbolBinarioEnlazado(){
            raiz = NULL;
            cont = 0;
        }
        int size(){
            return cont;
        }
        int getAltura(){
            return altura(&raiz);
        }
        T find(T element){
            if(busca(element,raiz) == 1){
                return element;
            }
            return NULL;
        }
        bool contains(T element){
            if(busca(element,raiz))
                return true;
            return false;
        }
};
template<class T> class ArbolBinarioDeBusqueda : public ArbolBinarioEnlazado<T>{
    protected:
        void remplazaActualPorHijo(NodoArbolBinario<T> *actual,NodoArbolBinario<T> *hijo){
            hijo->padre = actual->padre;
            if(actual == this->raiz){
                this->raiz = hijo;
            }else{
                if(actual->padre->izq == actual)
                    hijo->padre->izq = hijo;
                else
                    hijo->padre->der = hijo;
            }
        }
    public:
        T borra(T element){
            if(this->raiz != NULL){
                NodoArbolBinario<T>* actual= this->raiz;
                // encuentra el nodo correcto
                while(actual->element != element && actual != NULL){
                    if(element < actual->element){
                        actual = actual->izq;
                    }else{
                        actual = actual->der;
                    }
                }
                if(actual == NULL)
                    return element;
                //mueve el arbol
                NodoArbolBinario<T> *hijo = actual->der;
                if(hijo == NULL){
                    hijo = actual->izq;
                    if(hijo != NULL){
                        this->remplazaActualPorHijo(actual,hijo);
                    }else if(actual == this->raiz){
                        this->raiz = NULL;
                    }
                }else{
                    if(hijo->izq == NULL){
                        this->remplazaActualPorHijo(actual,hijo);
                        hijo->izq = actual->izq;
                        if(actual->izq != NULL)
                        	actual->izq->padre = hijo;
                    }else{
                        while(hijo-> izq != NULL){
                            hijo = hijo->izq;
                        }
                        hijo->padre->izq = hijo->der;
                        if(hijo->der != NULL)
                            hijo->der->padre = hijo->padre;
                        this->remplazaActualPorHijo(actual,hijo);
                        hijo->der = actual->der;
                        hijo->izq = actual->izq;
                        if(actual->der != NULL)
                        	actual->der->padre = hijo;
                        if(actual->izq != NULL)
                        	actual->izq->padre = hijo;
                    }
                }
                delete actual;
                this->cont--;
            }
            return element;
        }
        T encuentraMin(){
            NodoArbolBinario<T>* actual = this->raiz;
            while(actual->izq != NULL){
                actual= actual->izq;
            }
            actual->element;
        }
        T encuentraMax(){
            NodoArbolBinario<T>* actual = this->raiz;
            while(actual->der != NULL){
                actual= actual->der;
            }
            return actual->element;
        }
        void inserta(T element){
            this->cont++;
            NodoArbolBinario<T>* actual = this->raiz;
            NodoArbolBinario<T>* anterior = NULL;
            NodoArbolBinario<T>* nuevo = new NodoArbolBinario<T>;
            while(actual != NULL){
                anterior = actual;
                if(element < actual->element){
                    actual = actual->izq;
                }else{
                    actual = actual->der;
                }
            }
            nuevo.padre =  anterior;
            nuevo.element = element;
            if(actual == this->raiz){
                this->raiz = nuevo;
            }else{
                if(element < anterior->element){
                    anterior->izq = nuevo;
                }else{
                    anterior->der = nuevo;
                }
            }
        }
};
template<class T> class ArbolBinarioDeBusquedaBalanceado: public ArbolBinarioDeBusqueda<T>{
    protected :
    	void calculaAltura(NodoArbolBinario<T> *n){
    		if(n->izq != NULL && n->der != NULL){
                n->altura = max(n->der->altura,n->izq->altura)+1;
            }else if(n->der != NULL){
                n->altura = n->der->altura+1;
            }else if(n->izq != NULL){
                n->altura = n->izq->altura+1;
            }else{
            	n->altura = 0;
            }
    	}
    	int calculaFE(NodoArbolBinario<T> *n){
    		int fe;
    		if(n->izq != NULL && n->der != NULL){
                    fe = n->der->altura-n->izq->altura;
                }else if(n->der != NULL){
                    fe = n->der->altura+1;
                }else if(n->izq != NULL){
                    fe = -n->izq->altura-1;
                }else{
                    fe = 0;
                }
                return fe;
    	}
        NodoArbolBinario<T>* izqizq(NodoArbolBinario<T> *actual){
            NodoArbolBinario<T> *nuevoPadre = actual->izq;
            this->remplazaActualPorHijo(actual,nuevoPadre);
            actual->izq = nuevoPadre->der;
            if(nuevoPadre->der != NULL)
            	nuevoPadre->der->padre = actual;
            nuevoPadre->der = actual;
            actual->padre = nuevoPadre;
            return nuevoPadre;
        }
        NodoArbolBinario<T>* izqder(NodoArbolBinario<T> *actual){
            NodoArbolBinario<T> *nuevoPadre = actual->izq->der;
            actual->izq->der = nuevoPadre->izq;
            if(nuevoPadre->izq != NULL)
            	nuevoPadre->izq->padre = actual->izq;
            this->remplazaActualPorHijo(actual,nuevoPadre);
            actual->izq->padre = nuevoPadre;
            nuevoPadre->izq = actual->izq;
            actual->izq = nuevoPadre->der;
            if(nuevoPadre->der != NULL)
            	nuevoPadre->der->padre = actual;
            nuevoPadre->der = actual;
            actual->padre = nuevoPadre;
            return nuevoPadre;
        }
        NodoArbolBinario<T>* derizq(NodoArbolBinario<T> *actual){
            NodoArbolBinario<T> *nuevoPadre = actual->der->izq;
            actual->der->izq = nuevoPadre->der;
            if(nuevoPadre->der != NULL)
            	nuevoPadre->der->padre = actual->der;
            this->remplazaActualPorHijo(actual,nuevoPadre);
            actual->der->padre = nuevoPadre;
            nuevoPadre->der = actual->der;
            actual->der = nuevoPadre->izq;
            if(nuevoPadre->izq != NULL)
            	nuevoPadre->izq->padre = actual;
            nuevoPadre->izq = actual;
            actual->padre = nuevoPadre;
            return nuevoPadre;
        }
        NodoArbolBinario<T>* derder(NodoArbolBinario<T> *actual){
            NodoArbolBinario<T> *nuevoPadre = actual->der;
            this->remplazaActualPorHijo(actual,nuevoPadre);
            actual->der = nuevoPadre->izq;
            if(nuevoPadre->izq != NULL)
            	nuevoPadre->izq->padre = actual;
            nuevoPadre->izq = actual;
            actual->padre = nuevoPadre;
            return nuevoPadre;
        }
        NodoArbolBinario<T>* balancea(NodoArbolBinario<T> *actual,int fe){
            int caso = 0;
            if(fe < 0){
                actual = actual->izq;
            }else{
                actual = actual->der;
                caso += 2;
            }
            fe = calculaFE(actual);
            if(fe > 0){
                caso++;
            }
            actual = actual->padre;
            if(caso == 0){
                actual = izqizq(actual);
            }else if(caso == 1){
                actual = izqder(actual);
            }else if(caso == 2){
                actual = derizq(actual);
            }else
                actual = derder(actual);
            calculaAltura(actual->izq);
            calculaAltura(actual->der);
            calculaAltura(actual);
            return actual;
        }
        void acomoda(NodoArbolBinario<T> *actual){
            int fe;
            while(actual->padre != NULL){
                actual = actual->padre;
                calculaAltura(actual);
                fe = calculaFE(actual);
                if(fe < -1 || fe > 1){
                    actual = balancea(actual,fe);
                }
            }
        }
    public:
        T borra(T element){
            if(this->raiz != NULL){
                NodoArbolBinario<T>* actual= this->raiz;
                // encuentra el nodo correcto
                while(actual != NULL && actual->element != element){
                    if(element < actual->element){
                        actual = actual->izq;
                    }else{
                        actual = actual->der;
                    }
                }
                if(actual == NULL)
                    return element;
                //mueve el arbol
                NodoArbolBinario<T> *hijo = actual->der,*t = actual,temp;
                if(hijo == NULL){
                    hijo = actual->izq;
                    if(hijo != NULL){
                        this->remplazaActualPorHijo(actual,hijo);
                    }else{
                        if(this->raiz == actual)
                            this ->raiz = NULL;
                        else{
                            if(actual->padre->izq == actual)
                                actual->padre->izq = NULL;
                            else
                                actual->padre->der = NULL;
                        }
                    }
                }else{
                    if(hijo->izq == NULL){
                        this->remplazaActualPorHijo(actual,hijo);
                        hijo->izq = actual->izq;
                        if(hijo->izq != NULL)
                        	hijo->izq->padre = actual;
                        calculaAltura(hijo);
                        temp.padre = hijo;
                        t = &temp;
                    }else{
                        while(hijo-> izq != NULL){
                            hijo = hijo->izq;
                        }
                        temp.padre = hijo->padre;
                        t = &temp;
                        hijo->padre->izq = hijo->der;
                        if(hijo->der != NULL)
                            hijo->der->padre = hijo->padre;
                        this->remplazaActualPorHijo(actual,hijo);
                        hijo->der = actual->der;
                        hijo->izq = actual->izq;
                        if(hijo->der != NULL)
                            hijo->der->padre = hijo;
                        if(hijo->izq != NULL)
                            hijo->izq->padre = hijo;
                    }
                }
                if(t != NULL)
                    acomoda(t);
                delete actual;
                this->cont--;
            }
            return element;
        }
        void inserta(T element){
            NodoArbolBinario<T>* actual = this->raiz;
            NodoArbolBinario<T>* anterior = NULL;
            NodoArbolBinario<T>* nuevo = new NodoArbolBinario<T>;
            while(actual != NULL){
                anterior = actual;
                if(element < actual->element){
                    actual = actual->izq;
                }else{
                    actual = actual->der;
                }
            }
            nuevo->padre =  anterior;
            nuevo->element = element;
            if(actual == this->raiz){
                this->raiz = nuevo;
            }else{
                if(element < anterior->element){
                    anterior->izq = nuevo;
                }else{
                    anterior->der = nuevo;
                }
            }
            //lo de arriba lo pone en su posicion
            //lo de abajo checa si esta equil
            nuevo->altura = 0;
            acomoda(nuevo);
        }
};
