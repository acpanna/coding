#!/bin/sh

echo "INSERT INTO solution (host, rel, seed, scale, delta, beta, deep, sec, loop, sol, prec, vts, rnd, heu, prune, cvp, map, test, time) VALUES ('${1}', '${2}', '${3}', '${4}', '${5}', '${6}', '${7}', '${8}', '${9}', '${10}', '${11}', '${12}', '${13}', '${14}', '${15}', '${16}', '${17}', '${18}', '${19}');" | mysql -u rasa rasa
