# fnframe

## comparing the execution speeds over different containers  

This is a C++ program to check how well we can reduce no of new() calls from the execution.

In my opinion, We can use a vector with sufficient capacity (DEPTH) reserved.
It gave quite comparable results as that of my custom stack ( stack with a custom container supporting placement new ).
Benefits of the vector approach:
smaller code, we don't need to write a custom container,
We don't need to specify size of the underlying container (in case we go with fixed size container, second last approach)

Below table summarizes execution timings for each approach.

compiler used 	g++ v 13.1, , with Release mode set.
COUNT = 100'000'000	


		| | Time in milliseconds		
file	|Approach	| DEPTH = 40	| DEPTH = 400 |	DEPTH = 4000
list.cpp|	Existing, calling new on every iteration|	2400	| 2550	| 2650
vector.cpp	| vector with reserved capacity as DEPTH |	610	| 710 |	795
vector.cpp |	commenting line that does vector.reserve() |	595	| 705	| core dumped
stack.cpp	| std stack (with underlying default container as deque ) |	1460	| 1710	| 1850
stack_using_vector.cpp |	std stack (with underlying  container as vector )	 | 600	| 710 |	core dumped
custom_stack.cpp |	std stack with custom container (fixed sized array) (which uses placement new)	 | 575	650	710
custom_stack_with_buckets.cpp |	std stack with custom container (vector of fixed sized array) (which uses placement new)	| 670 |	870	| 880
