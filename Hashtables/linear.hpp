//Andrew Parker
//A hashtable implementing linear probing
#ifndef linear_hpp
#define linear_hpp

#include <vector>

class hashtable{

        public:
                hashtable();
                ~hashtable();
                void insert(int k);
                void erase(int);
                int bucket_count();
                double load();
                void rehash(int n);
                int *find(int k);
                int key_count();
                double _load();
                int _hash(int k);
                void _rehash(int n);

        private:
                int keycount;
                int tsize;
                std::vector<int > htable;
};

hashtable::hashtable(){
        tsize = 128;
        keycount = 0;
        std::vector<int> htable(tsize);
	for(int i = 0; i < tsize; i++)
	{
		htable[i] = -1;
	}
}

hashtable::~hashtable(){
        htable.clear();
}


void hashtable::insert(int k){
        int hashval = _hash(k);
        double l = _load();
	bool inserted = false;

        if(l < 0.75)
                _rehash(tsize *2);
	
	if(!inserted){
	while(hashval != tsize){
	if(htable[hashval] == -1 || htable[hashval] == -2)
        	{htable.insert(htable.begin()+hashval, k);
		keycount++;
		inserted = true;}
	else
		hashval++;
	}
	}	
	if(!inserted){
	int newval = 0;
	while(newval != tsize){
		if(htable[newval] == -1 || htable[newval] == -2) {
			htable.insert(htable.begin() + newval, k);
			keycount++;
			inserted = true;}
		else
			newval++;
			}
		}
	
}

int hashtable::_hash(int k){
        return k % tsize;
}

int hashtable::key_count(){
        return keycount;
}

int hashtable::bucket_count(){
        return tsize;
}

double hashtable::_load(){
        return keycount/tsize;
}

int *hashtable::find(int k){
        int* p = nullptr;
        int i = _hash(k) ;
        if(std::find(htable.begin(), htable.end()-1, k) != htable.end())
                return p;
        *p = i;
        return p;
}

void hashtable::_rehash(int n){
        if(n > tsize)
                htable.resize(tsize);
        else
                htable.resize(n);
}

void hashtable::erase(int k){
        int *i = find(k);
        htable[*i] = -2;
}

#endif


