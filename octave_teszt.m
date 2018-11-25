printf("a mátrix: \n")
#B = [4,5,10,12;6,7,8,-5;3,4,8,18;5,6,7,1;]
B = C = [1,6,5,4,5,6;7,5,3,0,7,3;3,4,5,6,0,1;12,15,1,-1,4,-6;8,8,7,10,12,19;6,5,1,2,4,5;]

printf("a mátrix redukált lépcsős alakja: \n")
rref(B)

printf("a mátrix inverze: \n")
inv(B)

printf("a mátrix rangja: %d, nyoma: %d\n", rank(B), trace(B))

printf("a mátrix determinánsa: %d\n", det(B))
