#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
enum Type {
	OPEN_PARENTHESES = 31, CLOSE_PARENTHESES = 32, OPERATOR = 2, NUMBER = 1, ERROR = 0 
};

enum ErrorType{
	ERROR_CHARACTER = 1,
	EXTRA_OPEN_PARENTHESIS = 21,
	EXTRA_CLOSE_PARENTHESIS = 22,
	EXTRA_OPERATOR = 31,
	EXTRA_OPERAND = 32,
	NOT_INFIX = 33
};

struct Node{
	int num ;
	char ch ;
	bool mach ;
	Type type ;  // 123,1  +-*/,2  (),3	
	Node *next ;
};

typedef Node * NodePtr ;

struct Char{
	char ch ;
	Char *next ;
};

typedef Char * CharPtr ;

void Read(NodePtr &head){
	char temp ;
	if(scanf(" %c", &temp)!=EOF){
		head = new Node ;
		head->ch = temp ;
		head->next = NULL ;
		Read(head->next) ;
	}		
}

void SetType(NodePtr &head){
	if(head!=NULL){
		if(head->ch=='(')
			head->type = OPEN_PARENTHESES ;
		else if(head->ch==')')
			head->type = CLOSE_PARENTHESES ;
		else if(head->ch=='+'||head->ch=='*'||head->ch=='-'||head->ch=='/')
			head->type = OPERATOR ;
		else if(head->ch>=0 && head->ch<='9')
			head->type = NUMBER ;
		else
			head->type = ERROR ;
			
		SetType(head->next) ;
	}
}

void SetMach(NodePtr &head){
	if(head!=NULL){
		if(head->type==OPEN_PARENTHESES||head->type==CLOSE_PARENTHESES)
			head->mach = false ;
		SetMach(head->next) ;
	}
	
}

bool CheckCharacter(NodePtr head){
	if(head!=NULL){
		if(head->type==ERROR)
			return false ;
		else
			return CheckCharacter(head->next) ;
	}
	
	return true ;
	
}

bool CheckParentheses(NodePtr head, int &haveOpen){
	if(head!=NULL){
		if(head->ch=='('){
			haveOpen++ ;
		}
		
		else if(head->ch==')'){
			haveOpen-- ;
		}
		
		if(haveOpen<0)
			return false ;
		
		return CheckParentheses(head->next, haveOpen) ;			
	}
	
	if(haveOpen!=0)
		return false ;
		
	return true ;
}

bool CheckRule(NodePtr head, Type &lastType, ErrorType &errorType){
	if(head!=NULL){
		if(lastType==OPERATOR){
			if(head->type==NUMBER||head->type==OPEN_PARENTHESES){
				lastType = head->type ;
				return CheckRule(head->next, lastType, errorType) ;
			}
			
			else{
				errorType=EXTRA_OPERATOR ;
				return false ;
			}
		}
		
		else if(lastType==OPEN_PARENTHESES ){
			if(head->type==NUMBER||head->type==OPEN_PARENTHESES){
				lastType = head->type ;
				return CheckRule(head->next, lastType, errorType) ;
			}
			
			else{
				errorType=NOT_INFIX ;
				return false ;
			}
		}
		
		else if(lastType==CLOSE_PARENTHESES){
			if(head->type==OPERATOR||head->type==CLOSE_PARENTHESES){
				lastType = head->type ;
				return CheckRule(head->next, lastType, errorType) ;
			}
			
			else{
				errorType=EXTRA_OPERAND ;
				return false ;
			}
		}
		
		else if(lastType==NUMBER){
			if(head->type==NUMBER||head->type==OPERATOR||head->type==CLOSE_PARENTHESES){
				lastType = head->type ;
				return CheckRule(head->next, lastType, errorType) ;
			}
			
			else{
				errorType=EXTRA_OPERAND ;
				return false ;
			}
		}
		

	}

	return true ;
}

bool Check( NodePtr head, ErrorType &errorType ){
	int haveOpen = 0 ;
	Type lastType = OPERATOR ; 
	if(!CheckCharacter(head)){
		errorType = ERROR_CHARACTER ;
		return false ;
	}
	
	else if(!CheckParentheses(head, haveOpen)){
		if(haveOpen>0)
			errorType = EXTRA_OPEN_PARENTHESIS ;
		else if(haveOpen<0)
			errorType = EXTRA_CLOSE_PARENTHESIS ;
			
		return false ;
	}
	
	else if(!CheckRule(head, lastType, errorType)){
		return false ;
	}
	
	return true ;
}

void PrintError(NodePtr head, ErrorType errorType){
	NodePtr run ;
	run = head ;
	if(errorType == ERROR_CHARACTER ){
		cout<<"ERROR 1:" ;
		for(;run!=NULL;run = run->next) {
			if(run->type = ERROR){
				cout<<run->ch ;
				break ;
			}
		}
		cout<<"is not a legitimate character."<<endl ;
	}
	
	else if(errorType == EXTRA_OPEN_PARENTHESIS)
		cout<<"ERROR 2:there is one extra open parenthesis." << endl ;
	else if(errorType == EXTRA_CLOSE_PARENTHESIS)
		cout<<"ERROR 2:there is one extra close parenthesis." << endl ;
		
	else if(errorType ==EXTRA_OPERATOR)
		cout<<"ERROR 3:there is one extra operator." << endl ;
	else if(errorType ==EXTRA_OPERAND)
		cout<<"ERROR 3:there is one extra operand." << endl ;
	else if(errorType == NOT_INFIX)
		cout<<"Error 3: it is not infix in the parentheses."<< endl ;
}

void SetNum(NodePtr head, NodePtr &infix){
	int num ;
	if(head!=NULL){
		if(head->type==NUMBER){
			if(infix==NULL){
				infix = new Node ;
				infix->next = NULL ;
				num = int(head->ch) -48 ;
				infix->num = num ;
				infix->type = head->type ;
				SetNum(head->next, infix) ;
			}
			
			else{
				num = int(head->ch) ;
				infix->num = infix->num*10 + num -48 ;
				SetNum(head->next, infix) ;
			}	
		}
		
		else{
			if(infix==NULL){
				infix = new Node ;
				infix->next = NULL ;
				infix->ch = head->ch ;
				infix->type = head->type ;
				SetNum(head->next, infix->next) ;
			}
			
			else{
				SetNum(head, infix->next) ;
			}
		}			
	}
}

void Postfix(NodePtr infix, CharPtr &ch, int &have, bool &first){
	CharPtr temp = NULL;
	if(infix!=NULL){
		if(infix->type==NUMBER) {
			if(!first)
				cout<<"," ;
			else
				first = false ;
			cout<<infix->num ;
			if(ch!=NULL){
				if(ch->ch=='*'||ch->ch=='/'){
					cout<<","<<ch->ch ;
					temp = ch ;
					ch = ch->next ;
					free(temp) ;
				}
			}				
		}
		
		else{
			if(infix->ch=='('){
				have++ ;
				temp = new Char ;
				temp->ch = infix->ch ;
				temp->next = ch ;
				ch = temp ;				
			}
			
			else if(infix->type == OPERATOR){
				if(infix->ch=='+'||infix->ch=='-'){
					if(ch!=NULL){
						if(ch->ch=='+'||ch->ch=='-'){
							cout<<","<<ch->ch ;
							temp = ch ;
							ch = ch->next ;
							free(temp) ;
						}						
					}
				}
				
				temp = new Char ;
				temp->ch = infix->ch ;
				temp->next = ch ;
				ch = temp ;
				
			}
			
			else if(infix->ch==')'){
				while(have>0 && ch->ch!='(' && ch != NULL){
					temp = ch ;
					if(ch->ch!=')')
						cout<<","<<ch->ch ;
					ch = ch->next ;
					free(temp) ;
				}
				
				have-- ;
				temp = ch ;
				ch = ch->next ;
				free(temp) ;
			}
		}
		
		Postfix(infix->next, ch, have, first) ;
	}
	
	else{
		while(ch!=NULL){
			temp = ch ;
			cout<<","<<ch->ch ;
			ch = ch->next ;
			free(temp) ;
		}
		
		cout<<endl ;
	}

		


}


int main(int argc, char** argv) {
	int input = 0 ;
	int have = 0 ;
	NodePtr head = NULL ;
	NodePtr infix = NULL ;
	NodePtr run ;
	CharPtr ch = NULL;
	cout<<endl<<"( 0 : Quit ; 1 : Work )"<<endl ;
	cin>>input ;

	while(input!=0){
		bool first = true ;
		cout<<"input infix :" ;	
		Read(head) ;
		SetType(head) ;
		SetMach(head) ;
	
		ErrorType errorType ;
		if(!Check(head, errorType))
			PrintError(head, errorType) ;
		else {
			cout<<"It is a legitimate infix expression."<< endl ;
		
			SetNum(head, infix) ;
			run = infix ;	
			
			Postfix(infix, ch, have, first) ;
		}
		
		free(infix) ;
		infix = NULL ;
		free(ch) ;
		ch = NULL ;
		free(head) ;
		head = NULL ;
		cout<<endl<<"( 0 : Quit ; 1 : Work )"<<endl ;			
		cin>>input ;
	}
}
