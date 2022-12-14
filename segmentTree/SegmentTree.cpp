//
struct info{ // Can be Change!
    ll mn;
    int pos;
    bool operator >(const ll &p){ // Can be Change!
        if(pos == p && p == -1) return true;
        return false; 
    }
};

//Algorithm or Logic: Segment Tree
//Complexity: update/query : O(log n) space: O(4*n)
// 1 to n (segmentTree) // array of value (0 to n-1) // query/udpate are 1 to n
// Update k-position / Query Range
template<class T>
struct segTree{
    int n; 
    vector<T> tree; vector <T> val; 
    
    segTree<T>(){}
    segTree<T>(int x, vector<T>& st ,vector<T>& vals):n(x), tree(st),val(vals){build(1,0,n-1);}
    
    int left(int p) {return p << 1;}
    int right(int p) {return (p << 1) + 1;}
    
    void build(int p, int L, int R){
        if(L == R)
            tree[p] = val[L];
        else{
            int mid = L + ((R-L)>>1);
            build(left(p),L,(mid));
            build(right(p),(mid+1),R);
            T p1 = tree[left(p)], p2 = tree[right(p)];

            //
            tree[p] = mrg(p1,p2);
            //
        }
    }

    T query(int p, int L, int R, int i, int j){
        if(i > R || j < L) return {oo,-1}; // Segmento fuera del rango // Can be Change!
        if(L >= i && R<= j) return tree[p]; // Dentro del rango
        
        int mid = L + ((R-L)>>1);
        T p1 = query(left(p), L, mid, i, j);
        T p2 = query(right(p), mid+1, R, i, j);

        if(p1 > -1) return p2; // Can be Change!
        if(p2 > -1) return p1; // Can be Change!

        return (mrg(p1,p2));
    }
    
    T DoQuery(int i, int j){return query(1,0,n-1,i-1,j-1);}

    T mrg(T p1, T p2){ // Can be Change!
        T all;
        all.mn = min(p1.mn,p2.mn);
        if(p1.mn > p2.mn) all.pos = p2.pos;
        else all.pos = p1.pos;

        return all;
    }

    void update(int p, int L, int R, int ind, T valNew){
        if(L == R){
            tree[p] = valNew;
        }
        else{
            int mid = L + ((R-L)>>1);
            if(ind <= mid) update(left(p),L,(mid), ind, valNew);
            else update(right(p),(mid+1),R, ind, valNew);
            
            T p1 = tree[left(p)], p2 = tree[right(p)];
            tree[p] = mrg(p1,p2);
        }
    }
    void DoUpdate(int ind, T valNew){update(1,0,n-1,ind-1,valNew);}
};
//Create Segment Tree
//vector<info> st(4*n); /*tree.assign(4*n,0)*/
//segTree<info> myTree(n,st,ar); // ar[i] = {ax,i};
//
//
