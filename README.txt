Compiled with:
g++ *.cpp -o rpc

---------------------EXAMPLES TO TRY IN LINUX TERMINAL---------------------

./rpc -p
OPENS PROMPT WITH BASIC INSTRUCTIONS AND ASKS FOR POSTFIX CALCULATION


./rpc 2 2 +
RUNS CALCULATION 2+2


echo 2 2 + | ./rpc
SAME AS ABOVE


----------------------------BASIC INSTRUCTIONS----------------------------

This program calculates PostFix expressions.
All the operators must be separated by a space.
Valid operators are:
+
-
*
/
^
% (modulo)
v (square root)
a (average)
s (sum all)
x (flip latest two)