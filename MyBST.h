#ifndef MYBST_H
#define MYBST_H
struct MyNodeBST{
    int data;
    MyNodeBST *left,
              *right;
    MyNodeBST(int data){
        this->data=data;
        this->left=this->right=nullptr;
    }
};

 
class MyBST{
    private:
        int size;
        MyNodeBST* root;
        bool search(int data, MyNodeBST* current);//listo
        void preorder(MyNodeBST* current);//listo
        void inorder(MyNodeBST* current);//listo
        void postorder(MyNodeBST* current);//listo
        void level(MyNodeBST* actual);//listo
        int height(MyNodeBST* actual);//listo
    public:
        MyBST();//listo
        ~MyBST();
        int length();//listo
        bool isEmpty();//lsito
        bool search(int data);//listo iterativo y recursivo
        bool insert(int data);//listo
        bool remove(int data);//listo
        void preorder();//listo
        void inorder();//listo
        void postorder();//listo
        void level();//listo
        void visit(int type);//listo
        int height();//listo
        void ancestors(int data);//listo
        int whatLevelAmI(int data);//listo
};
#endif