#include<iostream>
#include<iterator>
#include<map>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
class DB {
        string dbstore = "ssdb.kvstore";
	map<string,string> db;
	public:
	        void init_db();
		void insert(string key, string value);
		void dumpDB();
		~DB() {
			ofstream file(dbstore);
			if(file.is_open()){
				map<string, string>::iterator iter;
				for(iter = db.begin(); iter != db.end(); iter++) {
					file << iter->first << " " << iter->second << "\n";
				}
				file.close();


			}else {
				cout << "Corrupted database, error propagated from write operation in dusctortor" << endl;
			}


		}

};
//parse strings to key val pairs
//populate db
void DB::insert(string key, string value){
	db[key] = value;
}
void DB::dumpDB() {
	map<string, string>::iterator itr;
	for(itr=db.begin(); itr != db.end(); itr++) {
		cout << "Key: " << itr ->first << "\t" << "Value: " << itr->second << endl;
	}
}

void DB::init_db() {
	string line;
	deque<string> queue;
	ifstream file(dbstore);
	if(file.is_open()){
		while(!file.eof()) {
			while(getline (file, line)){
			stringstream ss(line);
			string s;
			while(getline(ss, s, ' ')) {
				queue.push_back(s);
			}
			string key = queue.at(0);
			string val = queue.at(1);
			db[key] = val;
			//clear queue
			queue.pop_front();
			queue.pop_front();
		}
		}
		file.close();
	}else {
		ofstream outfile("ssdb.kvstore");
		outfile.close();
		init_db();
	}
}
int main(int argc, char** argv) {
	DB db;
	db.init_db();
	db.insert(argv[1], argv[2]);
	db.dumpDB();
}
