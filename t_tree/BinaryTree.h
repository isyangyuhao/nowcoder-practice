#ifndef __BINARYTREE_H
#define __BINARYTREE_H
#include <stack>
#include <queue>
using namespace std;

//����������ṹ 
template<class ElemType>
struct BTNode
{
    ElemType         data;        //���ֵ
    BTNode<ElemType> *lchild;    //���ӽ��ָ��
    BTNode<ElemType> *rchild;    //�Һ��ӽ��ָ��
};

//����������    
template<class ElemType>
class BinaryTree
{
public:
    // ���캯�� 
    BinaryTree():m_root(NULL){} 
    
    //��������
    BinaryTree(const BinaryTree &rhs) 
    {
        m_root = _Copy (rhs.m_root);
    }

    //��ֵ���� 
    BinaryTree& operator=(const BinaryTree &rhs) 
    {
        if (&rhs == this)
            return *this;
            
        _Destroy (m_root);
        m_root = _Copy ( rhs.m_root);
        return *this;
    }

    //�������� 
    ~BinaryTree() 
    {
        _Destroy(m_root);
    }

    //�����������������ֵ�ķ�ʽ�����������Ľӿں���
    void Create1(ElemType ch[],const ElemType &endChar);
    
    //�Զ����������������������������Ľӿں���
    void Create2(ElemType ch1[],ElemType ch2[],int );
  
    //�ÿն�����
    void Clear() 
    { 
        _Destroy(m_root);
    }

    //�ж϶������Ƿ�Ϊ��
    bool IsEmpty() const 
    {
        return m_root == NULL;
    }

    //���ظ�����ָ��
    BTNode<ElemType>* Root() const 
    { 
        return m_root;
    }

    //���ض�����T��Ԫ��ֵΪe�Ľ���ָ��    
    BTNode<ElemType>* Locate(ElemType &e) 
    {
        return _Locate (m_root, e);
    }

    // ���������� 
    int Depth() 
    {
        return _Depth(m_root);
    }

	///////////////////////////��Ҷ�ӽ����////////////////////////////////////
	int CountLeaf()
	{
		return _CountLeaf(m_root);
	}
	///////////////////////////////////////////////////////////////////////////

    //������ָ��pָ��Ľ���˫�׽��,
    BTNode<ElemType>* Parent(BTNode<ElemType> *p) 
    {
        return _Parent(m_root, p);
    }

    //���ؽ������ӽ��    
    BTNode<ElemType>* LeftChild(BTNode<ElemType> *p) 
    {
        return p->lchild;
    }

    //���ؽ����Һ��ӽ��
    BTNode<ElemType>* RightChild(BTNode<ElemType> *p) 
    {
        return p->rchild;
    }
    //���ؽ������ֵܽ��
    BTNode<ElemType>* LeftSibling (BTNode<ElemType> *p);     
   
    //���ؽ������ֵܽ�� 
    BTNode<ElemType>* RightSibling (BTNode<ElemType> *p);       

   //����ݹ�����������Ľӿں���   
    void PreorderTraverse (void (*visit)(const ElemType &));   

    //����ǵݹ�����������Ľӿں���                                                                
    void PreorderTraverseNonRecursive (void (*visit)(const ElemType &));
 
    //����ݹ�����������Ľӿں���
    void InorderTraverse (void (*visit)(const ElemType &));       

    //����ǵݹ�����������Ľӿں�                                                       
    void InorderTraverseNonRecursive (void (*visit)(const ElemType &)); 

    //����ݹ�����������Ľӿں��� 
    void PostorderTraverse (void (*visit)(const ElemType &));    

    //����ǵݹ�����������Ľӿں���
    void PostorderTraverseNonRecursive (void (*visit)(const ElemType &));
                                                                    
   //�������������  
    void LevelTraverse (void (*visit)(const ElemType &e)); 

    //���������� 
    bool InsertChild(BTNode<ElemType> *p,const int &, BinaryTree<char> &);

    //������ɾ��
    void DeleteChild (BTNode<ElemType> *p, int which);          
	
   //����������е�Ҷ�ӽڵ����
   //int CountLeaf();



//	int CountLeaf(BTNode<ElemType> *p);


       
private:
    BTNode<ElemType> *m_root;                            //�����������ָ��

  


    BTNode<ElemType>* _Copy( BTNode<ElemType>* );    //���ƶ����� 
    
    //���������������ֵ�ķ�ʽ����������
    void _Create1(BTNode<ElemType>* &, ElemType ch[],const ElemType &,int &);
 
    //��֪�����������������������������򣬽���������T  
    void _Create2(BTNode<ElemType> * &,ElemType ch1[],ElemType ch2[],int ,int ,int &);   
                                                                                                       
    void _Destroy(BTNode<ElemType>* &);                //���ٶ����� 

    int _Depth(BTNode<ElemType>* );                    // ������������ 

	/////////////////////��Ҷ�ӽ�����ӿں���////////////////////////////////
	int _CountLeaf(BTNode<ElemType> *);
	/////////////////////////////////////////////////////////////////////////
  
     // ���ض�������Ԫ��ֵΪe�Ľ���ָ��    
     BTNode<ElemType>* _Locate(BTNode<ElemType>*, const ElemType &);

    //����e����˫�׽��ָ��
    BTNode<ElemType>* _Parent (BTNode<ElemType>*, BTNode<ElemType>*);
                                                    
    //����ݹ����������
    void _PreorderTraverse(BTNode<ElemType>* ,void (*visit)(const ElemType &e));

    //����ݹ����������
    void _InorderTraverse(BTNode<ElemType>* ,void (*visit)(const ElemType &e));

    //����ݹ����������
    void _PostorderTraverse(BTNode<ElemType>* ,void (*visit)(const ElemType &e));
	void _Exchange(BTNode<ElemType> *);

//	void_CountLeaf(BTNode<ElemType> *T, int &count);
    

};


//���������������ֵ�ķ�ʽ�����������Ľӿں���         
template<class ElemType>
void BinaryTree<ElemType>::Create1(ElemType ch[],const ElemType & c)        //ch[]��¼��ͨ�������������У�cΪָ�������ַ�
{
    int i = 0;
    _Create1(m_root, ch, c, i);   // i ��������������ch[]�е�λ��ָʾ������ֵΪ0
} 



//���������������ֵ�ķ�ʽ����������T                                
template<class ElemType>
void BinaryTree<ElemType>::_Create1(BTNode<ElemType> * &T,ElemType ch[],const ElemType &c,int &i)
{                 
     if (ch[i] == c)//cΪ�����������Ա�ʾ��ָ�� 
        T=NULL;
    else{
        T = new BTNode<ElemType>;
        T->data = ch[i];
        _Create1(T->lchild, ch, c, ++i);
        _Create1(T->rchild, ch, c, ++i);
    } 
}




//�Զ����������������������������Ľӿں���
template <class ElemType>
void BinaryTree<ElemType> ::Create2(ElemType ch1[],ElemType ch2[],int n) //n��¼�������еĽ����������������еĳ���
{    int i = 0;
   _Create2( m_root,ch1,ch2,0,n-1,i); //i��ֵΪ0
}



//��֪�����������������������������򣬽���������T                                
template<class ElemType>
void BinaryTree<ElemType> :: _Create2(BTNode<ElemType> * &T,ElemType ch1[],ElemType ch2[],int low,int high,int &k) 
 //��ֵ��,low=0, high=n-1����¼ch2[] �����е�λ���±ꡣk��ֵ��0,k��¼ch1[]�и�����λ���±꣬
{   
    int i;                                              
    if(low > high)              
        T=NULL;                                           
    else{                                                    
        T=new BTNode<ElemType>;                           
        T->data=ch1[k];                               //  ch1[]Ϊ�������У�ch2[]Ϊ�������У�k��¼ch1[]�и�����λ���±�
        for ( i = low;i <= high&&ch2[i] != ch1[k];i++) ;   //  i��¼ch2[]�еĸ�������ڵ�λ���±�
        if(ch2[i] == ch1[k]){ 
            k++;                                                                                      
            _Create2(T->lchild,ch1,ch2,low,i-1,k);     // k��¼��һ������������λ���±�
            _Create2(T->rchild,ch1,ch2,i+1,high,k);             // k��¼��һ������������λ���±�
        }  
    }                                                   
}




//���ض�����T�н������ֵܽ��ָ��     
template <class ElemType> 
BTNode<ElemType>* BinaryTree<ElemType>::LeftSibling (BTNode<ElemType> *p)
{
    BTNode<ElemType> *father;
    father = Parent(p);
    if (father && father->rchild == p )
        return father->lchild; 
    return NULL;
} 
 //���ض�����T�н������ֵܽ��ָ��     
template <class ElemType> 
BTNode<ElemType>* BinaryTree<ElemType>::RightSibling(BTNode<ElemType> *p)
{
    BTNode<ElemType> *father;
    father = Parent(p);
    if (father && father->lchild == p )
        return father->rchild; 
    return NULL;
}     

// ����ݹ�����������Ľӿں���    
template <class ElemType>
void BinaryTree <ElemType>::PreorderTraverse(void (*visit)(const ElemType &e))
{
    _PreorderTraverse(m_root, visit);
}

// ����ݹ�����������Ľӿں���        
template <class ElemType>
void BinaryTree <ElemType>::InorderTraverse(void (*visit)(const ElemType &e))
{
    _InorderTraverse(m_root,visit);
} 

//����ݹ�����������Ľӿں���              
template <class ElemType>
void BinaryTree <ElemType>::PostorderTraverse(void (*visit)(const ElemType &e))
{
    _PostorderTraverse(m_root,visit);
}
    
//whichΪ0ɾ����������p������������whichΪ1ɾ����������p������������
template <class ElemType> 
void BinaryTree<ElemType>::DeleteChild(BTNode<ElemType> *p, int which)
{ 
    if (which == 0)
        _Destroy(p->lchild); 
    else 
        _Destroy(p->rchild);
}    
//����һ������ 
template <class ElemType>
BTNode<ElemType>* BinaryTree<ElemType>::_Copy( BTNode<ElemType>* T)
{  
    if (T == NULL)    
        return NULL;
        
    BTNode<ElemType> *p; 
    p = new BTNode<ElemType>;
    p->data = T->data;
    p->lchild = _Copy(T->lchild);
    p->rchild = _Copy(T->rchild);
    return p;  
}


//���ٶ���������ʽ�Ķ�����T 
template <class ElemType>
void BinaryTree<ElemType>::_Destroy(BTNode<ElemType>* &T)
{
    if (T){
        _Destroy (T->lchild);
        _Destroy (T->rchild);
        delete T;
    }
    T = NULL;  
} 

//���ض�����T��Ԫ��ֵΪe�Ľ���ָ��    
template <class ElemType>
BTNode<ElemType>* BinaryTree<ElemType>::_Locate(BTNode<ElemType>* bt,const ElemType &e)
{
    if(!bt || bt->data == e)
        return bt;
        
    BTNode<ElemType> *q;
    q = _Locate(bt->lchild, e);
    if (q) 
        return q;
    q = _Locate(bt->rchild, e);
    return q;
}
//���ض�����T��Ԫ��ֵΪe�Ľ���˫�׽��ָ��     
template <class ElemType>
BTNode<ElemType>* BinaryTree<ElemType>::_Parent(BTNode<ElemType>* T, BTNode<ElemType>* p)
{
    if (T == NULL || T == p)
        return NULL;
        
    if (T->lchild == p || T->rchild==p) 
        return T;
            
    BTNode<ElemType> *q;
    q = _Parent(T->lchild, p);
    if (q) 
        return q;
    q = _Parent(T->rchild,p);
    return q;
}

//������������     
template <class ElemType> 
int BinaryTree<ElemType>::_Depth(BTNode<ElemType>* T)
{
    if (!T)
        return 0;

    int h1,h2;
    h1 = _Depth(T->lchild);
    h2 = _Depth(T->rchild);

    return h1 > h2 ? h1 + 1 : h2 + 1;
} 

/////////////////////////////��Ҷ�ӽ�����ӿں���///////////////////////////////
template <class ElemType>
int _CountLeaf(BTNode<ElemType> *T) {
	int count;
	if(T) {
		if((!T->lchild) && (!T->rchild)) {
			count++;
		}
		_CountLeaf(T->lchild);
		_CountLeaf(T->rchild);
	}
	return count;
}
///////////////////////////////////////////////////////////////////////////

//����ݹ����������         
template <class ElemType>
void BinaryTree<ElemType> ::_PreorderTraverse(BTNode<ElemType>* T,void (*visit)(const ElemType &e))
{  
    if (T){
        visit(T->data);
        _PreorderTraverse(T->lchild,visit);
        _PreorderTraverse(T->rchild,visit);
    }  
} 
//����ݹ����������     
template <class ElemType>
void BinaryTree<ElemType> ::_InorderTraverse(BTNode<ElemType>* T,void (*visit)(const ElemType &e))
{  
    if (T) {
        _InorderTraverse (T->lchild,visit);
        visit(T->data);
        _InorderTraverse (T->rchild,visit);
    }  
}
//����ݹ����������             
template <class ElemType>
void BinaryTree<ElemType> ::_PostorderTraverse(BTNode<ElemType>* T,void (*visit)(const ElemType &e))
{  
    if (T){
        _PostorderTraverse (T->lchild,visit);
        _PostorderTraverse (T->rchild,visit);
        visit (T->data);
    }  
}
// ��������������ķǵݹ��㷨(����ջ)   
template <class ElemType>
void BinaryTree<ElemType> ::InorderTraverseNonRecursive(void (*visit)(const ElemType &e))
{ 
    stack<BTNode<ElemType> *> S;
    S.push (m_root); //��ָ���ջ
    
    while (!S.empty ()) {
        BTNode<ElemType> *p;
        p = S.top ();

        while (p) {
            p = p->lchild;
            S.push(p); // �����ߵ���ͷ
        }
        
        S.pop(); // ��ָ����ջ
        
        if (!S.empty()){ // ���ʽ��,����һ��
            p = S.top ();
            S.pop();
            visit(p->data);
            S.push(p->rchild);
        }
    }
} 
// ��α����������ķǵݹ��㷨(���ö���)   
template <class ElemType>
void BinaryTree<ElemType> ::LevelTraverse(void (*visit)(const ElemType &e)){
    queue<BTNode<ElemType> *> Q;
    
    if (m_root)
        Q.push (m_root);
        
    while (!Q.empty ()){
        BTNode<ElemType> *p;
        p = Q.front ();
        Q.pop ();

        visit (p->data);
        if (p->lchild)
            Q.push (p->lchild);
        if (p->rchild)
            Q.push (p->rchild);
    }
}
// ��ʼ����: ������m_root����,e��m_root��ĳ�����,LRΪ0��1,�Ը��ƶ���ķ�ʽ��õķǿն�����s��m_root���ཻ��������Ϊ��
// �������: ����LRΪ0��1,����sΪT��e���������������e����ԭ��������������Ϊs��������           
template <class ElemType> 
bool BinaryTree<ElemType>::InsertChild(BTNode<ElemType> *p,const int &LR, BinaryTree<char> &r)
{
    BTNode<ElemType>*q,*s;
    if(p){ 
        q = r.Root(); //ȡ��������ָ�� 
        s = _Copy(q);//������
        if (LR == 0){
            s->rchild = p->lchild;
            p->lchild = s;
        }else{
            s->rchild = p->rchild;
            p->rchild = s;
        }
        return true;
    }
    return false;
} 


//���������Ҷ�ӽ����
/* template <class ElemType>
void BinaryTree<ElemType>::_CountLeaf(BTNode<ElemType> *T, int &count) {
	if(T) {
		if((!T->lchild) && (!T->rchild)) {
			++count;
			CoundLeaf(T->lchild, count);
			CoundLeaf(T->rchild, count);
		}
	}
}


template <class ElemType>
int BinaryTree<ElemType>::CountLeaf(BTNode<ElemType> *p) {
	int count;
	_CountLeaf(BTNode T, int &count);
	return count;
}
*/


#endif



   
