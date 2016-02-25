
Nishil Prajapati
1316771
--------------------------------------------------------------------------------------------------------------
Please run these codes on Unix machine only. Do not use putty for this.

Its a concurrent server not a sequential server.

To run client program:
./a.out 127.0.0.1 PORTNUM 1 <Clientnum> -> To read the memory

./a.out 127.0.0.1 PORTNUM 2 <Clientnum> <Numvalue> -> To create the memory and fill the numbers

./a.out 127.0.0.1 PORTNUM 3 <Clientnum> 0 -> to read the sum( Do not forget to put 0, Its a part of the code)

./a.out 127.0.0.1 PORTNUM 4 -> To terminate the server. If you have executed A number of clients except this one  then you have to 
this client which has argument 4  A times.


To run Server program:
./server PORTNUM


