expr --> var , [+] , expr .
expr --> var , [-] , expr .
expr --> [let] , defs , [in] , expr .
expr --> num . 
expr --> var . 
defs --> def , [:] , defs .
defs --> def .

def --> var , [=] , expr .

var([V|T],T) :- atom(V).
num([V|T],T) :- number(V).


expr(V+E) --> var(V) , [+] , expr(E) .
expr(V-E) --> var(V) , [-] , expr(E) .
expr(let(D,E)) --> [let] , defs(D) , [in] , expr(E) .
expr(N) --> num(N) . 
expr(V) --> var(V) . 
defs([D|DR]) --> def(D) , [:] , defs(DR) .
defs([D]) --> def(D) .

def(V=E) --> var(V) , [=] , expr(E) .

var(V,[V|T],T) :- atom(V).
num(V,[V|T],T) :- number(V).

parse(Inp,R) :- expr(R,Inp,[]).
