#include <bits/stdc++.h>
using namespace std;

// Method to assign memory to a block using the next fit memory allocation scheme
void NextFit(int b_size[], int m, int p_size[], int n)
{
   //code to store block id of a block to a process demanding memory
   int allocation[n], j = 0;

    // No process is assigned with memory at the initial phase

    memset(allocation, -1, sizeof(allocation));

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i = 0; i < n; i++) {

  // Condition to control memory search not from the beginning

        while (j < m) {


            if (b_size[j] >= p_size[i]) {

                // code to assign block j to p[i] process
                allocation[i] = j;

                // Reduce available memory in this block.
                b_size[j] -= p_size[i];

                break;

            }

           // mod m will help to traverse the free memory blocks from the first block when it reaches end

            j = (j + 1) % m;
        }
    }


    cout << "\nProcess Number\tProcess Size\tBlock Number \n";
    for (int i = 0; i < n; i++) {

        cout << " " << i + 1 << "\t\t" << p_size[i]
             << "\t\t";

        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else

            cout << "Not Allocated";

        cout<< endl;

    }
}

// Driver program
int main()
{
    int b_size[] = { 5, 10, 20 };
    int p_size[] = { 10, 20, 5 };
    int m = sizeof(b_size) / sizeof(b_size[0]);
    int n = sizeof(p_size) / sizeof(p_size[0]);


    NextFit(b_size, m, p_size, n);

    return 0;
}



/*


#include<bits/stdc++.h>
using namespace std;

int main()
{
  int nb,np,temp,lowest=9999;
  int a1[20],a2[20],b[20],p[20];
  cout<<"Enter number of blocks ";
  cin>>nb;
  cout<<"Enter number of processes ";
  cin>>np;

  cout<<"Enter size of each block"<<endl;
  for(int i=1;i<=nb;i++)
    {
        cout<<"Block "<<i<<"-";
        cin>>b[i];
    }

  cout<<"\nEnter size of each process."<<endl;
  for(int i=1;i<=np;i++)
    {
        cout<<"Process "<<i<<"-";
        cin>>p[i];
    }

  for(int t=1;t<=np;t++)
  {
    for(int q=1;q<=nb;q++)
    {
      if(a1[q]!=1)
      {
        temp=b[q]-p[t];
        if(temp>=0)
          if(lowest>temp)
          {
            a2[t]=q;
            lowest=temp;
          }
      }
    }
    a1[a2[t]]=1;
    lowest=10000;
  }

  cout<<endl<<"Process number\tProcess size\tBlock number\tBlock size";
  for(int i=1;(i<=np and a2[i]!=0);i++)
  {
    cout<<endl<<i<<"\t\t"<<p[i]<<"\t\t"<<a2[i]<<"\t\t"<<b[a2[i]];
  }
  return 0;
}
