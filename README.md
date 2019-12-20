# made_2019_tsp
_Solution of travelling salesman problem for metric graphs using MST and exact approaches

## "An approximate solution to the metric traveling salesman problem for undirected graphs".
* Find an approximate solution to the metric traveling salesman problem (TSP) for a full undirected graph (on a plane) using a minimal spanning tree (MST).
* Evaluate the quality of approximation on a random set of points normally distributed on a plane with the variance equal to 1. Get a normally distributed set of points using the Box-Muller transform.
* For a fixed `N`, the number of graph vertices, run the approximation quality estimation several times. Calculate the mean and standard deviation of the approximation quality for a given `N`.
* Run this experiment for all `N` in a certain range, for example, `[2, 10]`.
* Automate the execution of experiments.
* The solution requires a reasonable organization of the code using several files. Each class should has its own header and implementation files.

## How to build
* `cmake`

## How to run
* `tsp [-m <minimum_number_of_vertices>] [-M <maximum_number_of_vertices>] [-r <experiment_repetitions_count>]`, you can skip any parameter you want. 
* By default, `<minimum_number_of_vertices>` is 2, `<maximum_number_of_vertices>` is 10, `<experiment_repetitions_count>` is 20
* Examples: `tsp -m 2 -M 5`, `tsp -m 5 -M 10 -r 10`

## Results

~~~
> tsp
Using parameters:
 - Minimum number of vertices (--min_size or -m): 2
 - Maximum number of vertices (--max_size or -M): 10
 - Number of test repetitions (--requests or -r): 20

 Experiment for comparison of the approximate MST-based and the exact solutions
                          for Travelling Salesman Problem
---------------------------------------------------------------------------------
| #vertices | #repetitions | Mean cost of approx./exact | Std. of approx./exact |
---------------------------------------------------------------------------------
|         2 |           20 |                     1.0000 |                0.0000 |
|         3 |           20 |                     1.0000 |                0.0000 |
|         4 |           20 |                     1.0199 |                0.0372 |
|         5 |           20 |                     1.0887 |                0.1066 |
|         6 |           20 |                     1.1582 |                0.1028 |
|         7 |           20 |                     1.1450 |                0.1421 |
|         8 |           20 |                     1.1673 |                0.0839 |
|         9 |           20 |                     1.2334 |                0.0979 |
|        10 |           20 |                     1.3049 |                0.0975 |
---------------------------------------------------------------------------------
| All cases |    All cases |                     1.1241 |                0.1325 |
---------------------------------------------------------------------------------
~~~
Desription of the table:
* `#vertices` - the number of vertices used in a single experiment
* `#repetitions` - the number of randomly generated full metric graphs to solve TSP problem for them in a single experiment and to compute the rest two columns
* `Mean cost of approx./exact` - the mean ratio of the cost of approximate MST-based solution to the cost of exact solution
* `Std. of approx./exact` - the standard deviation of ratios
* In the last line, the last two columns are calculated for ratios from all experiments

## Conclusions

Here you can see that for number of vertices ranging from 2 to 10 the approximate MST-based solution is up to ~1.3 times worse than the exact solution, and we know that the theoretical bound is not more than 2 times. The standard deviation tends to decrease with the increase of graph size.
