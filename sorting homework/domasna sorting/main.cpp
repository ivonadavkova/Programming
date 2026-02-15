#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <random>
using namespace std;
using namespace std::chrono;

int container=0;

//merge

void mergeArrs(vector<int> &a, int l, int m, int r){
    int n1=m-l+1;
    int n2=r-m;
    int lc=0;
    int ac=0;
    int rc=0;

    vector<int> levo(n1), desno(n2);

    for(int i=0; i<n1; i++){
        levo[i]=a[l+i];
    }
    for(int j=0; j<n2; j++){
        desno[j]=a[(m+1)+j];
    }

    while(lc<n1 && rc<n2){

        if(levo[lc]<=desno[rc]){
            a[ac]=levo[lc];
            lc++;
        }else{
            a[ac]=desno[rc];
            rc++;
        }

        ac++;
    }
     while(lc<n1){
        a[ac]=levo[lc];
        ac++;
        lc++;
    }

    while(rc<n2){
        a[ac]=desno[rc];
        ac++;
        rc++;
    }
    }
void mergeSort(vector<int> &a, int l, int r){
   if(l<r){
     int mid=(l+r)/2;
     mergeSort(a,l,mid);
     mergeSort(a,mid+1,r);
     mergeArrs(a,l,mid,r);

   }else return;

}

//insertion
void insertionSort(vector<int> &arr, int n){
    int momentalenelement=0;

    for(int i=1; i<n; i++){
        momentalenelement=i;
        container=arr[momentalenelement];
        for(int j=momentalenelement-1; j>=0; j--){
            if(arr[j]>arr[momentalenelement]){
               arr[momentalenelement]=arr[j];
               arr[j]=container;
               momentalenelement=j;
            }
        }
    }
}

//selection
void selectionSort(vector<int> &arr, int n){
    int najmalavrednost=0;

    for(int i=0; i<n-1; i++){
        najmalavrednost=i;
        for(int j=i+1; j<n; j++) if(arr[najmalavrednost]>arr[j]) najmalavrednost=j;
        if(najmalavrednost!=i){
            container=arr[i];
            arr[i]=arr[najmalavrednost];
            arr[najmalavrednost]=container;
        }
    }
}

//quick
int partitionI(vector<int> &a, int f, int l){
    int p=a[l];
    int i=f;
    int temp=0;
    for(int j=f; j<=l-1; j++){
        if(a[j]<=p){
            temp=a[j];
            a[j]=a[i];
            a[i]=temp;
            i++;
        }
    }

    temp=a[i];
    a[i]=a[l];
    a[l]=temp;

 return i;
 }
void quicksort(vector<int> &a, int f, int l){
    if(f<l){
        int p=partitionI(a,f,l);
        quicksort(a,f,p-1);
        quicksort(a,p+1,l);
    }
}

int main()
{
     vector<int> a, b;
    for(int i=0; i<100000; i++) a.push_back(rand()%10000001);
    int N=a.size();
    b=a;
    auto x1=steady_clock::now();
    selectionSort(b, N);
    auto y1=steady_clock::now();
    b=a;
    auto x2=steady_clock::now();
    insertionSort(b, N);
    auto y2=steady_clock::now();
    b=a;
    auto x3=steady_clock::now();
    mergeSort(b, 0, N-1);
     auto y3=steady_clock::now();
    b=a;
    auto x4=steady_clock::now();
    quicksort(b, 0, N-1);
    auto y4=steady_clock::now();

    duration<double> t1=y1-x1;
    duration<double> t2=y2-x2;
    duration<double> t3=y3-x3;
    duration<double> t4=y4-x4;

    cout << "selection sort: " << t1.count() << "s" << endl;
    cout << "insertion sort: " << t2.count() << "s" << endl;
    cout << "merge sort: " << t3.count() << "s" << endl;
    cout << "quick sort: " << t4.count() << "s" << endl;

    return 0;
}

