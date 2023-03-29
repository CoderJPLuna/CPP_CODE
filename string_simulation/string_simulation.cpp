#pragma warning(disable:4996)
#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;
namespace st
{
    class string
    {
    private:
        char* _str;
        size_t _size;
        size_t _capacity;
        static const size_t npos;
    public:
        //指针是天然的迭代器
        /*
        typedef char* iterator;
        iterator begin()
        {
            return _str;
        }
        iterator end()
        {
            return _str+_size;
        }
        */
        typedef const char* iterator;
        iterator begin()const
        {
            return _str;
        }
        iterator end()const
        {
            return _str+_size;
        }
        string(const char* st="")
        {
            _size=strlen(st);
            _capacity=_size;
            _str=new char[_capacity+1];
            strcpy(_str,st);
        }
        //拷贝构造现代写法
        //s2(s1)
        string(const string& st)
        :_str(nullptr)//s是局部对象出了这个作用域这个空间就会释放，但不能对随机指向的空间释放
        ,_size(0)
        ,_capacity(0)
        {
            string s(st._str);//临时变量指向st._str
            swap(s);
        }
        /*
        string(const string& st)
        :_str(new char[strlen(st._str)+1])
        {
            strcpy(_str,st._str);
        }
        */
        char& operator[](size_t i)
        {
            assert(i<_size);
            return _str[i];
        }
        size_t size()
        {
            return _size;
        }
        ~string()
        {
            delete[] _str;
        }
        const char* c_str()
        {
            return _str;
        }
        //现代写法
        //s1=s2
        string& operator=(string st)
        {
            this->swap(st);
            return *this;
        }
        /*
        string& operator=(const string &st)
        {
            if(this!=&st)
            {
                delete[] _str;
                _str=new char[strlen(st._str)+1];
                strcpy(_str,st._str);
            }
            return *this;
        }
        */
        void reserve(size_t n)
        {
            if(n>_capacity)
            {
                char* tem=new char[n+1];
                strcpy(tem,_str);
                delete[]_str;
                _str=tem;
                _capacity=n;
            }
        }
        void resize(size_t n,char ch='\0')
        {
            if(n<_size)
            {
                _str[n]='\0';
                _size=n;
            }
            else
            {
                if(n>_capacity)
                {
                    reserve(n);
                }
                for(size_t i=_size;i<n;i++)
                {
                    _str[i]=ch;
                }
                _str[n]='\0';
                _size=n;
            }
        }
        void push_back(char ch)
        {
            if(_size==_capacity)
            {
                reserve(2*_capacity);
            }
            _str[_size]=ch;
            ++_size;
            _str[_size]='\0';
        }
        void append(const char* ch)
        {
            size_t len=strlen(ch)+1;
            if(_size+len>_capacity)
            {
                reserve(len+_size);
            }
            strcpy(_str+_size,ch);
            _size+=len;
        }
        string& operator+=(char s)
        {
            push_back(s);
            return *this;
        }
        string& operator+=(const string& ss)
        {
            append(ss._str);
            return *this;
        }
        void swap(string& st)
        {
            ::swap(_str,st._str);
            ::swap(_size,st._size);
            ::swap(_capacity,st._capacity);
        }
        void insert(size_t n,char ch)
        {
            if(_size==_capacity)
            {
                size_t capacity=(_capacity==0)?8:_capacity*2;
                reserve(capacity);
            }
            int end=_size+1;
            while(n<end)
            {
                _str[end]=_str[end-1];
                --end;
            }
            _str[n]=ch;
            _size++;
        }
        void insert(size_t n,const char* ch)
        {
            size_t len=strlen(ch);
            if(_size+len>_capacity)
            {
                reserve(_size+len);
            }
            size_t end=_size+len;
            while(end>=n+len)
            {
                _str[end]=_str[end-len];
                --end;
            }
            strncpy(_str+n,ch,len);
            _size+=len;
        }
        void exit(size_t np,size_t npo=npos)
        {
            if(npo==npos||np+npo>_size)
            {
                _str[np]='\0';
                _size=np;
            }
            else
            {
                strcpy(_str+np,_str+np+npo);
                _size-=npo;
            }
        }
        size_t find(const char* ch,size_t p=0)
        {
            const char* ret=strstr(_str+p,ch);
            if(ret==nullptr)
            {
                return npos;
            }
            else
            {
                return ret-_str;
            }
        }
    };
    const size_t string::npos=-1;
    bool operator>(string s1,string s2)
    {
        size_t i=0,j=0;
        while(i<s1.size()&&s2.size())
        {
            if(s1[i]>s2[j])
            {
                return true;
            }
            else if(s1[i]<s2[j])
            {
                return false;
            }
            else
            {
                i++;
                j++;
            }
        }
        if(i<s1.size())
        {
            return true;
        }
        else if(j<s2.size())
        {
            return false;
        }
        else{
            return true;
        }
    }
    ostream& operator<<(ostream& out,string& s)
    {
        for(size_t i=0;i<s.size();++i)
        {
            out<<s[i];
        }
        return out;
    }
    istream& operator>>(istream& in,string& s)
    {
        s.resize(0);
        char ch;
        while(1)
        {
            //in>ch;
            in.get(ch);
            if(ch==' '||ch=='\n')
            {
                break;
            }
            else{
                s+=ch;
            }
        }
        return in;
    }
    bool operator==(string& s1,string& s2)
    {
        size_t i=0,j=0;
        while(i<s1.size()&&s2.size())
        {
            if(s1[i]>s2[i])
            {
                return false;
            }
            else if(s1[i]<s2[j])
            {
                return false;
            }
            else
            {
                i++;
                j++;
            }
        }
        if(i==s1.size()&&j==s2.size())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void print(const st::string& s)
    {
        st::string::iterator it=s.begin();
        while(it<s.end())
        {
            cout<<*it;
            ++it;
        }
    }
}
int main()
{
    st::string s1("123456");
    st::string s2=s1;
    //s11.exit(2,3);
    //print(s1);
    cout<<s2;
    if(s1==s2)
    {
        cout<<"ok";
    }
    else
    {

        cout<<"no";
    }
    return 0;
}