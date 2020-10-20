// Cpp con lo necesario para usar un arbol de busqueda binaria, con metodos como insert, remove, search, inOrder, etc.
// Fecha: 17/10/2020
#include "MyBST.h"
#include <iostream>
#include <vector>
using namespace std;

/*
    Descripcion: Constructor que inicia todos los valores en 0 y nullptr para la raiz del arbol
    Input: N/a.
    Output: No regresa nada, pero el objeto termina construido/instanciado.
    Complejidad: O(1)
*/
MyBST::MyBST(){
    this->size = 0;
    this->root = nullptr;
}

/*
    Descripcion: Destructor que libera la memoria de cada nodo del arbol
    Input: N/a.
    Output: No regresa nada, pero la memoria es liberada y el objeto destruido
    Complejidad: O(n) Como siempre se remueve la raiz, el remove se vuelve O(1) dando siempre O(n) para el destructor
*/
MyBST::~MyBST(){
    while(! isEmpty()){
        remove(this->root->data);
    }
    cout<<"Arbol Destruido"<<endl;
}

/*
    Descripcion: Consulta el numero de elementos en el arbol
    Input: N/a.
    Output: Int con el numero de elementos en el arbol
    Complejidad: O(1)
*/
int MyBST::length(){
    return this->size;
}

/*
    Descripcion: Consulta si la lista esta vacia o no
    Input: N/a.
    Output: Bool con true si la lista esta vacia, o false si tiene al menos un elemento
    Complejidad: O(1)
*/
bool MyBST::isEmpty(){
    return this->size == 0;
}

/*
    Descripcion: Busca de forma recursiva un dato en el arbol
    Input: data -> entero con el numero a buscar; current -> apuntador de tipo MyNodeBST con el nodo actual
    Output: Bool con true si el numero esta en la lista, o false si no lo encontro
    Complejidad: Mejor caso O(1), caso promedio  y peor O(n)
*/
bool MyBST::search(int data, MyNodeBST* current){
    if(!current){
        return false;
    }else if(current->data == data){
        return true;
    }else if(current->data < data){
        return search(data, current->right);
    }else{
        return search(data, current->left);
    }
}

/*
    Descripcion: Metodo publico de busqueda para pasar los parametros iniciales
    Input: data -> entero con el numero a buscar
    Output: Bool con true si el numero esta en la lista, o false si no lo encontro
    Complejidad: Mejor caso O(1), caso promedio  y peor O(n)
*/
bool MyBST::search(int data){
    MyNodeBST* actual = this->root;
    return search(data, actual);
}

/*
    Descripcion: Busca de forma iterativa un dato en el arbol
    Input: data -> entero con el numero a buscar
    Output: Bool con true si el numero esta en la lista, o false si no lo encontro
    Complejidad: Mejor caso O(1), caso promedio  y peor O(n)
*/
/*
bool MyBST::search(int dato){
    MyNodeBST *actual = this->root;
    while (actual){
        if(dato == actual->data){
            return true;
        }else if(dato < actual->data){
            actual = actual->left;
        }else{
            actual = actual->right;
        }
    }
    return false;
}
*/

/*
    Descripcion: Inserta un nuevo elemento en el arbol
    Input: data -> entero con el numero a insertar
    Output: Bool con true si se pudo insertar, o false si ya habia ese elemento en la lista
    Complejidad: Mejor caso O(1), caso promedio  y peor O(n)
*/
bool MyBST::insert(int data){
    if(this->size == 0){
        this->root = new MyNodeBST(data);
        this->size++;
        return true;
    }else{
        MyNodeBST *actual = this->root,
                  *prev = nullptr;
        while(actual){
            prev = actual;
            if(data == actual->data){
                return false;
            }else{
                actual = data < actual->data ? actual->left : actual->right;
            }
        }
        if(prev->data>data){
            prev->left = new MyNodeBST(data);
        }else{
            prev->right = new MyNodeBST(data);
        }
        this->size++;
        return true;
    }
}

/*
    Descripcion: Borra un elemento del arbol
    Input: data -> entero con el numero a borrar
    Output: Bool con true si el numero esta en la lista y lo borro, o false si no lo encontro, por lo tanto no lo borro
    Complejidad: Mejor caso O(1), caso promedio O(n) y peor O(n^2)
*/
bool MyBST:: remove(int data){
    MyNodeBST *actual = this->root,
              *prev = nullptr;
    while(actual){
        if(actual->data ==  data){
            if(actual->right){
                MyNodeBST *MenorDeMayores = actual->right,
                          *padre = actual;

                while(MenorDeMayores->left){
                    padre = MenorDeMayores;
                    MenorDeMayores = MenorDeMayores->left;
                }
                if(padre->left){
                    padre->left = MenorDeMayores->right;
                    MenorDeMayores->right = nullptr;
                    actual->data = MenorDeMayores->data;
                }else{
                    padre->data = MenorDeMayores->data;
                    padre->right = MenorDeMayores->right;
                    MenorDeMayores->right = nullptr;
                }

                delete MenorDeMayores;
                this->size--;
                return true;
            }else if(actual->left){
                prev->left = actual->left;
                actual->left = nullptr;
            }else{
                if(prev){
                    if(prev->data>data){
                        prev->left=nullptr;
                    }else{
                        prev->right=nullptr;
                    }
                }else{
                    this->root = nullptr;
                }
            }
            delete actual;
            this->size--;
            return true;
        }else{
            prev = actual;
            actual = actual->data > data ? actual->left : actual->right;
        }
    }
    return false;
}

/*
    Descripcion: Recorre e imprime cada elemento del arbol en pre-orden de forma recursiva
    Input: current -> apuntador de tipo MyNodeBST con el nodo actual
    Output:No regresa nada, pero imprime el arbol en pre-orden
    Complejidad: O(n)
*/
void MyBST::preorder(MyNodeBST* current){
    if(current){
        cout<<current->data << " ";
        preorder(current->left);
        preorder(current->right);
    }
}

/*
    Descripcion: metodo publico que llama a preorden pasando el inicio como la raiz del arbol
    Input: n/a
    Output:No regresa nada, pero imprime el arbol en pre-orden
    Complejidad: O(n)
*/
void MyBST:: preorder(){
    preorder(this->root);
    cout<<endl;
}

/*
    Descripcion: Recorre e imprime cada elemento del arbol en orden de forma recursiva
    Input: current -> apuntador de tipo MyNodeBST con el nodo actual
    Output:No regresa nada, pero imprime el arbol en orden
    Complejidad: O(n)
*/
void MyBST::inorder(MyNodeBST* current){
    if(current){
        inorder(current->left);
        cout<<current->data << " ";
        inorder(current->right);
    }
}

/*
    Descripcion: metodo publico que llama a inorden pasando el inicio como la raiz del arbol
    Input: n/a
    Output:No regresa nada, pero imprime el arbol en orden
    Complejidad: O(n)
*/
void MyBST::inorder(){
    inorder(this->root);
    cout<<endl;
}

/*
    Descripcion: Recorre e imprime cada elemento del arbol en post-orden de forma recursiva
    Input: current -> apuntador de tipo MyNodeBST con el nodo actual
    Output:No regresa nada, pero imprime el arbol en post-orden
    Complejidad: O(n)
*/
void MyBST::postorder(MyNodeBST *current){
    if(current){
        postorder(current->left);
        postorder(current->right);
        cout<<current->data << " ";
    }
}

/*
    Descripcion: metodo publico que llama a postorden pasando el inicio como la raiz del arbol
    Input: n/a
    Output:No regresa nada, pero imprime el arbol en post-orden
    Complejidad: O(n)
*/
void MyBST::postorder(){
    postorder(this->root);
    cout<<endl;
}

/*
    Descripcion: Recorre e imprime cada elemento del arbol por nivel
    Input: current -> apuntador de tipo MyNodeBST con el nodo actual
    Output:No regresa nada, pero imprime el arbol por nivel
    Complejidad: O(n)
*/
void MyBST::level(MyNodeBST* actual){
    if(actual){
        cout<<actual->data<<" ";
        level(actual->left);
        level(actual->right);
    }
}

/*
    Descripcion: metodo publico que llama a level pasando el inicio como la raiz del arbol
    Input: n/a
    Output:No regresa nada, pero imprime el arbol por nivel
    Complejidad: O(n)
*/
void MyBST::level(){
    level(this->root);
    cout<<endl;
}

/*
    Descripcion: Recorre el arbol para contar su altura de forma recusiva
    Input: actual -> apuntador de tipo MyNodeBST con el nodo actual
    Output: Int con la altura del arbol
    Complejidad: O(n)
*/
int MyBST::height(MyNodeBST* actual){
    if(actual){
        int left = height(actual->left);
        int right = height(actual->right);
        if(left<right){
            return right+1;
        }else{
            return left+1;
        }
    }
    return 0;
}

/*
    Descripcion: metodo publico que llama a height pasando el inicio como la raiz del arbol
    Input: n/a
    Output: Int con la altura del arbol
    Complejidad: O(n)
*/
int MyBST::height(){
    return height(this->root);
}

/*
    Descripcion: Consulta en que nivel se encuentra cierto dato
    Input: data -> entero con el numero a buscar
    Output: Int del nivel en el que se encuentra el dato dado, regresa -1 si no se encuentra el dato
    Complejidad: Mejor caso O(1), caso promedio  y peor O(n)
*/
int MyBST::whatLevelAmI(int data){
    MyNodeBST *actual = this->root;
    int level = 0;
    while(actual){
        level++;
        if (actual->data == data){
            return level;
        }else{
            actual = actual->data > data ? actual->left : actual->right;
        }
    }
    return -1;
}

/*
    Descripcion: Consulta los ancestros o padres de cierto numero
    Input: data -> entero con el numero a buscar
    Output: No regresa nada, pero si se encuentra el valor imprime los ancestros desde la raiz  hacia abao
    Complejidad: Mejor caso O(1), caso promedio  y peor O(n)
*/
void MyBST::ancestors(int data){
    MyNodeBST *actual = this->root;
    vector<int> ancestro;
    while(actual){
        ancestro.push_back(actual->data);
        if(data == actual->data){
            for(int i=0;i<ancestro.size()-1;i++){
                cout<<ancestro[i]<<" ";
            }
            cout<<endl;
            return;
        }else{
            actual = actual->data > data ? actual->left : actual->right;
        }
    }
    cout<<endl;
}

/*
    Descripcion: Consulta de que forma se quiere imprimir o visitar al arbol
    Input: type -> entero con el tipo de impresion a hacer Type: 1->preorder, 2->inorder, 3->postorder, 4->level
    Output: No regresa nada, pero imprime los elemetos del arbol segun el parametro
    Complejidad: Siempre es O(n)
*/
void MyBST::visit(int type){
    switch (type){
    case 1:
        preorder();
        break;
    case 2:
        inorder();
        break;
    case 3:
        postorder();
        break;
    case 4:
        level();
        break;
    }
}

int main(){
    MyBST arbol;
    int aux=1;
    ///arbol.insert(6);
    for(int i=0; i<15;i++){
        arbol.insert(aux);
        cout<<aux<<" ";
        aux=aux*5%21;
    }
    cout<<endl;

    arbol.visit(1);
    arbol.visit(2);
    arbol.visit(3);
    arbol.visit(4);
    cout<<"HEIGHT: "<<arbol.height()<<'\n';
    arbol.ancestors(16);
    cout<<"WHATLEVEL: "<<arbol.whatLevelAmI(20)<<'\n'<<"\tEliminando el 1:\n";
    arbol.remove(1);
    arbol.visit(1);
    cout<<"HEIGHT: "<<arbol.height()<<endl<<"\tEliminando el 4:\n";
    arbol.remove(4);
    arbol.visit(1);
    cout<<"HEIGHT: "<<arbol.height()<<endl;
    cout<<"lenght: "<<arbol.length()<<endl;
    cout<<"empty: "<<arbol.isEmpty()<<endl;
    cout<<"Search 4: "<<arbol.search(4)<<endl;
    cout<<"Search 16: "<<arbol.search(16)<<endl;
}