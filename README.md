# CS 225 Final Project - FA2020
ibw2-mgraton2-allenhw2-jhmao2

## Overview
For our final project, our group has decided to use the Pennsylvania Road Map dataset, found on the [Stanford Dataset Collection](http://snap.stanford.edu/data/roadNet-PA.html) website. This data set is based off of the road map network within the state of Pennsylvania. Our algorithm implementations allow you to find the shortest distance between two nodes (intersections of roads or endpoints).

## Running the Project

To compile the executable, ensure that you are on EWS, in the current directory, and type `make` in the terminal.

Then, to run the program, type the following: `./finalproj [start node index] [end node index] [abbreviated algorithm name] [input file name]`
 
For example, to find the shortest distance between node 3 and node 39, using Dijkstras algorithm and input file 'small_cases.txt', type the following::

`./finalproj 0 7458 d ShortPAData.txt`

Or, to find the shortest distance between node 1 and node 5, using A* search algorithm and input file 'test_case.txt', type the following:

`./finalproj 1 5 a test_case.txt`

Argument      | Options
------------- | -------------
Start Node Index  | Integer from 0 to largest node ID
End Node Index  | Integer from 0 to largest node ID
Algorithm Name  | "d" for Dijkstra's algorithm or "a" for A* search algorithm
Input File Name  | Any text file resides in the current directory

## The Data
Although our usage of this repo is focused on PA road networks, it can be used with different datasets following the same format. Each line should be the weight of the edge, the from node ID, and the to node ID, separated with spaces. Additionally, there must be an empty line at the end of the dataset.

## Presentation
[This](https://youtu.be/2dhoVGAgC08) is the link to our final project presentation. 
