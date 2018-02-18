input_no = int(input("Enter the number of inputs: "))

inputs = [int(input("Enter the input "+str(i)+": ")) for i in range(1, input_no+1)]
weights = [1] * input_no
sum = 0

for i in range(0, input_no):
	sum = sum + weights[i]*inputs[i]

if sum<input_no:
	print("AND Value:\t 0")
else:
	print("AND Value:\t 1")
	
if sum>0:
	print("OR Value:\t 1")
else:
	print("OR Value:\t 0");