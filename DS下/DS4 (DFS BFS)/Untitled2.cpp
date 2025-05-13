//10727153 §f©yÂE 10727155 ´¿³Õ·u 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <time.h>

using namespace std;

#define	MAX_LEN	10
struct Message {
    char sendid[MAX_LEN] ;
    char getid[MAX_LEN] ;
    float weight ;
};

struct List {
    string sendid ;
    string getid ;
    float weight ;
};

typedef struct gI {
    string id ;
    float weight ;
    gI *right ;
} getID ;

typedef struct mL {
    string id ;
    int num ;
    bool visited ;
    gI *right ;
} messageList ;


class Adjecency {
    vector<mL> mesList ;
    vector<mL> BFSvis ;
    vector<List> aList ;
    int nodes ;

    void MakeFile( string fileName ) {
        int i = 0 ;
        int k = 1 ;
        int num = 0 ;
        char str[2] ;
        string str2 ;
        FILE *fout = NULL;
        fout = fopen( fileName.c_str(), "w" ) ;
        gI *walk ;
        fprintf( fout,"<<< There are %d IDs in total. >>>\n", mesList.size() ) ;
        while ( i < mesList.size() ) {
            if ( i < 9 ) {
            	fprintf( fout,"[  %d] %s:\n", i+1, mesList[i].id.c_str() ) ;
			}
			else if ( i < 99 ) {
				fprintf( fout,"[ %d] %s:\n", i+1, mesList[i].id.c_str() ) ;
			}
			else {
				fprintf( fout,"[%d] %s:\n", i+1, mesList[i].id.c_str() ) ;
			}
            walk = mesList[i].right ;
            fprintf( fout,"\t" ) ;
            while ( walk != NULL ) {
                num++ ;
                sprintf( str, "%g", walk->weight ) ;
                str2 = str ;
                while ( str2.length() < 4 ) {
                	str2 = " " + str2 ;
				}
                if ( k < 10 ) {
                	fprintf( fout,"( %d) %s,¡@%s\t", k, walk->id.c_str(), str2.c_str() ) ;
				}
                else if ( k%10 == 0 ) {
                    fprintf( fout,"(%d) %s,¡@%s\n\t", k, walk->id.c_str(), str2.c_str() ) ;
                }
                else {
                    fprintf( fout,"(%d) %s,¡@%s\t", k, walk->id.c_str(), str2.c_str() ) ;
                }

                k++ ;
                walk = walk->right ;
            }
            fprintf( fout,"\n" ) ;
            k = 1 ;
            i++ ;
        }
        fprintf( fout,"<<< There are %d nodes in total. >>>\n", num ) ;
        nodes = mesList.size() ;
        fclose( fout ) ;
        
        cout << "\n<<< There are " << mesList.size() << " IDs in total. >>>\n\n" ;
        cout << "<<< There are " << num << " nodes in total. >>>\n\n" ;
    } // MakeFile()
    
    void MakeFile2( string fileName ) {
        int i = 0 ;
        int k = 1 ;
        int num = 0 ;
        FILE *fout = NULL;
        fout = fopen( fileName.c_str(), "w" ) ;
        gI *walk ;
        fprintf( fout,"<<< There are %d IDs in total. >>>\n", mesList.size() ) ;
        while ( i < BFSvis.size() ) {
            num++ ;
            if ( i < 9 ) {
            	fprintf( fout,"[  %d] %s(%d):\n", i+1, BFSvis[i].id.c_str(), BFSvis[i].num ) ;
			}
			else if ( i < 99 ) {
				fprintf( fout,"[ %d] %s(%d):\n", i+1, BFSvis[i].id.c_str(), BFSvis[i].num ) ;
			}
			else {
				fprintf( fout,"[%d] %s(%d):\n", i+1, BFSvis[i].id.c_str(), BFSvis[i].num ) ;
			}
            
            walk = BFSvis[i].right ;
            fprintf( fout,"\t" ) ;
            while ( walk != NULL ) {
                num++ ;
                if ( k < 10 ) {
                	if ( walk->id.length() < 8 ) {
                		fprintf( fout,"( %d) %s¡@\t", k, walk->id.c_str() ) ;
                		
					}
					else {
						fprintf( fout,"( %d) %s\t", k, walk->id.c_str() ) ;
					}
					
				}
                else if ( k%10 == 0 ) {
                	if ( walk->id.length() < 8 ) {
                		fprintf( fout,"(%d) %s¡@ \n\t", k, walk->id.c_str() ) ;
					}
					else {
						fprintf( fout,"(%d) %s¡@\n\t", k, walk->id.c_str() ) ;
					}
                }
                else {
                	if ( walk->id.length() < 8 ) {
                		fprintf( fout,"(%d) %s¡@\t", k, walk->id.c_str() ) ;
					}
					else {
						fprintf( fout,"(%d) %s\t", k, walk->id.c_str() ) ;
					}
    
                }

                k++ ;
                walk = walk->right ;
            }
            fprintf( fout,"\n" ) ;
            k = 1 ;
            i++ ;
        }
        fclose( fout ) ;
		
    } // MakeFile()

/*    void Print() {
        int i = 0 ;
        while ( i < aList.size() ) {
            cout << aList[i].sendid << '\t' << aList[i].getid << '\t' << aList[i].weight << '\n' ;
            i++ ;
        }
    }

    void Print2() {
    	int i = 0 ;
        while ( i < mesList.size() ) {
            cout << mesList[i].id << "\n" ;
            i++ ;
        }
    } */

    void VisSet( string id ) {
		int i = 0 ;
        while ( mesList[i].id != id ) {
            i++ ;
        }
        mesList[i].visited = true ;
    } // VisSet()

    int Findadr( string id ) {
        int i = 0 ;
        while ( mesList[i].id != id ) {
            i++ ;
        }
        return i ;
    } // VisSet()

    bool VisCheck( string id ) {
        int i = 0 ;
        while ( mesList[i].id != id ) {
            i++ ;
        }

        if ( ! mesList[i].visited ) {
            return true ;
        }
        else {
            return false ;
        }
    } // VisCheck()
    
    bool IDCheck( string id ) {
        int i = 0 ;
        while ( i < mesList.size() ) {
            if ( id == mesList[i].id ) {
            	return true ;
			}
			i++ ;
        }

		return false ;
    } // VisCheck()

    void Reset() {
        int i = 0 ;
        while ( i < mesList.size() ) {
            mesList[i].visited = false ;
            i++ ;
        }
    }

    void NodeInsert( int i, gI *temp, vector<mL> &List ) {
        gI *walk = List[i].right ;
        gI *last = NULL ;
        while ( walk != NULL ) {
            if ( temp->id > walk->id ) {
                last = walk ;
                walk = walk->right ;
            }
            else if ( temp->id < walk->id ) {
                if ( List[i].right->right == NULL || last == NULL ) {
                    List[i].right = temp ;
                    temp->right = walk ;
                }
                else {
                    last->right = temp ;
                    temp->right = walk ;
                }
                break ;
            }
        }

        if ( List[i].right == NULL ) {
            List[i].right = temp ;
        }
        else if ( walk == NULL ) {
            last->right = temp ;
        }

    } // NodeInsert()

    void Visit( gI *&walk, int i, int &k, vector<int> &queue ) {
        gI *temp ;
        while ( walk != NULL && k < nodes-1 ) {
            if ( VisCheck(walk->id) ) {
            	queue.push_back( Findadr( walk->id ) ) ;
                temp = new gI() ;
                temp->id = walk->id ;
                temp->right = NULL ;
                NodeInsert( i, temp, BFSvis ) ;
                VisSet( walk->id ) ;
                k++ ;

            }
            walk = walk->right ;
        }
    } // Visit()
    
    int IDInsert( mL temp ) {
		int i = 0 ;
    	while ( i < mesList.size() ) {
    		if ( temp.id > mesList[i].id ) {
    			i++ ;
			}
			else if ( temp.id == mesList[i].id ) {						
				return i ;
			}
			else if ( temp.id < mesList[i].id ) {
				mesList.insert( mesList.begin()+i, temp ) ;
				return i ;
			}
		}

		mesList.push_back( temp ) ;	
		return mesList.size()-1 ;	
	} // IDInsert()
	
	void Merge( vector<mL> &information, int first, int mid, int last ) { 
		int first1 = first ;
		int last1 = mid ;
	
		int first2 = mid+1 ;
		int last2 = last ;
	
		int i = 0 ;
		vector<mL> temp ;
		while ( (first1 <= last1) && (first2 <= last2) ) {
			if ( information[first1].num < information[first2].num ) {
				temp.push_back( information[first2] ) ;
				first2++ ;
			}
			else{
				temp.push_back( information[first1] ) ;
				first1++ ;			
			}
		} // while
	
		while ( first1 <= last1 ) {
			temp.push_back( information[first1] ) ;
			first1++ ;
		} // while
	
		while ( first2 <= last2 ) {
			temp.push_back( information[first2] ) ;
			first2++ ;
		} // while
	
	
		while ( first <= last ) {
			information[first] = temp[i] ;
			first++ ;
			i++ ;
		} // while
	
	} // Merge()

	void MergeSort( vector<mL> &information, int first, int last ) { 
		if ( first < last ) {
			int mid = ( first + last ) / 2 ;
			MergeSort( information, first, mid ) ;
			MergeSort( information, mid+1, last ) ;
			Merge( information, first, mid, last ) ;
		} // if
	
	}  // MergeSort()

	void Check() {
		int i = 0 ;
		mL temp ;
		gI *walk ;
		while ( i < mesList.size() ) {

			walk = mesList[i].right ;
			while ( walk != NULL ) {
				temp.id = walk->id ;
				temp.visited = false ;
				temp.right = NULL ;
				if ( ! IDCheck( temp.id ) ) {
					IDInsert( temp ) ;
				}
				walk = walk->right ;
			}
			
			i++ ;
		}
	} // Check()
	
public:
    void readBinary( string fileName ) {
        fstream binFile ;
        Message oneSt ;
        int stNo = 0 ;
        List temp ;

        binFile.open( ("pairs" + fileName + ".bin").c_str(), fstream::in | fstream::binary ) ;
        if ( binFile.is_open() ) {
            binFile.seekg( 0, binFile.end ) ;
            stNo = binFile.tellg() / sizeof( oneSt ) ;
            binFile.seekg( 0, binFile.beg ) ;

            for ( int i = 0; i < stNo; i++ ) {
                binFile.read( (char*) &oneSt, sizeof(oneSt) ) ;
                temp.sendid = oneSt.sendid ;
                temp.getid = oneSt.getid ;
                temp.weight = oneSt.weight ;
                aList.push_back( temp ) ;
            }
        }
        binFile.close() ;
    } // readBinary()

/*    void Build2( string fileName ) {
        int i = 0 ;
        string curid ;
        mL temp ;
        gI *walk ;

        while ( i < aList.size() ) {
        	temp.visited = false ;
        	temp.right = NULL ;
            temp.id = aList[i].sendid ;
            walk = temp.right ;
            while ( i < aList.size() && aList[i].sendid == temp.id ) {
                if ( walk == NULL ) {
                    temp.right = new gI() ;
                    walk = temp.right ;
                }
                else {
                    walk->right = new gI() ;
                    walk = walk->right ;
                }
                walk->right = NULL ;
                
                walk->id = aList[i].getid ;
                walk->weight = aList[i].weight ;
                i++ ;
            }
			
			mesList.push_back( temp ) ;
        }

		Check() ;
		MergeSort2( mesList, 0, mesList.size()-1 ) ;
        fileName = "pairs" + fileName + ".adj" ;
        MakeFile( fileName ) ;
    } // Build2() */
    
    void Build( string fileName ) {
    	int i = 0 ;
    	int k = 0 ;
        mL temp ;
        gI *walk ;
        while ( i < aList.size() ) {			
        	temp.visited = false ;
        	temp.right = NULL ;
        	temp.id = aList[i].sendid ;

            if ( mesList.empty() ) {
                walk = new gI() ;
                walk->right = NULL ;
                walk->id = aList[i].getid ;
                walk->weight = aList[i].weight ;
                temp.right = walk ;
                mesList.push_back( temp ) ;
            }
            else {
            	k = IDInsert( temp ) ;
            	walk = new gI() ;
            	walk->right = NULL ;
            	walk->id = aList[i].getid ;
            	walk->weight = aList[i].weight ;

				NodeInsert( k, walk, mesList ) ;
			}
			k = 0 ;		
        	i++ ; 
		}

		Check() ;
        fileName = "pairs" + fileName + ".adj" ;
        MakeFile( fileName ) ;
    } // Build2()

/*    void BFS2( string fileName ) {
        int i = 0 ;
        int k = 0 ;
        mL temp ;
        gI *cur2 = NULL ;
        gI *cur3 = NULL ;
        gI *cur4 = NULL ;
        gI *cur5 = NULL ;
        gI *cur6 = NULL ;
        gI *walk ;
        gI *BFwalk ;
        while ( i < mesList.size() ) {

            temp.id = mesList[i].id ;
            temp.right = NULL ;
            BFwalk = temp.right ;

            walk = Findadr( mesList[i].id ) ;

            Visit( walk, BFwalk, temp, k ) ;
            mesList[i].visited = true ;


            cur2 = mesList[i].right ;
            while ( cur2 != NULL && k < nodes-1 ) {

                walk = Findadr( cur2->id ) ;
                Visit( walk, BFwalk, temp, k ) ;
                cur2 = cur2->right ;

            }

            cur3 = mesList[i].right ;
            while ( cur3 != NULL && k < nodes-1  ) {

                cur2 = Findadr( cur3->id ) ;
                while ( cur2 != NULL && k < nodes-1 ) {
                	
                    walk = Findadr( cur2->id ) ;
                    Visit( walk, BFwalk, temp, k ) ;
                    cur2 = cur2->right ;
                }
                cur3 = cur3->right ;
            }
            
			cur4 = mesList[i].right ;
			while ( cur4 != NULL && k < nodes-1  ) {
				
           		cur3 = Findadr( cur4->id ) ;
            	while ( cur3 != NULL && k < nodes-1  ) {

              	  cur2 = Findadr( cur3->id ) ;
                	while ( cur2 != NULL && k < nodes-1 ) {
                	
                   		walk = Findadr( cur2->id ) ;
                   		Visit( walk, BFwalk, temp, k ) ;
                   		cur2 = cur2->right ;
                	}
                	cur3 = cur3->right ;
            	}
            	cur4 = cur4->right ;
            }
            
            cur5 = mesList[i].right ;
            while ( cur5 != NULL && k < nodes-1  ) {
            	
				cur4 = Findadr( cur5->id ) ;
				while ( cur4 != NULL && k < nodes-1  ) {
				
           			cur3 = Findadr( cur4->id ) ;
            		while ( cur3 != NULL && k < nodes-1  ) {

              		  cur2 = Findadr( cur3->id ) ;
                		while ( cur2 != NULL && k < nodes-1 ) {
                	
                   			walk = Findadr( cur2->id ) ;
                   			Visit( walk, BFwalk, temp, k ) ;
                	   		cur2 = cur2->right ;
                		}
                		cur3 = cur3->right ;
            		}
            		cur4 = cur4->right ;
            	}
            	cur5 = cur5->right ;
        	}

			cur6 = mesList[i].right ;
			while ( cur5 != NULL && k < nodes-1  ) {
				
            	cur5 = Findadr( cur6->id ) ;
            	while ( cur5 != NULL && k < nodes-1  ) {
            	
					cur4 = Findadr( cur5->id ) ;
					while ( cur4 != NULL && k < nodes-1  ) {
				
           				cur3 = Findadr( cur4->id ) ;
            			while ( cur3 != NULL && k < nodes-1  ) {

              		 	 cur2 = Findadr( cur3->id ) ;
                			while ( cur2 != NULL && k < nodes-1 ) {               	
                   				walk = Findadr( cur2->id ) ;
                   				Visit( walk, BFwalk, temp, k ) ;
                	   			cur2 = cur2->right ;
                			}
                			cur3 = cur3->right ;
            			}
            			cur4 = cur4->right ;
            		}
            		cur5 = cur5->right ;
        		}
        		cur6 = cur6->right ;
        	}
			
			temp.num = k ;
			BFSvis.push_back( temp ) ;
            Reset() ;
            k = 0 ;
            i++ ;
        }
		
		
		MergeSort( BFSvis, 0, BFSvis.size()-1 ) ;
        fileName = "pairs" + fileName + ".cnt" ;
        MakeFile2( fileName ) ;
    } // BFS2() */
    
    void BFS( string fileName ) {
    	vector<int> queue ;
    	int i = 0 ;
    	int k = 0 ;
    	gI *walk ;
    	mL temp ;
    	
    	while ( i < mesList.size() ) {
    		
    		temp.id = mesList[i].id ;
    		temp.right = NULL ;
    		BFSvis.push_back( temp ) ;
    		
    		mesList[i].visited = true ;
    		
    		walk = mesList[i].right ;
    		Visit( walk, i, k, queue ) ;
    		
    		while ( queue.size() != 0 && k < nodes-1 ) { 
				walk = mesList[queue[0]].right ; 			
    			Visit( walk, i, k, queue ) ;
    			queue.erase( queue.begin() ) ;
			}
			
			BFSvis[i].num = k ;
			Reset() ;
			k = 0 ;
			i++ ;
		}
		
		MergeSort( BFSvis, 0, BFSvis.size()-1 ) ;
        fileName = "pairs" + fileName + ".cnt" ;
        MakeFile2( fileName ) ;
    	  	
    } // BFS()

};


int main() {
    Adjecency Adjecency ;
    string fileName ;
    cout << "Input a file number : " ;
    cin >> fileName ;
    
	Adjecency.readBinary( fileName ) ;
   	Adjecency.Build( fileName ) ; 
	Adjecency.BFS( fileName ) ; 
	cout<<"123";

} // main()
