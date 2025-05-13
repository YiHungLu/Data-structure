//10727153 呂宜鴻 10727155 曾博暉 
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;

struct College {
	int number ;
	int gNum ;
}; 

class BuildTree {
	string fileName  ;
	string fileNumber ;
	vector<College> aList ;
	vector<College> min ;
	vector<College> minmax ;
	
	void maxHeap( int cur, int cur2 ) {  //在min max heap中負責處理max heap的部分 
		College temp ;
		while ( minmax[cur].gNum > minmax[cur2].gNum  ) {
			temp = minmax[cur] ;
			minmax[cur] = minmax[cur2] ;
			minmax[cur2] = temp ;
			if ( cur2 == 1 || cur2 == 2 ) {
				break ;
			}
			cur = cur2 ;
			cur2 = ((( cur2 - 1 ) / 2 ) -1 ) / 2 ;
		} // while
		
	} // maxHeap()
	
	void minHeap( int cur, int cur2 ) {  //在min max heap中負責處理min heap的部分  
		College temp ;
		while ( minmax[cur].gNum < minmax[cur2].gNum  ) {
			temp = minmax[cur] ;
			minmax[cur] = minmax[cur2] ;
			minmax[cur2] = temp ;
			if ( cur2 == 0 ) {
				break ;
			}
			cur = cur2 ;
			cur2 = ((( cur2 - 1 ) / 2 ) -1 ) / 2 ;
		} // while
		
	} // minHeap()

	void Print( vector<College> tree ) {  // 印出答案 
		bool unfinish = true ;
		int i = 0 ;
		cout << "root: [" << tree[i].number << "] " << tree[i].gNum << "\n" ;
		i = tree.size() - 1 ;
		cout << "bottom: [" << tree[i].number << "] " << tree[i].gNum << "\n" ;
		i = 0 ;
		while ( unfinish ) {
			if ( i == tree.size()-1 ) {
				cout << "leftmost bottom: [" << tree[i].number << "] " << tree[i].gNum << "\n" ;
				unfinish = false ;
			}
			else if ( i > tree.size()-1 ) {
				i = ( i - 1 ) / 2 ;
				cout << "leftmost bottom: [" << tree[i].number << "] " << tree[i].gNum << "\n\n" ;
				unfinish = false ;
			}
			i = ( i * 2 ) + 1 ;
		} // while
	} // Print() 
	
	public:		
	
	bool Read(){           //讀檔 
		aList.clear() ;
		min.clear() ;
		minmax.clear() ;
		char ch ;
		int temp  = 0 ;
		int num = 0 ;
		int line = 0 ;
		int tab = 0 ;
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
				if ( ch == '\t' ) {
					tab++ ;
				}		
				if ( ch == '\n' ) {
					tab = 0 ;
				}	
				
				if ( tab == 8 ) {
					temp = 0 ;
					num++ ;
					fscanf(fPtr, "%c", &ch) ;
					while ( ch != '\t' ) {
						temp = ( temp*10 ) + ( ch - '0' ) ;
						fscanf(fPtr, "%c", &ch) ;
					} // while
					tab = 0 ;
					ct.gNum = temp ;
					ct.number = num ;
					aList.push_back(ct) ;
				}
			}
			return true ;
		}
		else {
			cout << "NO SUCH FILE!!!\n\n" ;
			return false ;
		}	
	} // Read()
	
	void minTree() {  // 負責建立 任務一 min heap 的樹 
		int i = 0 ;
		int cur2 = 0 ;
		int cur = 0 ;
		College temp ;
		while ( i < aList.size() ) {
			if ( ! min.empty() ) {
				min.push_back( aList[i] ) ;
				cur = i ;
				cur2 = ( i - 1 ) / 2 ;
				while ( min[cur].gNum < min[cur2].gNum  ) {
					temp = min[cur] ;
					min[cur] = min[cur2] ;
					min[cur2] = temp;
					if ( cur2 == 0 ) {
						break ;
					}
					cur = cur2 ;
					cur2 = ( cur2 - 1 ) / 2 ;					
				} // while
			}
			else {
				min.push_back( aList[i] ) ;
			}
			i++ ;
		}
		Print( min ) ;
	} // minTree()
	
	void minmaxTree() {  // 負責建立 任務二 min max heap 的樹 
		bool minn = true ;
		int i = 0 ;
		int gap = 1 ;
		int cur2 = 0 ;
		int cur = 0 ;
		College temp ;
		while ( i < aList.size() ) {
			if ( i == gap ) {
				gap = 2 * gap + 1 ;
				minn = !minn ;
			}
			if ( ! minmax.empty() ) {
				minmax.push_back( aList[i] ) ;
				cur = i ;
				cur2 = ( i - 1 ) / 2 ;
				if ( minn ) {
					if ( minmax[cur].gNum > minmax[cur2].gNum  ) {
						temp = minmax[cur] ;
						minmax[cur] = minmax[cur2] ;
						minmax[cur2] = temp;
						if ( cur2 != 1 && cur2 != 2 ) {
							cur = cur2 ;
							cur2 = ((( cur2 - 1 ) / 2 ) -1 ) / 2 ;
							maxHeap( cur, cur2 ) ;
						}		
					}
					else {
						cur2 = ( cur2 - 1 ) / 2 ;
						minHeap( cur, cur2 ) ;	
					}
				}
				else {
					if ( minmax[cur].gNum < minmax[cur2].gNum  ) {
						temp = minmax[cur] ;
						minmax[cur] = minmax[cur2] ;
						minmax[cur2] = temp;
						if ( cur2 != 0 ) {
							cur = cur2 ;
							cur2 = ((( cur2 - 1 ) / 2 ) -1 ) / 2 ;	
							minHeap( cur, cur2 ) ;	
						}		
					}
					else {
						cur2 = ( cur2 - 1 ) / 2 ;
						if ( cur2 != 0 ) {                                    
 							maxHeap( cur, cur2 ) ;	
 						}
					}	
				}
			}
			else {
				minmax.push_back( aList[i] ) ;
			}
			i++ ;
		}
		Print( minmax ) ;
	} // minmaxTree()

		
};

int main() {
	BuildTree tree ;
	int cmd ;
	cout<<endl<<"0. Quit"<<endl<<"1. min heap"<<endl<<"2. min max heap"<<endl<<"input a command(0,1,2) :" ;
	cin >> cmd ;
	while ( cmd != 0 ) {
		if ( cmd == 1 ) {
			if ( tree.Read() ) {
				tree.minTree() ;
			}
		}
		else if ( cmd == 2 ) {
			if ( tree.Read() ) {	
				tree.minmaxTree() ;
			}
		}

		cout<<endl<<"0. Quit"<<endl<<"1. min heap"<<endl<<"2. min max heap"<<endl<<"input a command(0,1,2) :" ;
		cin >> cmd ;
	}

} // main
