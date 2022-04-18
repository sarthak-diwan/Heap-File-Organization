#include <bits/stdc++.h>
#define INT_SIZE 4

using namespace std;



class Page{
    public:
    int max_size;
    int free_space;

    // Stored at end
    int free_address;
    Page * prev;
    Page * next;
    int record_count;
    vector<int> slots;
    map<int, int> directory;

    Page(int s){
        max_size = s;
        prev = NULL;
        next = NULL;
        free_address = 0;
        record_count = 0;
        free_space = max_size - 4*INT_SIZE;
    }

    int insert(int record_size, int value){
        if(record_size + INT_SIZE <= free_space){
            directory[value] = free_address;
            slots.push_back(value);
            free_address += record_size;
            free_space -= record_size + INT_SIZE;
            return 1;
        }else{
            return 0;
        }
    }

    int search(int value){
        auto it = directory.find(value);
        if(it != directory.end()){
            for(int i=0; i<slots.size(); i++){
                if(slots[i] == value){
                    return i;
                }
            }
            // return it->second;
        }
        return -1;
    }

};

class Heap{
    public:
    vector<Page *> pages;
    int page_size;
    Heap(int size){
        page_size = size;
    }

    void status(){
        cout << pages.size() << " ";
        for(auto page: pages){
            cout << page->directory.size() << " ";
        }
        cout << endl;
    }
    void insert(int s, int v){
        bool inserted = false;
        for(auto page: pages){
            if(page->insert(s, v)){
                inserted = true;
                break;
            };
        }
        if(!inserted){
            pages.push_back(new Page(page_size));
            pages.back()->insert(s, v);
        }
    }

    void search(int v){
        for(int i=0;i< pages.size(); i++){
            int res = pages[i]->search(v);
            if(res != -1){
                cout <<  i << " " << res << endl;
                return;
            }
        }
        cout << "-1 -1" << endl;
    }
};

int main(){
    int ps;
    cin >> ps;
    Heap h = Heap(ps);
    while(true){
        int x;
        cin >> x;
        if(x == 2){
            h.status();
        }
        else if(x == 1){
            int s, v;
            cin >> s >> v;
            h.insert(s,v);
        }else if(x == 3){
            int v;
            cin >> v;
            h.search(v);
        }else if(x == 4){
            break;
        }
    }
    return 0;
}

