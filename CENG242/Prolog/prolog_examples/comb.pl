select(E, [E|R],R).
select(E, [H|R], [H|R2]) :- select(E, R, R2).

combin(_,[], 0). % 0 combination is empty
% all N combin of remain . is also in comb .
combin([_|R], Res , N) :- N > 0, combin(R,Res ,N).
% N -1 combin of remain . add H
combin([H|R], [H|Res], N) :- N > 0, M is N-1,
                            combin(R,Res ,M).

permut(_,[], 0). % 0 permutation is empty
% for all elements H of L, permute remaining .
permut(L, [H|RP], N) :- N > 0, M is N-1,
                        select(H, L, Rem), permut(Rem, RP, M).