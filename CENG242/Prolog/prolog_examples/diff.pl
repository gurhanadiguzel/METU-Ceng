/* simple symbolic differentiation
  use as:  diff(x^3/(1+x), x, R).
*/

diff(A, A, 1) :- !.
diff(A, _, 0) :- number(A).
diff(-A, B, -C) :- diff(A, B, C).
diff(A+B, C, R) :- diff(A, C, D), diff(B, C, E), simp(D+E, R).
diff(A-B, C, R) :- diff(A, C, D), diff(B, C, E), simp(D-E, R).
diff(A*B, C, R) :- number(A), diff(B, C, D), simp(A*D, R),!.
diff(A*B, C, R) :- diff(A, C, E), diff(B, C, D), simp(A*D+B*E, R).
diff(A/B, C, R) :- diff(A*B^(-1), C, D), R = D.
diff(A^B, C, R) :- number(B), diff(A, C, D), simp(B*A^(B-1)*D, R).
diff(log(A), B, C*A^ -1) :- diff(A, B, C).

/* test if all components are
   numbers. So it can be evaluated */

ok(X) :- number(X),!.
ok(A):- A =.. [_,T1,T2] , ok(T1),ok(T2).
ok(A) :- A =.. [_,T1] , ok(T1).

/* evaluate if all numeric expression */
s(X,Y) :- ok(X),!,Y is X. 

/* eliminate multiply by 1 and -1 */
s(A*1,Y) :- simp(A,Y),!.
s(1*A,Y) :- simp(A,Y),!.
s(-1*A,-Y) :- simp(A,Y),!.

/* eliminate 0 add */
s(A+0,Y) :- simp(A,Y),!.
s(0+A,Y) :- simp(A,Y),!.
s(A-0,Y) :- simp(A,Y),!.
s(0-A,-Y) :- simp(A,Y),!.

/* eliminate 1 power and 0 power */
s(A^1,AE) :- simp(A,AE),!.
s(1^_,1) :- !.
s(_^0,1) :- !.
s(X,X).

simp(A*B,R) :- simp(A,AE),simp(B,BE),s(AE*BE,R),!.
simp(A+B,R) :- simp(A,AE),simp(B,BE),s(AE+BE,R),!.
simp(A-B,R) :- simp(A,AE),simp(B,BE),s(AE-BE,R), !.
simp(A^B,R) :- simp(A,AE),simp(B,BE),s(AE^BE,R),!.
simp(X,X).
