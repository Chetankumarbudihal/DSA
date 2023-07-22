 #include<stdio.h>
 #include<stdlib.h>

 struct NODE{
  int data;
  struct NODE *right;
  struct NODE *left;
  int height
  };
  typedef struct NODE *node;


  int getbalance(int x, int y)
  {
      return(x-y);
  }

  int maxof(int a, int b)
  {
      return (a>b?a:b);
  }


  int hgt(node x)
  {
      if (x==NULL)
        return 0;
      else
        return(x->height);
  }

  node newNode(int key)
  {
      node newn;
      newn=(node)malloc(sizeof(struct NODE));
      newn->data=key;
      newn->left=NULL;
      newn->right=NULL;
      newn->height=1;

      return newn;
  }


  node rightRotate(node x)
  {
      node y=x->left;
      node t2=y->right;

      y->right=x;
      x->left=t2;

      x->height= 1+maxof(hgt(x->left), hgt(x->right));
      y->height= 1+maxof(hgt(y->left), hgt(y->right));

      return y;

  }

  node leftRotate(node x)
  {
      node y=x->right;
      node t2=y->left;

      y->left=x;
      x->right=t2;

      x->height= 1+maxof(hgt(x->left), hgt(x->right));
      y->height= 1+maxof(hgt(y->left), hgt(y->right));

      return y;

  }


  node insertnode( node p,int key)
  {

      if(p==NULL)
       return( newNode(key));

       else if(key<p->data)
       {
           p->left=insertnode(p->left,key);
       }


       else if(key > p->data)
       {
           //printf("///%d///",key);
           p->right = insertnode(p->right,key);
       }


       p->height= 1+ maxof(hgt(p->left),hgt(p->right));

       int balance=getbalance(hgt(p->left),hgt(p->right));

       if(balance>1 && key<p->left->data )
       {
           //
           return rightRotate(p);
       }



       else if(balance<-1 && key>p->right->data)
       {

           return leftRotate(p);
       }



         else if(balance>1 && key>p->left->data)
         {
             //printf("//%d//",key);
             p->left=leftRotate(p->left);
             return rightRotate(p);
         }


         else if(balance<-1 && key<p->right->data)
         {
             //printf("//%d//",key);
             p->right=rightRotate(p->right);
             return leftRotate(p);
         }


       return p;

}

void printPreOrder(node root)
  {
      if(root!=NULL)
      {
         printf("%d->",root->data);
         printPreOrder(root->left);
         printPreOrder(root->right);
      }
}


int main()
{

      node  root=NULL;
      root=insertnode(root,5);
       root=insertnode(root,7);
        root=insertnode(root,4);
         root=insertnode(root,3);
          root=insertnode(root,9);
           root=insertnode(root,8);
            root=insertnode(root,2);

            printPreOrder(root);



}
