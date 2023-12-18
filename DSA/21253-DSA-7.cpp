#include<iostream>
#include<conio.h>
using namespace std;

class tree
{
	int** a,l,u,w,i,j,v,e,visited[20],parent[20];
    public:
	void input();
	void display();
	void prims();
	void kruskals();
	int find(int);
	void unionSet(int, int);
};

void tree::input()
{
	cout<<"Enter the no. of vertices : ";
	cin>>v;

	a = new int*[v];
	for(i = 0; i < v; i++)
	{
		visited[i] = 0;
		parent[i] = i;
		a[i] = new int[v];
		for(j = 0; j < v; j++)
		{
			a[i][j] = 999;
		}
	}

	cout<<"Enter the no. of edges    : ";
	cin>>e;
	cout<<endl;

	for(i = 0; i < e; i++)
	{
		cout<<endl;
		cout<<"Enter the branches :  ";
		cin>>l>>u;
		cout<<"Enter the weight   :  ";
		cin>>w;
		cout<<endl;
		a[l-1][u-1] = a[u-1][l-1] = w;
	}
}

void tree::display()
{
	cout<<"Adjacency matrix:"<<endl;
	for(i=0;i<v;i++)
	{
		for(j=0;j<v;j++)
		{
			cout<<a[i][j]<<"    ";
		}
		cout<<endl;
	}
}

void tree::prims()
{
	int p=0,q=0,total=0,min;
	visited[0]=1;
	for(int count=0;count<(v-1);count++)
	{
		min=999;
		for(i=0;i<v;i++)
		{visited[0]=1;
			if(visited[i]==1)
			{
				for(j=0;j<v;j++)
				{
					if(visited[j]!=1)
					{
						if(min > a[i][j])
						{
							min=a[i][j];
							p=i;
							q=j;
						}
					}
				}
			}
		}
		visited[p]=1;
		visited[q]=1;
		total=total+min; 
		cout<<"Edge : "<<(p+1)<<" -> "<<(q+1)<<"  weight : "<<min<< endl;
		visited[0]=1;
	}
	cout<<"The minimum total cost is: "<<total<<endl;
}

void tree::kruskals()
{
	int p, q, total = 0, count = 0, min;
	int selectedEdges = 0;

	while (count < v - 1)
	{
		min = 999;
		p = -1;
		q = -1;

		for (i = 0; i < v; i++)
		{
			for (j = 0; j < v; j++)
			{
				if (find(i) != find(j) && a[i][j] < min)
				{
					min = a[i][j];
					p = i;
					q = j;
				}
			}
		}

		if (p != -1 && q != -1)
		{
			unionSet(p, q);
			cout << "Edge : " << p+1 << " -> " << q+1 << "  weight : " << min << endl;
			total += min;
			count++;
		}
	}

	cout << "The minimum total cost is: " << total << endl;
}

int tree::find(int i)
{
	if (parent[i] == i)
		return i;
	
	return find(parent[i]);
}

void tree::unionSet(int i, int j)
{
	int a = find(i);
	int b = find(j);
	parent[a] = b;
}
int main()
{
	int ch;
	tree t;
	do
	{
        cout<<endl;
		cout<<"1. Enter Graph"<<endl;
        cout<<"2. Adjacency Matrix"<<endl;
        cout<<"3. Prims Algo"<<endl;
		cout<<"4. Kruskals Algo"<<endl;
		cout<<"5. Exit"<<endl;
        cout<<endl;
		cout<<"Enter your choice :";
		cin>>ch;
        cout<<endl;
	
        switch(ch)
        {	
            case 1: 
            t.input();
            break;

            case 2:
            t.display();
            break;

            case 3: 
            cout<<"Prims Algo"<<endl;
            t.prims();
            break;

			case 4:
			cout<<"Kruskals Algo"<<endl;
			t.kruskals();
			break;

			case 5:
			cout<<"Exitting the Code"<<endl;
			break;

            default: 
            cout<<"Invalid choice"<<endl;
            break;
        }
	
	}while(ch!=4);
	getch();
	return 0;
}