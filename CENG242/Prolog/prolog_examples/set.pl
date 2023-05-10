%%%% Set operations %%%%%%

% union(+SetA, +SetB, ?Result)   Result <- SetA U SetB 
union([],T,T).
union([A|Rem],T, Z) :- member(A,T),!, union(Rem,T,Z). 
	% if member, skip since it comes from setB
union([A|Rem],T, [A|Z]) :- union(Rem,T,Z).	      
	% if not member (due to cut above) include A in result

%---------------------------


% intersection(+SetA, +SetB, ?Result)   Result <- SetA * SetB 
intersection([],_,[]).
intersection([A|Rem],T, [A|Z]) :- member(A,T),!, intersection(Rem,T,Z).
	% if member A is included in Result and rest skipped
intersection([_|Rem],T, Z) :- intersection(Rem,T,Z).
	% if not member (due to cut above) intersect the rest.

%---------------------------

% difference(+SetA, +SetB, ?Result)   Result <- SetA - SetB 
difference(A,[],A).
difference(A,[B|BRest], Res ) :- insert(B,ARem, A), ! ,
	%if B is a member of A too, exclude (see insert below)
			difference(ARem,BRest,Res).

difference(A,[_|BRest], Res ) :- difference(A,BRest,Res).
% if A is not a member of setB (due to cut above), include it 


%---------------------------

% insert(?Value, ?Remainder, ?List)  Value inserted at different positions
%	of Remainder or for all Value,Remainder combinations
%	of List
insert(X,R,[X|R]).
insert(X,[A|Rem],[A|List]) :- insert(X,Rem, List).


%---------------------------

% setequal(+setA, +setB)    setA =:= setB (assume lists are not ordered)
setequal([],[]).
setequal([A|Arem],B) :- insert(A,BRem,B), setequal(Arem,BRem).


%---------------------------

% subset(+setA, +setB)   
subset([],_).
subset([A|ARest],B)   :- insert(A,BRem,B), subset(ARest,BRem).

%---------------------------


% powerset(+SetA, ?Powerset)  
powerset([],[[]]).
powerset([A|ARest],Res) :- powerset(ARest,PoARest),
		% PoARest gives members without A in result
	 inserttermall(A,PoARest,PoARest,Res).
		% insert A to all elements of 
		% PoARest combine with PoARest

% inserttermall(+Term, +List, +Inlist, ?ResList)
% insert Term to all elements of List (which is a list of lists)
% result is prepended to InList resulting list will be ResList
% insertermall(x, [[a],[a,b],[b,c]], [[w]], R) will set R to
% [[x,a],[x,a,b],[x,b,c],[w]]
inserttermall(_,[],R,R).
inserttermall(T,[S|SRest],Inp,Res) :- 
	inserttermall(T,SRest,[[T|S]|Inp],Res).
