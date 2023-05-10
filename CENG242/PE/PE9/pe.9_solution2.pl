% ===== KNOWLEDGE BASE =====

% vegan(Name), vegetarian(Name), and omnivorous(Name) predicates, 
% defining the diets of customers
vegan(chidi).
vegetarian(tahani).
omnivorous(eleanor).
omnivorous(jason).
% base(Name) predicate, options for salad base
base(lettuce).
% protein(Name) predicate, options for proteins
protein(smoked_turkey).
protein(hellim_cheese).
protein(smoked_tofu).
% topping(Name) predicate, options for toppings
topping(cucumber).
topping(tomato).
topping(pickled_onion).
topping(olive).
% condiment(Name) predicate, options for condiments
condiment(mustard).
condiment(mayonnaise).
condiment(ranch).
% sauce(Name) predicate, options for sauces
sauce(olive_oil).
sauce(lemon_juice).
sauce(balsamic_vinegar).
% not_vegan(Item) and not_vegetarian(Item) predicates, 
% defining dietary restrictions
not_vegetarian(Item) :- 
    member(Item, [smoked_turkey]), !.
not_vegan(Item) :- 
    not_vegetarian(Item), !;
    member(Item, [hellim_cheese,mayonnaise,ranch]), !.


% ===== IMPLEMENTATIONS =====

% salad_type/2
salad_type(ItemList, vegan) :-
    all_vegan(ItemList).
salad_type(ItemList, vegetarian) :-
    all_vegetarian(ItemList).
salad_type(_, omnivorous).

% helpers for salad_type/2
all_vegan([]).
all_vegan([H|T]) :-
    not(not_vegan(H)), all_vegan(T).
all_vegetarian([]).
all_vegetarian([H|T]) :-
    not(not_vegetarian(H)), all_vegetarian(T).


% person_can_eat/3
person_can_eat(Person, [Salad|_], Salad) :-
    (vegan(Person), salad_type(Salad, vegan));
    (vegetarian(Person), salad_type(Salad, vegetarian));
    (omnivorous(Person), salad_type(Salad, omnivorous)).
person_can_eat(Person, [_|Rest], Salad) :- person_can_eat(Person, Rest, Salad).


% count_per_type/2
count_per_type(SaladList, TypeMap) :- 
    type_list(SaladList, TypeList),
    map_of_types(TypeList, TypeList, RepeatedResults),
    % you can implement your own predicate to remove the repetitive terms
    % or you can use: 
    % list_to_set/2  (https://www.swi-prolog.org/pldoc/doc_for?object=list_to_set/2)
    list_to_set(RepeatedResults, TypeMap),
    !.

% helpers for count_per_type/2
map_of_types(_,[],[]).
map_of_types(FullList, [Type|T], [[Type, Count]|Acc]) :-
    % you can implement your own predicate to count terms
    % or you can use: occurrences_of_term/3 (https://www.swi-prolog.org/pldoc/doc_for?object=occurs%3Aoccurrences_of_term/3)
    occurrences_of_term(Type, FullList, Count),
    map_of_types(FullList, T, Acc).
type_list([],[]).
type_list([Salad|T], [Type|Rest]) :-
    salad_type(Salad,Type),
    type_list(T,Rest).


% possible_order_options/3
possible_order_options(Person, OrderString, ItemList) :-
    % atom_chars, given as hint in pdf
    atom_chars(OrderString, OrderList),
    (
        % is_set, given as hint in pdf
        (vegan(Person), vegan_order(OrderList, ItemList), is_set(ItemList));
        (vegetarian(Person), vegetarian_order(OrderList, ItemList), is_set(ItemList));
        (omnivorous(Person), omnivorous_order(OrderList, ItemList), is_set(ItemList))
    ).

% helpers for possible_order_options/3
vegan_order([],[]).
vegan_order([H|T], [Item|Rest]) :- 
    (
        (H == b, base(Item));
        (H == p, protein(Item));
        (H == t, topping(Item));
        (H == c, condiment(Item));
        (H == s, sauce(Item))
    ),
    not(not_vegan(Item)),
    vegan_order(T,Rest).

vegetarian_order([],[]).
vegetarian_order([H|T], [Item|Rest]) :- 
    (
        (H == b, base(Item));
        (H == p, protein(Item));
        (H == t, topping(Item));
        (H == c, condiment(Item));
        (H == s, sauce(Item))
    ),
    not(not_vegetarian(Item)),
    vegetarian_order(T,Rest).

omnivorous_order([],[]).
omnivorous_order([H|T], [Item|Rest]) :- 
    (
        (H == b, base(Item));
        (H == p, protein(Item));
        (H == t, topping(Item));
        (H == c, condiment(Item));
        (H == s, sauce(Item))
    ),
    omnivorous_order(T,Rest).


