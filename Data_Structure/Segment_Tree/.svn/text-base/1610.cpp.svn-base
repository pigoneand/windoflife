#include <iostream>
using namespace std;

const int NOCOLOR=-1;
const int MULCOLOR=-2;

struct TNode
{
	//线段端点
	int l,r;
	//颜色
	int c;
	TNode *left,*right;
	
	void Construct(int start,int stop);
	void Insert(int start,int stop,int color);
	void Calculate();
	void Check();
}Tree[26000],*root=&Tree[0];

int len;

void TNode::Construct(int start,int stop)
{
	l=start;r=stop;

	if (start+1==stop)
	{ left=right=NULL;return;}

	int mid=(start+stop)>>1;

	left =&Tree[len++];
	right=&Tree[len++];
	left->Construct(start,mid);
	right->Construct(mid,stop);
}

void TNode::Insert(int start,int stop,int color)
{
	//如果当前线段颜色和要涂线段相同，那么直接return
	if (this->c==color) return;
	//如果插入线段就是当前线段，那么直接赋值
	if (this->l==start && this->r==stop) 
	{
		this->c=color;
		return;
	}

	//如果这条线段颜色单一,包括未涂色情况，先将左右儿子颜色保存
	if (c!=MULCOLOR)
	{
		left->c=right->c=c;
	}
	//当前线段为多重颜色
	this->c=MULCOLOR;

	int mid=((this->l+this->r)>>1);

	if (stop<=mid) {left->Insert(start,stop,color);return;}
	if (start>=mid) {right->Insert(start,stop,color);return;}

	left->Insert(start,mid,color);
	right->Insert(mid,stop,color);
}


int N;
int ss[9000],tt[9000],cc[9000];
int CC[9000];
int cal[9000];

void TNode::Calculate()
{
	int i;
	if (c!=MULCOLOR && c!=NOCOLOR) 
	{
		for (i=l;i<r;++i) CC[i]=c;
		return ;
	}
	if (c==MULCOLOR) 
	{
		left->Calculate();
		right->Calculate();
	}
}

int main()
{
	int i,j,k;

	while (cin>>N)
	{
		len=1;
		root->Construct(0,8000);	
		root->c=NOCOLOR;

		for (i=0;i<N;++i) 
		{
			scanf("%d%d%d",&ss[i],&tt[i],&cc[i]);
			root->Insert(ss[i],tt[i],cc[i]);
		}

		memset(cal,0,sizeof(cal));
		for (i=0;i<=8000;++i) CC[i]=-1;
		
		root->Calculate();

		k=-1;
		for (i=0;i<=8000;++i) 
		{
			if (CC[i]==k) continue;
			k=CC[i];
			if (k>=0) cal[k]++;
		}

		for (i=0;i<=8000;++i)
			if (cal[i]>0) printf("%d %d\n",i,cal[i]);
	
		printf("\n");
	}

	return 0;
}

