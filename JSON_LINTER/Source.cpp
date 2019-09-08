typedef enum {INIT,STRING,NUMBER,OBJECT,ARRAY,TRUE,FALSE,NULL}stateType;
enum eventForValue {QUOTES,NUMBER,LBRACE,LBRACKET,T,F,N ,OTHER};

typedef struct
{
	stateType nextState;
	void (*action)(void *);
}cellType;

			
cellType FSM[][] = { {QUOTES, string()} , {NUMBER, number()} , {LBRACE , object()} , {T , isTrue()} , {F,isFlase()}, {N, isNull()} , {OTHER,error()} };		//INIT