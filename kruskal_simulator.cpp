#include <bits/stdc++.h>
using namespace std;

/*
 Kruskal's MST Simulator
 - Reads a weighted undirected graph
 - Sorts edges by weight
 - Uses Disjoint Set Union (Union-Find) to pick edges
 - Prints step-by-step selection with simple ASCII visualization
 - Saves final MST edges and total weight

 How to use:
 1) Compile: g++ kruskal_simulator.cpp -o kruskal
 2) Run: ./kruskal
*/

struct Edge {
    int u, v;
    int w;
    int id;
};

struct DSU {
    int n;
    vector<int> parent, rankv;
    DSU(int n=0){ init(n); }
    void init(int N){
        n = N;
        parent.resize(N+1);
        rankv.assign(N+1,0);
        for(int i=0;i<=N;i++) parent[i]=i;
    }
    int find(int x){
        if(parent[x]==x) return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int a, int b){
        a = find(a); b = find(b);
        if(a==b) return false;
        if(rankv[a]<rankv[b]) swap(a,b);
        parent[b]=a;
        if(rankv[a]==rankv[b]) rankv[a]++;
        return true;
    }
};

void printEdges(const vector<Edge>& edges){
    cout << "Edges (id: u - v : weight):\n";
    for(auto &e : edges){
        cout << setw(2) << e.id << ": " << e.u << " - " << e.v << " : " << e.w << "\n";
    }
}

void simulateKruskal(int n, vector<Edge> edges, bool verbose=true){
    // sort by weight, break ties by id
    sort(edges.begin(), edges.end(), [](const Edge&a, const Edge&b){
        if(a.w!=b.w) return a.w < b.w;
        return a.id < b.id;
    });

    DSU dsu(n);
    vector<Edge> mst;
    int total=0;

    cout << "\nEdges sorted by weight (id: u-v : weight):\n";
    for(auto &e: edges) cout << setw(2) << e.id << ": " << e.u << "-" << e.v << " : " << e.w << "\n";

    cout << "\nStarting Kruskal's simulation...\n\n";
    for(size_t i=0;i<edges.size();++i){
        auto &e = edges[i];
        cout << "Considering edge " << e.id << " (" << e.u << " - " << e.v << " : " << e.w << ")\n";
        int ru = dsu.find(e.u);
        int rv = dsu.find(e.v);
        cout << "  Find roots: root("<<e.u<<")="<<ru<<", root("<<e.v<<")="<<rv<<"\n";
        if(ru!=rv){
            cout << "  => No cycle. SELECT this edge.\n";
            dsu.unite(ru, rv);
            mst.push_back(e);
            total += e.w;
            // Visual: print current components (small)
            // Build component groups
            unordered_map<int, vector<int>> comp;
            for(int v=1; v<=n; ++v) comp[dsu.find(v)].push_back(v);
            cout << "  Components now: ";
            bool first = true;
            for(auto &p: comp){
                if(!first) cout << " | ";
                first = false;
                cout << "{";
                for(size_t k=0;k<p.second.size();++k){
                    if(k) cout << ",";
                    cout << p.second[k];
                }
                cout << "}";
            }
            cout << "\n\n";
        } else {
            cout << "  => Would form a cycle. SKIP this edge.\n\n";
        }
        // Pause-like divider
        if(verbose){
            cout << "----------------------------------------\n";
        }
        // Early stop: MST complete when n-1 edges selected
        if((int)mst.size() == n-1) {
            cout << "MST complete (selected " << mst.size() << " edges).\n";
            break;
        }
    }

    if((int)mst.size() != n-1){
        cout << "\nWarning: Graph is not connected. MST not possible for entire graph.\n";
    }

    cout << "\nFinal MST edges (id: u-v : w):\n";
    for(auto &e : mst) cout << setw(2) << e.id << ": " << e.u << " - " << e.v << " : " << e.w << "\n";
    cout << "Total weight of MST (or forest): " << total << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << "Kruskal's MST Simulator\n";
    cout << "------------------------\n";
    cout << "Input method:\n";
    cout << "1) Manual input\n";
    cout << "2) Example graph\n";
    cout << "Choose (1 or 2): ";
    int mode;
    if(!(cin >> mode)) return 0;

    int n = 0, m = 0;
    vector<Edge> edges;

    if(mode == 1){
        cout << "Enter number of vertices (n): ";
        cin >> n;
        cout << "Enter number of edges (m): ";
        cin >> m;
        cout << "Enter each edge as: u v w (1-based vertices). Example: 1 2 10\n";
        for(int i=1;i<=m;i++){
            int u,v,w;
            cin >> u >> v >> w;
            edges.push_back({u,v,w,i});
        }
    } else {
        // Example graph (connected)
        // n=6, m=9
        n = 6;
        vector<tuple<int,int,int>> ex = {
            {1,2,3},
            {1,3,1},
            {2,3,7},
            {2,4,5},
            {3,4,4},
            {3,5,2},
            {4,5,6},
            {4,6,8},
            {5,6,9}
        };
        int id=1;
        for(auto &t: ex){
            edges.push_back({get<0>(t), get<1>(t), get<2>(t), id++});
        }
        m = edges.size();
        cout << "Loaded example graph with n="<<n<<", m="<<m<<"\n";
        printEdges(edges);
    }

    cout << "\nRun verbose simulation? (1 = yes / 0 = no): ";
    int vflag;
    cin >> vflag;
    bool verbose = (vflag==1);

    simulateKruskal(n, edges, verbose);

    cout << "\nProgram finished. Thank you!\n";
    return 0;
}
