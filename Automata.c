#include "Automata.h"

Automata Automata_New(Automata errorState, Accept_Callback onAccept) {
	Automata new = malloc(sizeof(struct State));
	new->onAccept = onAccept;
	new->transitions = LinkedList_New();
	new->errorState = errorState;
	return new;
}

void Automata_Run(Automata automata, char* input) {
	char* start = input;

	while (*input) {
		LinkedList trans = automata->transitions->next;
		while (trans && ((Transition*) trans->data)->input != *input)
			trans = trans->next;

		if (trans) {
			automata = ((Transition*) trans->data)->to;
			input++;
			continue;
		}

		if (automata->onAccept)
			automata->onAccept(start, input - 1);

		start = ++input;

		if (automata->errorState)
			automata = automata->errorState;
	}

	if (automata->onAccept)
		automata->onAccept(start, input);
}