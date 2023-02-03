#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;
int** create(unsigned int n, unsigned int m)
{
    int **a = new int*[n];
    for (unsigned int i = 0; i < n; i++)
        a[i] = new int[m];
    return a;
}
void destroy(int** a, unsigned int n)
{
    for (unsigned int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
}
void print(int **a, unsigned int n, unsigned int m)
{
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
}

int** create_compact(int **a, unsigned int H, unsigned int W){
    int **fuck = create(H/2 + 1u, W/2 + 1u);
    for(int h = 0; h < H/2 + 1; h++){
        for(int w = 0; w < W/2 + 1; w++){
            fuck[h][w] = a[2*h][2*w] +
            H%2 == 0 ? a[2*h+1][2*w] : 0 +
            W%2 == 0 ? a[2*h][2*w+1] : 0 +
            W%2 == 0 && h%2 == 0 ? a[2*h+1][w*2+1] : 0;
        }
    }
    return fuck;
}

void print_compact(int **compact, unsigned int n, unsigned int m){
    print(compact, ceil(n/2), ceil(m/2));
}

void destroy_compact(int** compact, unsigned int n){
    destroy(compact, ceil(n/2));
}

int main()
{
    unsigned int n, m;
    cin >> n >> m;
    int **a = create(n, m);
    for (unsigned int i = 0; i < n; i++)
        for (unsigned int j = 0; j < m; j++)
            cin >> a[i][j];
    int** b = create_compact(a, n, m);
    print(a, n, m);
    print_compact(b, n, m);
    destroy(a, n);
    destroy_compact(b, n);
    return 0;
}