#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int lights(vector<int> s, vector<bool> used_l){
    int l=0, d=0;
    for(int i=1;i<s.size();++i){
        if(used_l[s[i]])
            d++;
        else 
            l++;
    }
    return l-d;
}

int main(){
    freopen("light.in","r",stdin);
    int n=0,k=0;
    int res=0;
    vector<vector<int> > ss;

    int b=0, max=0;

    cin>>n;
    for(int i=0;i<n;++i){
        vector<int> s;
        int all=0;
        cin>>all;
        s.push_back(all);
        if(max<all){
            b=i;
            max=all;
        }
        for(int j=0;j<all;++j){
            int l=0;
            cin>>l;
            if(k<l)
                k=l;
            s.push_back(l);
        }
        ss.push_back(s);
    }

    vector<bool> used_s;
    for(int i=0;i<ss.size();++i)
        used_s.push_back(false);
    
    vector<bool> used_l;
    for(int i=0;i<=k;++i)
        used_l.push_back(false);
    used_s[b]=true;
    res+=ss[b][0];
    while(42){
        bool sw=false;
        for(int i=1; i<ss[b].size();++i){
            used_l[ss[b][i]]=!used_l[ss[b][i]];
        }
        max=0;
        for(int i=0;i<n;++i){
            if(used_s[i])
                continue;
            int l=lights(ss[i],used_l);
            if(max<=l){
                sw=true;
                max=l;
                b=i;
            }
        }
        if(!sw)
            break;
        res+=max;
        used_s[b]=true;
    }

    cout<<res;
    return 0;
}