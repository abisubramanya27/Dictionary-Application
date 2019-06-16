#include<bits/stdc++.h>
#include<unistd.h>

#define for0(i,n) for(ll i = 0;i < n;i++)
#define for1(i,n) for(ll i = 1;i <= n;i++)

using namespace std;

typedef struct TreeNode Node;
typedef map<string,string> Dtype;
typedef long long ll;
typedef vector<ll> vl;

struct TreeNode{
    Dtype Data;
    map<char,Node*> next;
    Node* parent;
    bool isWord;
    TreeNode(){
    	Data["meaning"] = "";
    	Data["synonym"] = "";
    	Data["example"] = "";
    	for(int i = 0;i < 26;i++){
    		next[char(i+'a')] = NULL;
    	}
    	parent = NULL;
        isWord = false;
    }
};

struct Dictionary{
	Node* root;
    Dictionary() {
        root = new TreeNode();
    }
    void insert(string word,string m = "",string syn = "",string ex = ""){
        Node* tmp = root;
        transform(word.begin(),word.end(),word.begin(),::tolower);
        for(ll i = 0;i < word.length();i++){
        	if(!(tmp->next[word[i]])){
                tmp->next[word[i]] = new TreeNode();
                tmp->next[word[i]]->parent = tmp;
                tmp = tmp->next[word[i]];
        	}
        	else tmp = tmp->next[word[i]];
        }
        if(tmp->Data["meaning"] != "") {
        	cout<<"WORD ALREADY EXISTS!!\n\n";
        	return;
        }
        tmp->isWord = true;
        tmp->Data["meaning"] = m;
        tmp->Data["synonym"] = syn;
        tmp->Data["example"] = ex;
    }
    Node* find(string word){
        Node* tmp = root;
        Node* found = NULL;
        transform(word.begin(),word.end(),word.begin(),::tolower);
        for(ll i = 0;i < word.length();i++){
        	tmp = tmp->next[word[i]];
        	if(!tmp){
                break;
        	}
        }
        if(tmp) found = tmp;
        return found;
    }
    void setMeaning(string word,string m){
    	transform(word.begin(),word.end(),word.begin(),::tolower);
    	Node* found = find(word);
    	if(found){
            found->Data["meaning"] = m;
            found->isWord = true;
    	}
    	else{
    		cout<<"WORD NOT FOUND!!\n\n";
    	}
    }
    void setSynonym(string word,string syn){
    	transform(word.begin(),word.end(),word.begin(),::tolower);
    	Node* found = find(word);
    	if(found){
            found->Data["synonym"] = syn;
            found->isWord = true;
    	}
    	else{
    		cout<<"WORD NOT FOUND!!\n\n";
    	}
    }
    void setExample(string word,string ex){
    	transform(word.begin(),word.end(),word.begin(),::tolower);
    	Node* found = find(word);
    	if(found){
            found->Data["example"] = ex;
            found->isWord = true;
    	}
    	else{
    		cout<<"WORD NOT FOUND!!\n\n";
    	}
    }
    void setDetails(string word,string m,string syn,string ex){
    	transform(word.begin(),word.end(),word.begin(),::tolower);
    	Node* found = find(word);
    	if(found){
    		found->Data["meaning"] = m;
    		found->Data["synonym"] = syn;
            found->Data["example"] = ex;
            found->isWord = true;
    	}
    	else{
    		cout<<"WORD NOT FOUND!!\n\n";
    	}
    }
    ll Lev_Distance(string s1,string s2){
        ll l1 = s1.length(),l2 = s2.length();
        vl dp(l1+1,0),tmp(l1+1,0);
        for1(i,l1) dp[i] = i;
        for1(i,l2){
            tmp[0] = i;
            for1(j,l1){
                if(s1[j-1] == s2[i-1]) tmp[j] = dp[j-1];
                else{
                    tmp[j] = 1+min(dp[j-1],min(dp[j],tmp[j-1]));
                }
            }
            dp.swap(tmp);
            tmp.clear();
            tmp.resize(l1+1,0);
        }
        return dp[l1];
    }
    void List_Words(Node* node,string w,string word){
        if(node){
            if(w != "" && node->isWord){
                if(Lev_Distance(word,w) <= word.length()/2){
                    cout<<"\t\t"<<w<<"\n";
                }
            }
            for(int i = 0;i < 26;i++){
                if(node->next[char(i+'a')]){
                    List_Words(node->next[char(i+'a')],w+char(i+'a'),word);
                }
            }
        }
    }
    void Suggest(string word){
        cout<<"DID YOU MEAN :\n\n";
        List_Words(root,"",word);
    }
    void getDetails(string word){
    	transform(word.begin(),word.end(),word.begin(),::tolower);
    	Node* found = find(word);
    	if(found && found->isWord){
    		cout<<word<<" : \n\n";
    		cout<<"MEANING : ";
            if(found->Data["meaning"] != "") cout<<found->Data["meaning"]<<endl;
            else cout<<"--NIL--"<<endl;
            cout<<"SYNONYM : ";
            if(found->Data["synonym"] != "") cout<<found->Data["synonym"]<<endl;
            else cout<<"--NIL--"<<endl;
            cout<<"EXAMPLE : ";
            if(found->Data["example"] != "") cout<<found->Data["example"]<<endl;
            else cout<<"--NIL--"<<endl;
    	}
    	else{
    		cout<<"WORD NOT FOUND!!\n\n";
            Suggest(word);
    	}
    }
    void remove(string word){
    	transform(word.begin(),word.end(),word.begin(),::tolower);
    	Node* found = find(word);
    	if(found){
            found->Data["meaning"] = "";
            found->Data["synonym"] = "";
            found->Data["example"] = "";
            found->isWord = false;
            bool stop = false;
            while(!stop && found && found != root){
            	for(int i = 0;i < 26;i++){
    				if(found->next[char(i+'a')]) {stop = true;break;}
    	        }
    	        if(!stop){
    	        	Node* tmp = found->parent;
                    if(tmp){
                        for(int i = 0;i < 26;i++){
        					if(tmp->next[char(i+'a')] == found) {tmp->next[char(i+'a')] = NULL;break;}
        	            }
                    }
    	            delete found;
    	            found = tmp;
    	        }
            }
    	}
    	else{
            cout<<"WORD NOT FOUND!!\n\n";
    	}
    }
    void print(Node* node,string word){
        if(node){
            if(word != "" && node->isWord){
                cout<<word<<" ";
                if(node->Data["meaning"] != "") cout<<"MEANING: "<<node->Data["meaning"]<<" ";
                if(node->Data["synonym"] != "") cout<<"SYNONYM: "<<node->Data["synonym"]<<" ";
                if(node->Data["example"] != "") cout<<"EXAMPLE: "<<node->Data["example"]<<" ";
                cout<<"$"<<endl;
            }
            for(int i = 0;i < 26;i++){
                if(node->next[char(i+'a')]){
                    print(node->next[char(i+'a')],word+char(i+'a'));
                }
            }
        }
    }
    void ListOut(int mode = 1){
        FILE* fptr;
        if(mode != 1) {
            fptr = freopen("DICTIONARY.txt","w",stdout);
            print(root,"");
            fclose(fptr);
        }
        else{
            print(root,"");
        }
    }
    void Load(){
        ifstream fin("DICTIONARY.txt",ios::in);
        if(fin){
            string tmp;
            while(fin>>tmp){
                string w,m,s,x;
                int mode = 0;
                w = tmp;
                fin>>tmp;
                while(tmp != "$"){
                    if(tmp != "MEANING:" && tmp != "SYNONYM:" && tmp != "EXAMPLE:"){
                        if(mode == 1){
                            m += tmp;
                            m += " ";
                        }
                        else if(mode == 2){
                            s += tmp;
                            s += " ";
                        }
                        else if(mode == 3){
                            x += tmp;
                            x += " ";
                        }
                    }
                    if(tmp == "MEANING:"){
                        mode = 1;
                    }
                    else if(tmp == "SYNONYM:"){
                        mode = 2;
                    }
                    else if(tmp == "EXAMPLE:"){
                        mode = 3;
                    }
                    fin>>tmp;
                }
                if(m.length()) m.pop_back();
                if(s.length()) s.pop_back();
                if(x.length()) x.pop_back();
                insert(w,m,s,x);
            }
        }
        fin.close();
    }
};

void Pause(){
    cout<<"\n\n\n\t\tEnter any character to return to main menu.....";
    cin.get();
}

int main(){
    Dictionary D;
    D.Load();
    int mode = -1;
    string st = "DICTIONARY APPLICATION";
    int l = st.length();
    int pos = (int)((80-l)/2);
    while(mode != 9){
        system("clear");
        for(int i=0;i<pos;i++)
            cout<<" ";
        cout<<st<<"\n\n\n";
        cout<<"\t\t1. Search for a word\n";
        cout<<"\t\t2. Insert a word\n";
        cout<<"\t\t3. Inert the meaning of a word\n";
        cout<<"\t\t4. Insert the synonym of a word\n";
        cout<<"\t\t5. Insert an example for a word\n";
        cout<<"\t\t6. Insert the details for a word\n";
        cout<<"\t\t7. Remove a word from the dictionary\n";
        cout<<"\t\t8. List out the words in the dictionary\n";
        cout<<"\t\t9. Exit the application\n\n";
        cout<<"Enter the number based on the action required : ";
        cin>>mode;
        switch(mode){
            case 1:
            {
                string w;
                cout<<"\n\nEnter the word to search for : ";
                cin>>w;
                cout<<"\n\n";
                D.getDetails(w);
                cin.ignore();
                Pause();
                break;
            }
            case 2:
            {
                string w,m = "",s = "",x = "";
                cout<<"\n\nEnter the word with right spelling : ";
                cin>>w;
                int res = 0;
                cout<<"\n\nDo you wish to enter the word's meaning - (1 for YES / 0 for NO) : ";
                cin>>res;
                if(res) {
                    cout<<"\n\nEnter the meaning : ";
                    cin.ignore();
                    getline(std::cin,m);
                }
                cout<<"\n\nDo you wish to enter the word's synonym - (1 for YES / 0 for NO) : ";
                cin>>res;
                if(res) {
                    cout<<"\n\nEnter the synonym : ";
                    cin.ignore();
                    getline(std::cin,s);
                }
                cout<<"\n\nDo you wish to enter the word's example - (1 for YES / 0 for NO) : ";
                cin>>res;
                if(res) {
                    cout<<"\n\nEnter the example : ";
                    cin.ignore();
                    getline(std::cin,x);
                }
                cout<<"\n\n";
                D.insert(w,m,s,x);
                cin.ignore();
                Pause();
                break;
            }
            case 3:
            {
                string w,m;
                cout<<"\n\nEnter the word for which you wish to enter the meaning : ";
                cin>>w;
                cout<<"\n\nEnter the meaning of the word : ";
                cin.ignore();
                getline(std::cin,m);
                D.setMeaning(w,m);
                cin.ignore();
                Pause();
                break;
            }
            case 4:
            {
                string w,s;
                cout<<"\n\nEnter the word for which you wish to enter the synonym : ";
                cin>>w;
                cout<<"\n\nEnter the synonym of the word : ";
                cin.ignore();
                getline(std::cin,s);
                D.setSynonym(w,s);
                cin.ignore();
                Pause();
                break;
            }
            case 5:
            {
                string w,x;
                cout<<"\n\nEnter the word for which you wish to enter the example : ";
                cin>>w;
                cout<<"\n\nEnter the example of the word : ";
                cin.ignore();
                getline(std::cin,x);
                D.setExample(w,x);
                cin.ignore();
                Pause();
                break;
            }
            case 6:
            {
                string w,m,s,x;
                cout<<"\n\nEnter the word for which you wish to enter the details : ";
                cin>>w;
                cout<<"\n\nEnter the meaning of the word : ";
                cin.ignore();
                getline(std::cin,m);
                cout<<"\n\nEnter the synonym of the word : ";
                cin.ignore();
                getline(std::cin,s);
                cout<<"\n\nEnter the example of the word : ";
                cin.ignore();
                getline(std::cin,x);
                D.setDetails(w,m,s,x);
                cin.ignore();
                Pause();
                break;
            }
            case 7:
            {
                string w;
                cout<<"\n\nEnter the word you wish to remove from the Dictionary : ";
                cin>>w;
                D.remove(w);
                cin.ignore();
                Pause();
                break;
            }
            case 8:
            {
                cout<<"\n\n";
                D.ListOut(1);
                cin.ignore();
                Pause();
                break;
            }
            default:{
                system("clear");
                cout<<"\n\n\n\t\t\tThank you for using the application!!\n\n";
                usleep(2000000);
                break;
            }
        }
    }
    system("clear");
    D.ListOut(2);
    return 0;
}
