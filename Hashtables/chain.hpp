//Andrew Parker
#ifndef chain_hpp
#define chain_hpp

#include <list>
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
		std::vector<std::list<int> > htable;
};

hashtable::hashtable(){
	tsize = 128;
	keycount = 0;
	std::vector<std::list<int>> htable(tsize);
}

hashtable::~hashtable(){
	for(int i = 0; i < tsize; i++){
		std::list<int> & ilist = htable[i];
		while(!ilist.empty())	
		ilist.pop_back();
		}
	htable.clear();
}


void hashtable::insert(int k){
	int hashval = _hash(k);
	double l = _load();
	if(l < 0.75)
		_rehash(tsize *2);
	std::list<int> & ilist = htable[hashval];
	ilist.push_back(k);
	keycount++;	
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
	int i = _hash(k);
	std::list<int> & ilist = htable[i];
	if(std::find(ilist.begin(), ilist.end(), k) != ilist.end())
		return p;
	*p = i;
	return p;
}

void hashtable::_rehash(int n){
	if(n < tsize)
		htable.resize(tsize);
	else
		htable.resize(n);
}

void hashtable::erase(int k){
	int *i = find(k);
	std::list<int> & ilist = htable[*i];
	ilist.remove(k);
}

#endif
