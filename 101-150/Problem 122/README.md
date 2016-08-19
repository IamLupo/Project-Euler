The most naive way of computing n15 requires fourteen multiplications:

	n × n × ... × n = n15

But using a "binary" method you can compute it in six multiplications:

	n × n = n2
	n^2 × n^2 = n4
	n^4 × n^4 = n8
	n^8 × n^4 = n12
	n^12 × n^2 = n14
	n^14 × n = n15

However it is yet possible to compute it in only five multiplications:

	n × n = n2
	n^2 × n = n3
	n^3 × n^3 = n6
	n^6 × n^6 = n12
	n^12 × n^3 = n15

We shall define m(k) to be the minimum number of multiplications to compute nk;
for example m(15) = 5.

For 1 ≤ k ≤ 200, find ∑ m(k).
