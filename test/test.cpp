#include <iostream>
#include <vector>
using namespace std;
struct edge {
    int a,b;
    double c;
    edge(int a,int b,double c):a(a),b(b),c(c) {}
    edge():a(0),b(0),c(0) {}
    bool operator < (const edge& e) {
        if (c == e.c) return a < e.a;
        return c < e.c;
    }
    bool operator == (const edge& e) {
        return a == e.a && b == e.b && c == e.c;
    }
};
void heap_sort(vector<edge>& edges) {
    for (int i = edges.size()/2-1;i >= 0;i--) {
        int t = i;
        while (t*2+1 < edges.size()) {
            int j = t*2+1;
            if (j+1 < edges.size() && edges[j] < edges[j+1]) j++;
            if (edges[t] < edges[j]) {
                swap(edges[t],edges[j]);
                t = j;
            } else {
                break;
            }
        }
    }
    for (int i = edges.size()-1;i > 0;i--) {
        swap(edges[0],edges[i]);
        int t = 0;
        while (t*2+1 < i) {
            int j = t*2+1;
            if (j+1 < i && edges[j] < edges[j+1]) j++;
            if (edges[t] < edges[j]) {
                swap(edges[t],edges[j]);
                t = j;
            } else {
                break;
            }
        }
    }
}
template<typename T>
bool find(vector<T> v,T n)
{
    for (int i = 0;i < v.size();i++) {
        if (v[i] == n) return true;
    }
    return false;
}
int main()
{
    int n;
    cin>>n;
    vector<edge> edges(n);
    for (int i = 0;i < n;i++) {
        int a,b;double c;
        cin>>a>>b>>c;
        edges[i] = edge(a,b,c);
    }
    vector<edge> sorted_edges(edges);
    heap_sort(sorted_edges);
    vector<int> parent;
    vector<edge> ret;
    for (int i = 0;i < n;i++) {
        if (i == 0) {
            parent.push_back(sorted_edges[i].a);
            parent.push_back(sorted_edges[i].b);
            ret.push_back(sorted_edges[i]);
        } else {
            if (find(parent,sorted_edges[i].a) == 0 && find(parent,sorted_edges[i].b) != 0) {
                parent.push_back(sorted_edges[i].a);
                ret.push_back(sorted_edges[i]);
            } else if (find(parent,sorted_edges[i].a) != 0 && find(parent,sorted_edges[i].b) == 0) {
                parent.push_back(sorted_edges[i].b);
                ret.push_back(sorted_edges[i]);
            }
        }
    }
    // for (int i = 0;i < ret.size();i++) {
    //     cout<<ret[i].a<<" "<<ret[i].b<<" "<<ret[i].c<<endl;
    // }
    int cnt = 0;
    for (int i = 0;i < edges.size();i++) {
        if (find(ret,edges[i]) || find(ret,edge(edges[i].b,edges[i].a,edges[i].c))) cnt++;
    }
    cout<<cnt<<endl;
    for (int i = 0;i < edges.size();i++) {
        if (find(ret,edges[i])) {
            cout<<edges[i].a<<" "<<edges[i].b<<" "<<edges[i].c<<endl;
        } else if (find(ret,edge(edges[i].b,edges[i].a,edges[i].c))) {
            cout<<edges[i].a<<" "<<edges[i].b<<" "<<edges[i].c<<endl;
        }
    }
    return 0;
}