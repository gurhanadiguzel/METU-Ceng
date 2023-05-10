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
% Many thanks to our student TA, Tugba Tumer

% salad_type/2
salad_type([], vegan).
salad_type([H|R], vegan):- not(not_vegan(H)), salad_type(R, vegan).
salad_type([], vegetarian).
salad_type([H|R], vegetarian):- not(not_vegetarian(H)), salad_type(R, vegetarian).
salad_type(_, omnivorous):- true.



% person_can_eat/3
person_can_eat(Person, SaladList, Salad):- 
    member(Salad, SaladList), 
    (
        (vegan(Person), salad_type(Salad, vegan)); 
        (vegetarian(Person), salad_type(Salad, vegetarian));
        (omnivorous(Person))
    ).



% count_per_type/2
count_per_type(SaladList, TypeList):- 
    count_per_type_helper(SaladList, ToBeFixed),
    flatten(ToBeFixed, CanBeZeros),
    % you can implement your own delete predicate to remove the salad types with zero count
    % or you can use delete/3 (https://www.swi-prolog.org/pldoc/doc_for?object=delete/3)
    delete(CanBeZeros, [_, 0], TypeList).

% helpers for count_per_type/2
count_the_type(_, [], 0).
count_the_type(Type, [[Type, _]|R], N):- 
    !, 
    count_the_type(Type, R, N1), 
    N is N1 + 1.
count_the_type(Type, [_|R], N):- 
    count_the_type(Type, R, N).

flatten(ToBeFixed, [[vegan, Count1], [omnivorous, Count2], [vegetarian, Count3]]):- 
    count_the_type(vegan, ToBeFixed, Count1),
    count_the_type(omnivorous, ToBeFixed, Count2),
    count_the_type(vegetarian, ToBeFixed, Count3),
    !. 

count_per_type_helper([H|R], [[X,1]|NewList]):- 
    salad_type(H, X),
    !,
    count_per_type_helper(R, NewList).
count_per_type_helper([], []).




% possible_order_options/3
possible_order_options(Person, OrderString, ItemList):- 
    atom_chars(OrderString, OrderList),
    make_salad_from_list(OrderList, ItemList),
    person_can_eat_simple(Person, ItemList),
    check_duplicates(ItemList).

% helpers for possible_order_options/3
person_can_eat_simple(Person, Salad):- 
    (
        (vegan(Person), salad_type(Salad, vegan));
        (vegetarian(Person), salad_type(Salad, vegetarian));
        (omnivorous(Person))
    ).
make_salad_from_list([Ch|R], [Item|R1]):- 
    (
        (Ch = b, base(Item));
        (Ch = p, protein(Item));
        (Ch = t, topping(Item)); 
        (Ch = c, condiment(Item));
        (Ch = s, sauce(Item))
    ), 
    make_salad_from_list(R, R1).
make_salad_from_list([], []). 

check_duplicates([X|R]):- 
    not(member(X, R)), 
    check_duplicates(R).
check_duplicates([]).



