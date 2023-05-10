subset([] ,[]).
subset(Rsub,[_|R]):- subset(Rsub,R).
subset([H|Rsub],[H|R]):- subset(Rsub,R).
