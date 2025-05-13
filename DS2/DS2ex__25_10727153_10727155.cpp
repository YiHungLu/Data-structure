// 10727153 �f�y�E 10727155 ���շu 
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

 
using namespace std;

struct Maze {
	char step ;  // �Ҧb��m��E�BO�BG 
	bool visited ;  // �O�_���L 
	char laststep ; // �e�@�B�Ҩ�����V 
	int otheroads ; // ���X�إi������V 
	bool right ; // �O�_����X�f�g�L�� 
	bool foundg ; // �O�_�����G 
};

void InputFile(Maze **maze, int line, int column,	FILE *fPtr){  //�B�zŪ�� 


	
	char temp ;
	int i = 0 ;
	int j = 0 ;
	fscanf(fPtr, " %c", &temp) ;	



	do {  
		if(temp!=' '){			
			if(temp!='\n') {
				maze[j][i].step = temp ;
				i++ ;
			}
			else{
				j++ ;
				i=0 ;
			}
		}

	} while(fscanf(fPtr, "%c", &temp) != EOF) ;
	
	fclose(fPtr);
	
	
	
}

void Initialize( Maze **maze, int nowline, int nowcolumn, int column, int line ) {  //��l�ƤG���}�C 
	while ( nowline < line ) {
		while ( nowcolumn < column ) {
			if ( nowline == 0 && nowcolumn == 0 )
				maze[nowline][nowcolumn+1].laststep = 'R' ;
			maze[nowline][nowcolumn].visited = false ;
			maze[nowline][nowcolumn].otheroads = 0 ;
			maze[nowline][nowcolumn].right = false ;
			nowcolumn++ ;
		} // while
		nowline++ ;
		nowcolumn = 0 ;
	} // while
} // Initialize()

void PutWrong( Maze **maze, int &nowline, int &nowcolumn, int column, int line ) { //���즺���᪺�B�z (���Ȥ@) 
	while ( maze[nowline][nowcolumn].otheroads == 0 ) {                            // �h��e�@�Ӧ��ø�����m 
        maze[nowline][nowcolumn].right = false ;  //�N�o�Ӧ�m�]���D���T�� 
		if ( maze[nowline][nowcolumn].laststep == 'R' )
			nowcolumn-- ;
		else if ( maze[nowline][nowcolumn].laststep == 'L' )
			nowcolumn++ ;
		else if ( maze[nowline][nowcolumn].laststep == 'U' )
			nowline++ ;		
		else if ( maze[nowline][nowcolumn].laststep == 'D' )
			nowline-- ;
	} // while
    maze[nowline][nowcolumn].otheroads =0 ; 
} // PutWrong()

bool AnyOtherRoads( Maze **maze, int nowline, int nowcolumn, int column, int line ) {  //���X�ӥi������V 
	if ( maze[nowline][nowcolumn].laststep == 'R' ) { //�e�@�B���V�k�A�ˬd�k�B�W�B�U�O�_���Ů� 
		
		if (  nowline < line-1 && maze[nowline+1][nowcolumn].step != 'O' && ! maze[nowline+1][nowcolumn].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowline > 0 && maze[nowline-1][nowcolumn].step != 'O' && ! maze[nowline-1][nowcolumn].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowcolumn < column-1 && maze[nowline][nowcolumn+1].step != 'O' && ! maze[nowline][nowcolumn+1].visited )
			maze[nowline][nowcolumn].otheroads++ ;		
			
	} // if
	else if ( maze[nowline][nowcolumn].laststep == 'L' ) {
		
		if (  nowline < line-1 && maze[nowline+1][nowcolumn].step != 'O' && ! maze[nowline+1][nowcolumn].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowline > 0 && maze[nowline-1][nowcolumn].step != 'O' && ! maze[nowline-1][nowcolumn].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowcolumn > 0 && maze[nowline][nowcolumn-1].step != 'O' && ! maze[nowline][nowcolumn-1].visited )
			maze[nowline][nowcolumn].otheroads++ ;	
			
	} // if
	else if ( maze[nowline][nowcolumn].laststep == 'U' ) {
		
		if (  nowline > 0 && maze[nowline-1][nowcolumn].step != 'O' && ! maze[nowline-1][nowcolumn].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowcolumn > 0 && maze[nowline][nowcolumn-1].step != 'O' && ! maze[nowline][nowcolumn-1].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowcolumn < column-1 && maze[nowline][nowcolumn+1].step != 'O' && ! maze[nowline][nowcolumn+1].visited )
			maze[nowline][nowcolumn].otheroads++ ;
			
	} // if
	else if ( maze[nowline][nowcolumn].laststep == 'D' ) {
		
		if (  nowline < line-1 && maze[nowline+1][nowcolumn].step != 'O' && ! maze[nowline+1][nowcolumn].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowcolumn > 0 && maze[nowline][nowcolumn-1].step != 'O' && ! maze[nowline][nowcolumn-1].visited )
			maze[nowline][nowcolumn].otheroads++ ;
		if (  nowcolumn < column-1 && maze[nowline][nowcolumn+1].step != 'O' && ! maze[nowline][nowcolumn+1].visited )
			maze[nowline][nowcolumn].otheroads++ ;	
			
	} // if
	
} // AnyOtherRoads()

bool Walk( Maze **maze, int nowline, int nowcolumn, int column, int line ) { //�B�z���Ȥ@���g�c 
    Maze *p[50] ;
	while ( nowline < line ) {
		p[nowline] = maze[nowline] ;
		nowline++ ;
	} // while
    nowline = 0 ;
	while ( maze[nowline][nowcolumn].step != 'G' ) {
        maze[nowline][nowcolumn].right = true ;   
		AnyOtherRoads( p, nowline, nowcolumn, column, line ) ;
		maze[nowline][nowcolumn].visited = true ;
		
		if ( nowcolumn != column-1 && maze[nowline][nowcolumn+1].step != 'O' && maze[nowline][nowcolumn].laststep != 'L' && ! maze[nowline][nowcolumn+1].visited ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowcolumn++ ;
			maze[nowline][nowcolumn].laststep = 'R' ;
		} // if
		else if ( nowline != line-1 && maze[nowline+1][nowcolumn].step != 'O' && maze[nowline][nowcolumn].laststep != 'U' && ! maze[nowline+1][nowcolumn].visited ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowline++ ;
			maze[nowline][nowcolumn].laststep = 'D' ;
		} // if
		else if ( nowcolumn != 0 && maze[nowline][nowcolumn-1].step != 'O' && maze[nowline][nowcolumn].laststep != 'R' && ! maze[nowline][nowcolumn-1].visited ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowcolumn-- ;
			maze[nowline][nowcolumn].laststep = 'L' ;
		} // if
		else if ( nowline != 0 && maze[nowline-1][nowcolumn].step != 'O' && maze[nowline][nowcolumn].laststep != 'D' && ! maze[nowline-1][nowcolumn].visited ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowline-- ;
			maze[nowline][nowcolumn].laststep = 'U' ;
		} // if
		else if ( nowline == 0 && nowcolumn == 0 && maze[nowline][nowcolumn].otheroads == 0 )
			return false ;
		else 
			PutWrong( p, nowline, nowcolumn, column, line ) ; // �L���i����h�^�h 

			
	} // while 
	return true ;
	
}

void PrintVisit( Maze **maze, int nowline, int nowcolumn, int column, int line ) {  // �L�X�Ҩ��L�����| 
	
	cout << '\n' ;
	while ( nowline < line ) {
		while ( nowcolumn < column ){
			if ( maze[nowline][nowcolumn].visited )
				if(maze[nowline][nowcolumn].step=='G')
					cout<<'G' ;
				else 
					cout << 'V' ;
			else
				cout << maze[nowline][nowcolumn].step ;
			
			nowcolumn++ ;
		}
		cout << '\n' ;
		nowcolumn = 0 ;
		nowline++ ;
	}
	
} // PrintVisit()

void PrintRight( Maze **maze, int nowline, int nowcolumn, int column, int line ) {  // �L�X���T�����| 
	
	cout << '\n' ;
	while ( nowline < line ) {
		while ( nowcolumn < column ){
			if ( maze[nowline][nowcolumn].right ){
				if(maze[nowline][nowcolumn].step=='G')
					cout<<'G' ;
				else
					cout << 'R' ;
			}
			else
				cout << maze[nowline][nowcolumn].step ;
			
			nowcolumn++ ;
		}
		cout << '\n' ;
		nowcolumn = 0 ;
		nowline++ ;
	}
	
} // PrintRight()

void PutWrongMissionTwo( Maze **maze, int &nowline, int &nowcolumn, int column, int line ) {  //���즺���᪺�B�z (���ȤG) 
	bool findg = false ;                                                                    // �h��e�@�Ӧ��ø�����m 
	while ( maze[nowline][nowcolumn].otheroads == 0 ) {
		if ( maze[nowline][nowcolumn].step == 'G' || maze[nowline][nowcolumn].foundg ) // �ˬd�o�����|�O�_���g�LG  
			findg = true ;
    
		if ( ! findg )  
        	maze[nowline][nowcolumn].right = false ;
        else
         	maze[nowline][nowcolumn].foundg = true ;
         	
		if ( maze[nowline][nowcolumn].laststep == 'R' )
			nowcolumn-- ;
		else if ( maze[nowline][nowcolumn].laststep == 'L' )
			nowcolumn++ ;
		else if ( maze[nowline][nowcolumn].laststep == 'U' )
			nowline++ ;		
		else if ( maze[nowline][nowcolumn].laststep == 'D' )
			nowline-- ;
		
         	
	} // while
  
    if ( ! findg )
        maze[nowline][nowcolumn].right = false ;
    else
        maze[nowline][nowcolumn].foundg = true ;
  
    maze[nowline][nowcolumn].otheroads = 0 ;
} // PutWrongMissoinTwo()

bool WalkMissionTwo( int goal, Maze **maze, int nowline, int nowcolumn, int column, int line ) { //�B�z���ȤG���g�c
    int count = 0 ;  // �p��g�L�X��G 
    Maze *p[50] ;
	while ( nowline < line ) {
		p[nowline] = maze[nowline] ;
		nowline++ ;
	} // while
    nowline = 0 ;
	while ( count < goal ) {
        maze[nowline][nowcolumn].right = true ;
		AnyOtherRoads( p, nowline, nowcolumn, column, line ) ;
		maze[nowline][nowcolumn].visited = true ;
		
		if ( nowcolumn != column-1 && maze[nowline][nowcolumn+1].step != 'O' && maze[nowline][nowcolumn].laststep != 'L' && ! maze[nowline][nowcolumn+1].visited ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowcolumn++ ;
			maze[nowline][nowcolumn].laststep = 'R' ;
		} // if
		else if ( nowline != line-1 && maze[nowline+1][nowcolumn].step != 'O' && maze[nowline][nowcolumn].laststep != 'U' && ! maze[nowline+1][nowcolumn].visited ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowline++ ;
			maze[nowline][nowcolumn].laststep = 'D' ;
		} // if
		else if ( nowcolumn != 0 && maze[nowline][nowcolumn-1].step != 'O' && maze[nowline][nowcolumn].laststep != 'R' && ! maze[nowline][nowcolumn-1].visited ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowcolumn-- ;
			maze[nowline][nowcolumn].laststep = 'L' ;
		} // if
		else if ( nowline != 0 && maze[nowline-1][nowcolumn].step != 'O' && maze[nowline][nowcolumn].laststep != 'D' && ! maze[nowline-1][nowcolumn].visited ) {
			maze[nowline][nowcolumn].otheroads-- ;
			nowline-- ;
			maze[nowline][nowcolumn].laststep = 'U' ;
		} // if
		else if ( nowline == 0 && nowcolumn == 0 && maze[nowline][nowcolumn].otheroads == 0 )
			return false ;
		else 
			PutWrongMissionTwo( p, nowline, nowcolumn, column, line ) ;
			
		if ( maze[nowline][nowcolumn].step == 'G' && maze[nowline][nowcolumn].visited==false ) {
			count++ ;
		}
			
	} // while
	return true ;
}

int main() {
    Maze maze[50][50];
    Maze *p[50] ;
	int line = 0 ;
	int column = 0 ;
	int nowline = 0 ;
	int nowcolumn = 0 ;
	bool success = false ;
	string fileName ;
	string fileNumber ;
	
	int input ;
	cout<<"0 : Quit" << endl << "1 : one goal" << endl << "2 : more goal" << endl ;
	cin>> input ;
	while(input!=0&&input!=1&&input!=2) {
		cout<<endl<<"0 : " << endl; 
		cin>> input ;
	}
	
	while(input!=0){		
		cout << "FileNumber(201,202...) : " << endl ;   
		cin >> fileNumber ;                       // ��J�nŪ���ɮצW��
		fileName = "input" + fileNumber + ".txt" ;
		FILE *fPtr = NULL;
		fPtr=fopen(fileName.c_str(),"r");
		if(fPtr==NULL)
			cout<<"ERROR FILE"<<endl ;
		else{		
			fscanf(fPtr, "%d", &column) ;
			fscanf(fPtr, "%d", &line) ;

				while ( nowline < line ) {
				p[nowline] = maze[nowline] ;
				nowline++ ;
			} // while
	
			nowline = 0 ;

	
			InputFile( p, column, line ,fPtr ) ;
			Initialize( p, nowline, nowcolumn, column, line ) ;
			if(input==1)
				success = Walk( p, nowline, nowcolumn, column, line ) ;
			else if(input==2) {
				int goal = 0 ;
				cout << "goal : "<<endl ;
				cin >> goal ;	
				success = WalkMissionTwo( goal, p, nowline, nowcolumn, column, line ) ;
			}
			PrintVisit( p, nowline, nowcolumn, column, line ) ;
			if ( success )
				PrintRight( p, nowline, nowcolumn, column, line ) ;
			
			cout<<"0 : Quit" << endl << "1 : one goal" << endl << "2 : more goal" << endl ;
			
			cin>> input ;
			while(input!=0&&input!=1&&input!=2) {
				cout<<"0 : Quit" << endl << "1 : one goal" << endl << "2 : more goal" << endl ;
				cin>> input ;
			}
		}
	}
	
} // Main


	









