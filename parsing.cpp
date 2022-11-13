#include "bits/stdc++.h"

using namespace std;

typedef pair<string,string> pss;

struct person
{
    string name;
    string father_name;
    string husband_name;
    string house_number;
    int age;
    string gender;
};

bool check_first(string s)
{
    return s == "Name" ;
}

bool check_father(string s)
{
    return s == "Father" or s == "Fathers";
}

bool check_husband(string s)
{
    return s == "Husband" or s == "Husbands";
}

bool check_house(string s)
{
    return s == "House";
}

string parse_word(string s)
{
    int n=s.length(),i;
    string ans="";
    for(i=0;i<n;i++)
    {
        if((s[i]>='a' and s[i]<='z') or (s[i]>='A' and s[i]<='Z'))
            ans.push_back(s[i]);
    }
    return ans;
}

vector<string> input;
int len;
map< string,pss > solve()
{
    string word;
    map<string,pss>ans;    // {person_name,{relation,relative_name}}
    bool accept=false;
    string prev="";
    int iter=1;
    while(iter<len)
    {
        word=input[iter++];
        word=parse_word(word);
        //cout<<word<<endl;
        if(!check_first(word) and !check_first(prev))
            continue;
        //cout<<" Found"<<endl;
        string s;
        string name="";
        int count=0;
        string relation="";
        while(iter<len)
        {
            s=input[iter++];
            s=parse_word(s);
            if(check_first(s))
            {
                prev=s;
                break;
            }
            if(check_father(s) or check_husband(s))
            {
                if(check_father(s))
                relation="Father";
                else if(check_husband(s))
                relation="Husband";
                prev=s;
                s=input[iter++];
                break;
            }
            name+=s+" ";
            count++;
        }
        name.pop_back();
        //cout<<"Name is here: "<<name<<endl;
        if(check_first(prev) and count>5)
        continue;
        //cout<<"Continued"<<endl;
        queue<string>q;
        q.push(name);
        if(check_first(prev))
        {
            prev="";
            name="";
            while(iter<len)
            {
                s=input[iter++];
                s=parse_word(s);
                if(check_first(s))
                {
                    prev=s;
                    break;
                }
                if(check_father(s) or check_husband(s))
                {
                    if(check_father(s))
                    relation="Father";
                    else if(check_husband(s))
                    relation="Husband";
                    prev=s;
                    s=input[iter++];
                    break;
                }
                name+=s+" ";
                count++;
            }
            name.pop_back();
            q.push(name);
        }
        if(check_first(prev))
        {
            //cout<<"Here"<<endl;
            prev="";
            name="";
            while(iter<len)
            {
                s=input[iter++];
                s=parse_word(s);
                if(check_first(s))
                {
                    prev=s;
                    break;
                }
                if(check_father(s) or check_husband(s))
                {
                    if(check_father(s))
                    relation="Father";
                    else if(check_husband(s))
                    relation="Husband";
                    prev=s;
                    s=input[iter++];
                    break;
                }
                name+=s+" ";
                count++;
            }
            name.pop_back();
            q.push(name);
        }
        while(q.size())
        {
            name=q.front();
            q.pop();
            string rel="";
            string temp="";
            while(iter<len)
            {
                s=input[iter++];
                s=parse_word(s);
                if(check_first(s))
                {
                    prev=s;
                    break;
                }
                if(check_father(s) or check_husband(s) or check_house(s))
                {
                    if(check_father(s))
                    temp="Father";
                    else if(check_husband(s))
                    temp="Husband";
                    prev=s;
                    s=input[iter++];
                    break;
                }
                rel+=s+" ";
            }
            rel.pop_back();
            while(name.size() and name[0]==' ')
                name.erase(name.begin());
            while(name.size() and name[name.size()-1]==' ')
                name.pop_back();
            while(rel.size() and rel[0]==' ')
                rel.erase(rel.begin());
            while(rel.size() and rel[name.size()-1]==' ')
                rel.pop_back();
            ans[name]= make_pair(relation,rel);
            relation=temp;
        }

    }
    return ans;
}


int main(int argc, char *argv[]) {

    len=argc;
    for (int i = 0; i <argc ; i++) {
        input.push_back(argv[i]);
    }
    map<string,pss>m=solve();
    for(auto it:m)
    {
        string name=it.first;
        string relative=it.second.second;
        cout<<it.first<<"->"<<it.second.first<<" "<<it.second.second;
        while(m.find(relative)!=m.end())
        {
            cout<<"->"<<m[relative].first<<" "<<m[relative].second;
            relative=m[relative].second;
        }
        cout<<endl;
    }
}
