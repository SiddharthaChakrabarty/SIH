% Facts
parent(john, mary).
parent(john, david).
parent(susan, mary).
parent(susan, david).
parent(mary, lucas).
parent(mary, emma).
parent(david, anna).

% Rules
mother(X, Y) :- parent(X, Y), female(X).
father(X, Y) :- parent(X, Y), male(X).
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
grandchild(X, Y) :- grandparent(Y, X).

% Facts for gender
female(mary).
female(susan).
female(anna).
female(emma).
male(john).
male(david).
male(lucas).