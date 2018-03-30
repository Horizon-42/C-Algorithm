//
//  main.cpp
//  coins
//
//  Created by 刘东旭 on 2018/3/30.
//  Copyright © 2018年 刘东旭. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

class Int{
protected:
    unsigned int size;
    vector<int> bits;
public:
    Int(){
        this->size=0;
    }
    
    Int(const string &n){
        this->size=(int)n.size();
        for(int i=(int)n.size()-1; i>=0; --i){
            this->bits.push_back(n[i]-'0');
        }
    }
    
    Int(const Int &a){
        this->size=a.size;
        for(int i=0;i<a.size;++i)
            this->bits.push_back(a.bits[i]);
    }
    
    bool is_0(){
        return this->size==1&&this->bits[0]==0;
    }
    
    int &operator[](int i){
        if(i>=0&&i<(*this).size)
            return (*this).bits[i];
        return (*this).bits[0];
    }
    
    Int &operator=(const Int &a){
        this->size=a.size;
        for(int i=0;i<a.size;++i)
            this->bits[i]=a.bits[i];
        return *this;
    }
    
    friend bool operator<(Int a, Int b){
        if(a.size!=b.size){
            return a.size<b.size;
        }
        else{
            for(int i=a.size-1; i>=0; --i)
                if(a.bits[i]!=b.bits[i])
                    return a.bits[i]<b.bits[i];
        }
        return false;
    }
    
    friend bool operator==(Int a, Int b){
        if(a.size!=b.size)
            return false;
        for(int i=a.size-1; i>=0;--i)
            if(a.bits[i]!=b.bits[i])
                return false;
        return true;
    }
    
    friend bool operator<=(Int a, Int b){
        return a==b||a<b;
    }
    
    friend Int operator+(Int a, Int b){
        Int res;
        res.size=1;
        res.size+=a.size>b.size? a.size:b.size; //两数相加 位数最大为较大的位数加1
        for(int i=0; i<res.size; ++i){
            res.bits.push_back(0);//每一位都初始化为0，方便进位
        }
        int i=0;
        for(; i+1<res.size; ++i){
            if(i>=a.size)
                res.bits[i]+=b.bits[i];
            else if(i>=b.size)
                res.bits[i]+=a.bits[i];
            else if(i<a.size&&i<b.size){
                res.bits[i]+=a.bits[i]+b.bits[i];
            }
            
            if(res.bits[i]>9){
                res.bits[i+1]+=res.bits[i]/10;
                res.bits[i]%=10;
            }
        }
        
        if(res.bits[i]==0)
            res.bits.erase(res.bits.begin()+i);
        
        res.size=(int)res.bits.size();
        
        return res;
    }
    
    Int &operator++(){
        this->bits[0]+=1;
        for(int i=0;this->bits[i]>9;++i){
            if(i+1<this->size){
                this->bits[i+1]+=this->bits[i]/10;
            }
            else{
                this->bits.push_back(1);
                this->size++;
            }
            this->bits[i]%=10;
        }
        return *this;
    }
    
    friend Int operator*(Int a, Int b){
        Int res;
        if(a.is_0()||b.is_0()){
            res.size=1;
            res.bits.push_back(0);
        }
        res.size = a.size+b.size+1;
        for(int i=0; i<res.size; ++i)
            res.bits.push_back(0);
        
        for(int i=0; i<a.size; ++i){
            for(int j=0; j<b.size; ++j){
                res.bits[i+j]+=a.bits[i]*b.bits[j]; //先乘，再进位
                if(res.bits[i+j]>9){
                    res.bits[i+j+1]+=res.bits[i+j]/10;
                    res.bits[i+j]%=10;
                }
            }
        }
        
        for(int i=(int)res.bits.size()-1; res.bits[i]==0; --i){
            res.bits.erase(res.bits.begin()+i);
        }
        res.size = (int)res.bits.size();
        
        return res;
    }
    
    Int floor_sqrt(){
        //为了提高寻找开平方的效率，这里使用一个简便的算法
        //假设一个位数为len的数，开平方后是一个位数为lenSqrt的数
        //如果len为偶数，则lenSqrt=len/2
        //如果len为奇数 则lenSqrt=（len/2）+1
        Int res;
        res.size=this->size/2+this->size%2;
        for(int i=0; i<res.size; ++i){
            res.bits.push_back(0);
        }
        
        for(int i=res.size-1; i>=0; --i){
            int tmp=0;
            for(int bit=1;bit<10;++bit){
                res[i]=bit;
                if(res*res==*this)
                    return res;
                else if(*this<res*res)
                    break;
                tmp=bit;
            }
            res[i]=tmp;
        }
        
        return res;
    }
    
    friend ostream &operator<<(ostream &out, const Int &a){
        
        for(int i=a.size-1; i>=0; --i){
            out<<a.bits[i];
        }
        
        return out;
    }
};

int main(){
    string n_str, m_str;
    cin>>n_str>>m_str;
    Int n(n_str);
    Int m(m_str);
   // cout<<n.floor_sqrt()<<" "<<m.floor_sqrt()<<endl;
    cout<<n.floor_sqrt()*m.floor_sqrt();
    
    return 0;
}
