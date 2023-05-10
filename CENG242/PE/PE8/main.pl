:- module(main, [is_movie_directed_by/2, total_awards_nominated/2, all_movies_directed_by/2, total_movies_released_in/3, all_movies_released_between/4]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE
%movie(Name, Director, Year, OscarNoms, EmmyNoms, GoldenGlobeNoms).

is_movie_directed_by(Title, Director) :- 
    movie(Title, Director, _, _, _, _).

total_awards_nominated(Title, Nominations) :- 
    movie(Title, _, _, Oscar, Emy, Golden) , Nominations is Oscar + Emy+ Golden .

all_movies_directed_by(Director, Movies) :- 
    findall(Title, movie(Title, Director, _, _, _, _) , Movies).

total_movies_released_in([], Year, 0).

total_movies_released_in([Head|Tail], Year, Count):-  
    movie(Head, _, Year1, _, _, _),
    Year1 \= Year,
    total_movies_released_in( Tail, Year, Count).
    
total_movies_released_in([Head|Tail], Year, Count):-  
    movie(Head, _, Year1, _, _, _),
    Year1 =:= Year,
    total_movies_released_in( Tail, Year, Count1),
    Count is Count1+1.

all_movies_released_between([],MinYear, MaxYear, []).

all_movies_released_between([Head|Tail], MinYear, MaxYear, [Head|Res]) :-
    movie(Head, _, Year1, _, _, _), 
    Year1 =< MaxYear,
    Year1 >= MinYear,
    all_movies_released_between(Tail, MinYear, MaxYear, Res).

all_movies_released_between([Head|Tail],MinYear, MaxYear, MoviesBetweenYears):-
    movie(Head, _, Year1, _, _, _), 
    Year1 > MaxYear,
    all_movies_released_between(Tail, MinYear, MaxYear, MoviesBetweenYears).

all_movies_released_between([Head|Tail],MinYear, MaxYear, MoviesBetweenYears):-
    movie(Head, _, Year1, _, _, _), 
    Year1 < MinYear,
    all_movies_released_between(Tail, MinYear, MaxYear, MoviesBetweenYears).