#include <iostream>
using namespace std;

struct TNode
{
	int l,r;
	int minstep;
	TNode *leftchild,*rightchild;
	
	void Construct(int left,int right);
	void Insert(int,int);
	int Getminstep(int,int);
} tree[200000], *root=&tree[0];

int len;

void TNode::Construct(int left,int right)
{
	l=left;r=right;minstep=999999;
	if (left==right) { leftchild=rightchild=NULL;return;}
	int mid=(left+right)>>1;
	leftchild=&tree[len++];
	rightchild=&tree[len++];
	leftchild->Construct(left,mid);
	rightchild->Construct(mid+1,right);
}

void TNode::Insert(int posi,int rank)
{
	if (rank<minstep) minstep=rank;
	if (l==r)
	{
		return;
	}

	int mid=(l+r)>>1;
	if (posi<=mid) leftchild->Insert(posi,rank); else rightchild->Insert(posi,rank);
}

int TNode::Getminstep(int left,int right)
{
	if (l==left && r==right) return minstep;
	int mid=(l+r)>>1;
	if (right<=mid) return leftchild->Getminstep(left,right);
	if (left>mid) return rightchild->Getminstep(left,right);

	int ret1=leftchild->Getminstep(left,mid);
	int ret2=rightchild->Getminstep(mid+1,right);
	return ret1<ret2 ? ret1 : ret2;
}

int N,M;

void deal()
{
	int i,j,k,p;
	
	len=1;
	root->Construct(1,N);
	root->Insert(1,0);

	for (k=1;k<=M;++k)
	{
		scanf("%d%d",&i,&j);
		if (i<j) 
		{
			p=root->Getminstep(i,j-1);
			root->Insert(j,p+1);
		}
	}

	printf("%d\n",root->Getminstep(N,N));
}
int main()
{
	while (cin>>N>>M) deal();

	return 0;
}