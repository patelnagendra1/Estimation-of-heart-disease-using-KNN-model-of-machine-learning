#include<stdio.h>
#include<stdlib.h>
 struct node
          {
            int data;
            struct node *parent,*left,*right;
            int balance;
          };
 struct node *root=NULL;
 
       struct node *newnode(int item)
                 {
                   struct node *temp;
                   temp=(struct node*)malloc(sizeof(struct node));
                    temp->data=item;
                    temp->left=temp->right=NULL;
                    
                    return temp;
                 }
     struct node* insert(struct node *node,int key)
                   {
                     if(node==NULL)
                       {
                         return newnode(key);
                       }
                     if(key < node->data)
                       {
                         node->left=insert(node->left,key);
                         node->left->parent=node;
                       }
                     else if(key>node->data)
                       {
                         node->right=insert(node->right,key);
                         node->right->parent=node;
                       }
                     
                     return node;
                   }
                   
                   
                   
 void printPreorder(struct node* node) 
	{ 
    if (node == NULL) 
        return; 
  
    /* first print data of node */
    printf("%d ",node->data); 
  
    /* then recur on left sutree */
    printPreorder(node->left);  
  
    /* now recur on right subtree */
    printPreorder(node->right);                  
                   
	 }                  


  
  int hight(struct node* node)  
		{  
			if (node == NULL)  
				return 0;  
			else
			{  
				/* compute the depth of each subtree */
				int lDepth = hight(node->left);  
				int rDepth = hight(node->right);  
			  
				/* use the larger one */
				if (lDepth > rDepth)  
					return(lDepth + 1);  
				else return(rDepth + 1);  
			}  
		}


 void LL_rotation(struct node *a,struct node *b,struct node *c)
     		{
     			//printf("%d %d %d\n",c->data,b->data,a->data);
     			
     			if(b->left!=NULL)
     			{
     			c->right=b->left;
     			c->right->parent=c;
     			}
     			else
     			c->right=NULL;
     			
     			if(c==root)
     			{
     				root=b;
     				b->parent=NULL;
     				b->left=c;
     				c->parent=b;
     			}
     			else
     			{
     				if(c->parent->right==c)
     				{
     					b->parent=c->parent;
     					c->parent->right=b;
     					c->parent=b;
     					b->left=c;
     				}
     			}
     	}

 void RR_rotation(struct node *a,struct node *b,struct node *c)
     		{
     			
     			
     			if(b->right!=NULL)
     			{
     			c->left=b->left;
     			c->left->parent=c;
     			}
     			else
     			c->left=NULL;
     			
     			if(c==root)
     			{
     				root=b;
     				b->parent=NULL;
     				b->right=c;
     				c->parent=b;
     			}
     			else
     			{
     				if(c->parent->left==c)
     				{
     					b->parent=c->parent;
     					c->parent->left=b;
     					c->parent=b;
     					b->right=c;
     				}
     			}
     	}

	void LR_rotation(struct node *a,struct node *b,struct node *c)
		{
			a->parent=b->parent;
			c->left=a;
			a->left=b;
			b->parent=a;
			b=a;
			a=b->left;
			a->right=NULL;
			
			RR_rotation(a,b,c);
		}
	void RL_rotation(struct node *a,struct node *b,struct node *c)	
	{	
			a->parent=b->parent;
			c->right=a;
			a->right=b;
			b->parent=a;
			b=a;
			a=b->right;
			a->left=NULL;
			
			LL_rotation(a,b,c);
	}
                   
 void type_of_imbalance(struct node *p,int value,int x)//p is node which is imbalace and x is imbalance factor
   			{
   				struct node *a,*b,*c;
   				c=p;
   				
   				if(x>0)
   				{
   					//Either LL imbalance or LR imbalance
   					b=c->left;
   					if(b->data < value)//LR imbalance
   					{
   						printf("LR imbalance\n");
   					    a=b->right;
   					    LR_rotation(a,b,c);
   					    
   					}
   					else // LL imbalance
   					{
   					a=b->left;
   					printf("LL imbalance\n");
   					RR_rotation(a,b,c);
   					}
   				}
   				else
   				{
   					b=c->right;
   					if(b->data < value) //RR imbalance
   					{
   						a=b->right;
   						
   						printf("RR imbalance\n");
   						printf("hj\n");
   						LL_rotation(a,b,c);
   					}
   					else // RL imbalance
   					{
   						a=b->left;
   						printf("RL imbalance\n");
   						RL_rotation(a,b,c);
   					}
   				}
   				
   				
   		}
    
                 

void  inorder_to_find_imbalance(int value)
     	          {
     	          
                    struct node *p=root;
                     while(p->data!=value)
                     {
                     	if(p->data<value)
                     	p=p->right;
                     	else
                     	p=p->left;
                     
                   	}
                   	
                  while(1)
                  {
                  	if(p->parent!=NULL)
                  	{
                  	p=p->parent;
                  	int x=0,y=0;
                  	 
                  	if(p->left!=NULL)
					{
						x=hight(p->left);
					}
					if(p->right!=NULL)
					{
						y=hight(p->right);
					}
					x=x-y;
						
                  	
                   	if(x<-1 || x>1)
                   	{
                   	type_of_imbalance(p,value,x);
                   	break;
                   	}
                  }
                  else
                  break;
                 }
                } 	
					
                 
 int main()
             { 
               int n,x,i;
               struct node *p,*q;
               printf("enter the no of nodes\n");
               scanf("%d",&n);
                printf("enter the node ");
                  scanf("%d",&x);
                root=insert(root,x);
               for(i=1;i<n;i++)
                 {
                   printf("enter the node ");
                   scanf("%d",&x);
                   insert(root,x);
                   
                  inorder_to_find_imbalance(x);
                   
                 } 
                 printPreorder(root);   
             }
