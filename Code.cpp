#include <iostream>
#include <chrono>
#include <fstream>
#include<algorithm>
#include<vector>
#include<random>
using namespace std;
using namespace std::chrono;


void count_sort(int v[], int n, int max1)
{

    int* output, * aparitii;
    output = new int[n+1];
    aparitii = new int[max1 + 1];

    for (int i = 0; i <= max1; i++)
        aparitii[i] = 0;

    for (int i = 1; i <= n; i++)
        aparitii[v[i]]++;

    for (int i = 1; i <= max1; i++)
        aparitii[i] = aparitii[i - 1] + aparitii[i];

    for (int i = n; i >= 1; i--)
    {
        output[aparitii[v[i]]] = v[i];
        aparitii[v[i]]--;
    }
    for (int i = 1; i <= n; i++)
        v[i] = output[i];

}

void merge_sort(int v[], int st, int dr,int output[])
{
    int  m, i, j, t;
    if (st < dr)
    {
        m = (st + dr) / 2;
        merge_sort(v, st, m,output);
        merge_sort(v, m + 1, dr,output);
        i = st; j = m + 1; t = 1;
        while (i <= m && j <= dr)
            if (v[j] < v[i])
            {
               
                output[t] = v[j];
                j++;
                t++;
            }
            else
            {
                
                output[t] = v[i];
                i++;
                t++;
            }
        while (i <= m)
        {
            output[t] = v[i];
            i++;
            t++;

        }
        while (j <= dr)
        {
            output[t] = v[j];
            j++;
            t++;

        }
        t = 1;
        for (i = st; i <= dr; i++)
        {
            v[i] = output[t];
            t++;
        }
    }
}
void shell_sort(int v[], int n)
{
    int i, dif, j, x, dif_k;
    dif_k = 1;
    while (dif_k < n){
      dif_k = dif_k * 3 + 1;
    }
    for (dif =dif_k; dif >=1; dif = dif / 3)
    {
        i = dif;
        while (i < n)
        {
            x = v[i];
            j = i;
            while (j >= dif && v[j - dif] > x)
            {
                v[j] = v[j - dif];
                j = j - dif;
            }
            v[j] = x;
            i++;
        }
    }
}


void count_sort_radix(int v[], int n, long long p, int baza,int max1)
{
    int* output; int size;
    output = new int[n + 1];
    int* aparitii;
    if (baza > max1)
    {
        aparitii = new int[max1 + 1];
        size = max1;
    }
    else
    {
        aparitii = new int[baza];
            size = baza - 1;
    }
    for (int i = 0; i <= size; i++)
        aparitii[i] = 0;

    for (int i = 1; i <= n; i++)
        aparitii[(v[i] / p) % baza]++;

    for (int i = 1; i <= size; i++)
        aparitii[i] = aparitii[i - 1] + aparitii[i];

    for (int i = n; i >= 1; i--)
    {
        output[aparitii[(v[i] / p) % baza]] = v[i];
        aparitii[(v[i] / p) % baza]--;
    }
    for (int i = 1; i <= n; i++)
        v[i] = output[i];
    
   

}

void radix_sort(int v[], int n, int baza, int max1)
{
    for (long long p = 1; max1 / p > 0; p = p * baza)
        count_sort_radix(v, n, p, baza,max1);
}

void heapify(int v[], int n, int i)
{
    int max1 = i;
    int st = 2 * i + 1;
    int dr = 2 * i + 2;


    if (st < n and v[st] > v[max1])
        max1 = st;


    if (dr < n and v[dr] > v[max1])
        max1 = dr;

    if (max1 != i) {
        swap(v[i], v[max1]);


        heapify(v, n, max1);
    }
}

void heapsort(int v[], int n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);


    for (int i = n - 1; i > 0; i--) {
        swap(v[0], v[i]);

        heapify(v, i, 0);
    }
}

string test(int v[], int n)
{
    int ok = 1;
    for (int i = 2; i <= n; i++)
        if (v[i] < v[i - 1])
            ok = 0;
    if (ok)
        return "corect ";
    else
        return "gresit ";

}
int main()
{
    int i, n, max1, m, j, k;
    int* v, * cv, * output;
    ifstream f("teste.txt");
    f >> m;
    for (j = 1; j <= m; j++)
    {
        f >> n >> max1;
        v = new int[n + 1];
        cv = new int[n + 1];
        output = new int[n + 1];
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<std::mt19937::result_type> dist(0,max1);

        for (i = 1; i <= n; i++)
        {
            v[i] = dist(rng);
            cv[i] = v[i];
            output[i] = 0;
           

           
        };
        
        auto start = high_resolution_clock::now();
        count_sort(v, n, max1);
        auto stop = high_resolution_clock::now();
        cout<<"Count sort a sortat " << test(v, n);


        auto duration = duration_cast<microseconds>(stop - start);

        if (duration.count() > 100)
            cout << float(duration.count()) / float(pow(10, 6)) << "secunde" << "\n";
        else
            cout << duration.count() << "microsecunde" << "\n";

        cout << "\n";

        for (i = 1; i <= n; i++)
            v[i] = cv[i];

        start = high_resolution_clock::now();
        merge_sort(v, 1, n,output);
        stop = high_resolution_clock::now();


        cout<<"Merge sort a sortat " << test(v, n);

        duration = duration_cast<microseconds>(stop - start);

        if (duration.count() > 100)
            cout << float(duration.count()) / float(pow(10, 6)) << "secunde" << "\n";
        else
            cout << duration.count() << "microsecunde" << "\n";

        cout << "\n";

        for (i = 1; i <= n; i++)
            v[i - 1] = cv[i];

        start = high_resolution_clock::now();
        shell_sort(v, n);
        stop = high_resolution_clock::now();



        cout<<"Shell sort a sortat " << test(v, n);

        duration = duration_cast<microseconds>(stop - start);

        if (duration.count() > 100)
            cout << float(duration.count()) / float(pow(10, 6)) << "secunde" << "\n";
        else
            cout << duration.count() << "microsecunde" << "\n";

        cout << "\n";

        for (i = 1; i <= n; i++)
            v[i] = cv[i];


        start = high_resolution_clock::now();
        radix_sort(v, n, 10, max1);
        stop = high_resolution_clock::now();


        cout<<"Radix sort in baza 10 a sortat " << test(v, n);

        duration = duration_cast<microseconds>(stop - start);
        cout << "Durata a fost de: ";
        if (duration.count() > 100)
            cout << float(duration.count()) / float(pow(10, 6)) << "secunde" << "\n";
        else
            cout << duration.count() << "microsecunde" << "\n";

        cout << "\n";

        for (i = 1; i <= n; i++)
            v[i - 1] = cv[i];


        start = high_resolution_clock::now();
        heapsort(v, n);
        stop = high_resolution_clock::now();


        cout<<"Heapsort a sortat " << test(v, n);

        duration = duration_cast<microseconds>(stop - start);
        if (duration.count() > 100)
            cout << float(duration.count()) / float(pow(10, 6)) << "secunde" << "\n";
        else
            cout << duration.count() << "microsecunde" << "\n";

        cout << "\n";
        
        
        for (i = 4; i <= 65536; i=i*2)
        {
         
            for (k= 1; k <= n; k++)
                v[k] = cv[k];

            start = high_resolution_clock::now();
            radix_sort(v, n, i, max1);
            stop = high_resolution_clock::now();
            cout << "radix sort in baza " << i << " a sortat " << test(v, n);

            duration = duration_cast<microseconds>(stop - start);
            if (duration.count() > 100)
                cout << float(duration.count()) / float(pow(10, 6)) << "secunde" << "\n";
            else
                cout << duration.count() << "microsecunde" << "\n";
            cout << "\n";

           
        }
     
       for (i = 1; i <= n; i++)
            v[i-1] = cv[i];


        start = high_resolution_clock::now();
        sort(v, v+n);
        stop = high_resolution_clock::now();


        cout<<" Algoirtmul nativ de sortare a sortat " << test(v, n);

        duration = duration_cast<microseconds>(stop - start);
        if (duration.count() > 100)
            cout << float(duration.count()) / float(pow(10, 6)) << "secunde" << "\n";
        else
            cout << duration.count() << "microsecunde" << "\n";
        cout << "\n" << "\n"<<"\n"<<"\n";
    }

    f.close();
    return 0;


}














