#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 5;
const int INF = 0x7fffffff;
int graph[N][N];
int dist[N];
int prim(int m)
{
    int res = 0;
    for (int i = 1;i <= m;i++) dist[i] = INF;
    dist[1] = 0;
    for (int i = 2;i <= m;i++) dist[i] = graph[1][i];
    for (int i = 2;i <= m;i++) {
        int path = INF;
        int index = -1;
        for (int j = 2;j <= m;j++) {
            if (dist[j] < path && dist[j] != 0) {
                path = dist[j];
                index = j;
            }
        }
        if (index == -1) return res;
        res += path;
        //cout<<path<<endl;
        dist[index] = 0;
        for (int j = 2;j <= m;j++) {
            dist[j] = min(dist[j],graph[index][j]);
        }
    }
    return res;
}
int main()
{
    int n,m;
    cin>>n>>m;
    for (int i = 1;i <= m;i++)
        for (int j = 1;j <= m;j++)
            graph[i][j] = INF;
    for (int i = 0;i < n;i++) {
        int u,v,w;
        cin>>u>>v>>w;
        graph[u][v] = w;
        graph[v][u] = w;
    }
    cout<<prim(m);
    return 0;
}