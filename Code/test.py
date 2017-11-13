import random
R = 1000
r = 20
a = []
for i in range(R):
	a1,a2,a3 = random.randint(1,999),random.randint(1,999),random.randint(1,999)
	a.append([a1,a2,a3])
	if len(a)%100 == 0:
		d = len(a)
		for i in range(r):
			x = random.randint(0,d)
			a.append(a[x])
with open('data.txt', 'w') as FF:
	for i in range(len(a)):
		s=str(a[i][0]) + ' ' + str(a[i][1]) + ' ' + str(a[i][2]) + '\n'
		FF.write(s);
# for i in range(len(a)):
	# a[i] = tuple(a[i])
# print len(list(set(a))), len(a)