#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

void hepy(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) 
    {
        swap(arr[i], arr[largest]);

        hepy(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
        hepy(arr, n, i);

    for (int i = n - 1; i >= 0; i--) 
    {
        swap(arr[0], arr[i]);

        hepy(arr, i, 0);
    }
}

void buildmaxheap(int arr[], int n)
{
    for(int i=n/2 -1;i>=0;i--)
    {
       hepy(arr,n,i);
    }
}

int main()
{
    cout<<"Enter no of elements:";
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cout<<"Element";
        cin>>arr[i];
    }

    buildmaxheap(arr,n);

    cout<<"Array after max heap:";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";

    heapSort(arr,n);

    cout<<"Array after heapsort:";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
    getch();
    return 0;
}