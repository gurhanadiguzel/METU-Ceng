taketwo(A, B, [A|R] , Rem ) :- select(B, R, Rem).
taketwo(A, B, [H|R], [H|Rem]) :- taketwo(A, B, R, Rem).

% if top element evaluates to number, it is the result
findit([A|_],V,A) :- V is A.
% asymmetric ops.
findit(L,V,T) :- select(A,L,AR), select(B,AR,Rest),
        member(O,[-,//]), check(O,A,B), E =.. [O,A,B],
        findit([E|Rest],V,T).
% symmetric ops.
findit(L,V,T) :- taketwo(A,B,L,Rest),
        member(O,[+,*]),  E =.. [O,A,B],
        findit([E|Rest],V,T).
check(-,A,B) :- A>B.
check(//,A,B) :- 0 is A mod B.
