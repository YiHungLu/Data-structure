//10727153 呂宜鴻 10727155 曾博暉 
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;

struct twthrtree {
	vector<int> firlist ;
	vector<int> seclist ;
	string first ;
	string second ;
	twthrtree *pre ;
	twthrtree *left ;
	twthrtree *right ;
	twthrtree *middle ;
};

struct College {
	int number ;
	string name ;
	string information ;
}; 

typedef twthrtree* ttTree ;

class BuildTree {
	string fileName  ;
	string fileNumber ;
	ttTree tttree ;
	vector<College> aList ;
	
	void Print2() {
		int i = 0 ;
		while ( i < aList.size() ) {
			cout << aList[i].information << '\n' ;
			i++ ;
		} // while
	} // Print()

	void Print( ttTree tree ) {
		int index = 1 ;
		int i = 0 ;
		vector<int> num = tree->firlist ;
		while ( i < num.size() ) {
			cout << index << ": " << "[" << num[i]  << "]" << " " ;
			cout << aList[num[i]-1].information << '\n' ;
			index++ ;
			i++ ;
		} // while
		
		if ( tree->second != "XXX" ) {
			i = 0 ;
			vector<int> num = tree->seclist ;
			while ( i < num.size() ) {
				cout << index << ": " << "[" << num[i]  << "]" << " " ;
				cout << aList[num[i]-1].information << '\n' ;
				index++ ;
				i++ ;
			} // while
		}
		
	} // Print()	
	
	
	void Cut( string chs, College &ct ) {
		ct.name = "" ;
		ct.information = "" ;
		string temp ;
		int i = 0 ;
		int tab = 0 ;
		while ( chs[i] != '\n' ) {
			if ( chs[i] == '\t' ) {
				tab++ ;
			}
			
			if ( tab == 1 ) {
				i++ ;
				while ( chs[i] != '\t' ) {
					ct.name = ct.name + chs[i] ;
					i++ ;
				} // while	
				ct.information = ct.name + ", " ;
				tab++ ;
			}
			else if ( tab == 3 ) {
				i++ ;
				while ( tab != 6 ) {
					
					if ( chs[i] == '\t' ) {
						tab++ ;
						ct.information = ct.information + ", " ;
					}
					else {
						ct.information = ct.information + chs[i] ;
					}
					
					i++ ;
				} // while					
			}
			else if ( tab == 8 ) {
				i++ ;
				while ( chs[i] != '\t' ) {
					ct.information = ct.information + chs[i] ;
					i++ ;
				} // while	
				break ;			
			}		
			i++ ;	
		}	
			
	} // Cut()
	
	ttTree Set( ttTree previous ) {
		ttTree tree ;
		tree = new twthrtree() ;
		tree->first = "XXX" ;
		tree->second = "XXX" ;
		tree->left = NULL ;
		tree->middle = NULL ;
		tree->right = NULL ;
		tree->pre = previous ;
		return tree ;
	} // Set()
	
	int Counthigh( ttTree tree ) {
		int height = 0 ;
		while ( tree != NULL ) {
			height++ ;
			tree = tree->left ;
		}
		return height ;
	} // Counthigh()
	
	int Countnode( ttTree tree ) {
		if ( tree != NULL ) {
			return 1 + Countnode( tree->left ) + Countnode( tree->right ) + Countnode( tree->middle ) ;
		}
		else {
			return 0 ;
		}

	} // Countnode()
	
	public:	
	
	
	bool Read(){           //讀檔 
		char ch ;
		string temp ;
		string chs ;
		int num = 1 ;
		int line = 0 ;
		College ct ;
		
		cout<<endl<<"FileNumber : " ;		
		cin>>fileNumber ;
		fileName = "input" + fileNumber + ".txt" ;
		
		FILE *fPtr = NULL ;
		fPtr=fopen(fileName.c_str(),"r");
		
		if ( fPtr != NULL ) {
			while ( line < 3 ) {
				fscanf(fPtr, "%c", &ch) ;
				if ( ch == '\n' ) {
					line++ ;
				}
			}
			
			while ( fscanf(fPtr, "%c", &ch)!=EOF ) {
				if ( ch != '\n' ) {
					temp = ch ;
					chs = chs + temp ;
				}
				else {
					ct.number = num ;
					Cut( chs, ct ) ;
					aList.push_back( ct ) ;
					num++ ;
					chs = "" ;
				}
			}
			ct.number = num ;
			Cut( chs, ct ) ;
			aList.push_back( ct ) ;
			return true ;
		}
		else {
			cout << "NO SUCH FILE!!!\n\n" ;
			return false ;
		}	
	} // Read()
	
	void MissionOne() {
		bool same = true ;
		int i = 0 ;
		vector<int> numlist ;
		vector<int> temp ;
		string temp2 ;
		ttTree cur ;
		ttTree limit = NULL ;
		cur = NULL ;
		while ( i < aList.size() ) {
			if ( cur == NULL ) {
				tttree = Set( NULL ) ;
				tttree->first = aList[i].name ;
				tttree->firlist.push_back( aList[i].number ) ;
			}
			else {
				while ( cur->left != NULL || cur->right != NULL || cur->middle != NULL ) {
					if ( aList[i].name == cur->first ) {
						cur->firlist.push_back( aList[i].number ) ;
						same = false ;
						break ;
					}
					else if ( aList[i].name == cur->second ) {
						cur->seclist.push_back( aList[i].number ) ;
						same = false ;
						break ;
					}
					else if ( cur->first != "XXX" && cur->second != "XXX" ) {
						if ( aList[i].name < cur->first ) {
							cur = cur->left ;
						}
						else if ( aList[i].name < cur->second ) {
							cur = cur->middle ;
						}
						else if ( aList[i].name > cur->second ) {
							cur = cur->right ;
						}
					}
					else if ( cur->first != "XXX" && cur->second == "XXX" ) {
						if ( aList[i].name < cur->first ) {
							cur = cur->left ;
						}
						else if ( aList[i].name > cur->first ) {
							cur = cur->right ;
						}
					}
				}
				if ( same ) {
					if ( aList[i].name == cur->first ) {
						cur->firlist.push_back( aList[i].number ) ;
					}
					else if ( aList[i].name == cur->second ) {
						cur->seclist.push_back( aList[i].number ) ;
					}
					else if ( cur->first != "XXX" && cur->second == "XXX" ) {
						if ( aList[i].name < cur->first ) {
							cur->second = cur->first ;
							cur->seclist = cur->firlist ;
							cur->first = aList[i].name ;
							cur->firlist.clear() ;
							cur->firlist.push_back( aList[i].number ) ;
						}
						else if ( aList[i].name > cur->first ) {
							cur->second = aList[i].name ;
							cur->seclist.push_back( aList[i].number ) ;
						}
					}
					else if ( cur->first != "XXX" && cur->second != "XXX" ) {
						numlist.push_back( aList[i].number ) ;
						Spilt( cur, aList[i].name, numlist, temp, temp2, limit ) ;
						Distribute( temp, temp2, cur, limit ) ;
					} 
				}
					
			}
			same = true ;
			numlist.clear() ;
			temp.clear() ;
			temp2 = "" ;
			limit = NULL ;
			cur = tttree ;
			i++ ;
		}
		
		cout << "Tree Height: " << Counthigh( tttree ) << '\n' ;
		cout << "Number Of Nodes: " << Countnode( tttree ) << '\n' ;
		Print( tttree ) ;
	} // MissionOne()
	
	void Distribute( vector<int> num, string name, ttTree cur, ttTree limit ) {
		twthrtree* temp1 = NULL ;	
		twthrtree* temp2 = NULL ;	
		twthrtree* temp3 = NULL ;	
		twthrtree* temp4 = NULL ;			//用來存分裂的四個點 
		
		twthrtree* tf1 = Set( NULL ) ;
		tf1->first = cur->first ;
		tf1->firlist = cur->firlist ;
		twthrtree* tf2 = Set( NULL ) ;		//用來存父親節點分裂成的兩個點 
		tf2->first = cur->second ;
		tf2->firlist = cur->seclist ;
		twthrtree* father = NULL ;		
		father = cur->pre ;
		while ( father != limit ) {
			if ( cur->second > father->second ) {		//分裂的點在右邊 
				temp1 = father->left ;
				temp2 = father->middle ;
				temp3 = tf1 ;
				temp4 = tf2 ;
			}
			else if ( cur->first < father->first ) {	//分裂的點在左邊 
				temp4 = father->right ;
				temp3 = father->middle ;
				temp1 = tf1 ;
				temp2 = tf2 ;
			}
			else if ( cur->first > father->first && cur->second < father->second ) {	//分裂的點在中間 
				temp1 = father->left ;
				temp4 = father->right ;
				temp2 = tf1 ;
				temp3 = tf2 ;
			}
			tf1 = Set( NULL ) ;
			tf2 = Set( NULL ) ;
			tf1->first = father->first ;
			tf1->firlist = father->firlist ;
			tf1->left = temp1 ;
			tf1->right = temp2 ;
			temp1->pre = tf1 ;
			temp2->pre = tf1 ;
			tf2->first = father->second ;
			tf2->firlist = father->seclist ;
			tf2->left = temp3 ;
			tf2->right = temp4 ;
			temp3->pre = tf2 ;
			temp4->pre = tf2 ;
			
			cur = cur->pre ;		//繼續往上 
			father = cur->pre ;
		}
		
		if ( limit != NULL ) {
			if ( tf2->first > limit->second ) {
				limit->right = tf2 ;
				limit->middle = tf1 ;
				tf2->pre = limit ;
				tf1->pre = limit ;
			}
			else if ( tf1->first < limit->first ) {
				limit->left = tf1 ;
				limit->middle = tf2 ;
				tf2->pre = limit ;
				tf1->pre = limit ;
			}
		}
		else {
			tttree = Set( NULL ) ;  //創新的根把新的樹接上 
			tttree->first = name ;
			tttree->firlist = num ;
			tttree->left = tf1 ;
			tf1->pre = tttree ;
			tttree->right = tf2 ;
			tf2->pre = tttree ;
		}
		
	} // Distribute()
	
	
	void Spilt( ttTree &cur, string name, vector<int> num, vector<int> &temp, string &temp2, ttTree &limit ) {
		if ( cur->first != "XXX" && cur->second == "XXX" ) {
			if ( cur->first < name ) {
				cur->second = name ;
				cur->seclist = num ;
			}
			else {
				cur->second = cur->first ;
				cur->seclist = cur->firlist ;
				cur->first = name ;
				cur->firlist = num ;
			}	
			limit = cur ;
		}
		else if ( cur->first != "XXX" && cur->second != "XXX" ) {
			if ( name < cur->first ) {
				temp2 = cur->first ;
				temp = cur->firlist ;
				cur->first = name ;
				cur->firlist = num ;
				name = temp2 ;
				num = temp ;
			}
			else if ( name > cur->second ) {
				temp2 = cur->second ;
				temp = cur->seclist ;
				cur->second = name ;
				cur->seclist = num ;
				name = temp2 ;
				num = temp ;
			}
			else {
				temp2 = name ;
				temp = num ;
			}
			
			if ( cur->pre != NULL ) {
				Spilt( cur->pre, name, num, temp, temp2, limit ) ;
			}
		}
	} // Spilt()
	

};

int main() {
	BuildTree tree ;
	tree.Read() ;
	tree.MissionOne() ;
} // main
