import random

left = 100000000000000000000000000000000000
right = 1000000000000000000000000000000000000000000

nums1 = [random.randint(left, right) for _ in range(10)]
nums2 = [random.randint(left, right) for _ in range(10)]

with open('sums.txt', 'w') as sums_file, open('diffs.txt', 'w') as diffs_file, open('prods.txt', 'w') as prods_file:
	for n1, n2 in zip(nums1, nums2):
		print(str(n1) + " " + str(n2) + " " + str(n1 + n2), file=sums_file)
		print(str(n1) + " " + str(n2) + " " + str(n1 - n2), file=diffs_file)
		print(str(n1) + " " + str(n2) + " " + str(n1 * n2), file=prods_file)