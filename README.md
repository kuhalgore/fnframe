# fnframe

## comparing the execution speeds over different containers  

This is a C++ program to check how well we can reduce no of new() calls from the execution.

In my opinion, We can use a vector with sufficient capacity (DEPTH) reserved.
It gave quite comparable results as that of my custom stack ( stack with a custom container supporting placement new ).
Benefits of the vector approach:
smaller code, we don't need to write a custom container,
We don't need to specify size of the underlying container (in case we go with fixed size container, second last approach)

Below table summarizes execution timings for each approach.

![Alt text](table1.jpg?raw=true "Execution times comparison")

