#include <bits/stdc++.h>

using namespace std;

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
    return s == "Name";
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

map<string,pair<string,string>> solve()
{
    string word;
    map<string,pair<string,string>>ans;    // {person_name,{relation,relative_name}}
    bool accept=false;
    string prev="";
    while(cin>>word)
    {
        word=parse_word(word);
        //cout<<word<<endl;
        if(!check_first(word) and !check_first(prev))
            continue;
        //cout<<" Found"<<endl;
        string s;
        string name="";
        int count=0;
        string relation="";
        while(cin>>s)
        {
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
                cin>>s;
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
            while(cin>>s)
            {
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
                    cin>>s;
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
            prev="";
            name="";
            while(cin>>s)
            {
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
                    cin>>s;
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
            while(cin>>s)
            {
                s=parse_word(s);
                if(check_father(s) or check_husband(s) or check_house(s))
                {
                    if(check_father(s))
                    temp="Father";
                    else if(check_husband(s))
                    temp="Husband";
                    prev=s;
                    cin>>s;
                    break;
                }
                rel+=s+" ";
            }
            rel.pop_back();
            ans[name]={relation,rel};
            relation=temp;
        }
        
    }
    return ans;
}


int main() {
    map<string,pair<string,string>>m=solve();
    for(auto it:m)
    {
        cout<<it.first<<"->"<<it.second.first<<" "<<it.second.second<<endl;
    }
}