#include "LinkedList.h"

typedef void (*Accept_Callback)(char*, char*) ;

struct State;
typedef struct State* Automata;

typedef struct {
	char input;
	Automata to;
} Transition;

struct State {
	Accept_Callback onAccept;
	LinkedList transitions;
	Automata errorState;
};

Automata Automata_New(Automata, Accept_Callback);
void Automata_Run(Automata, char*);