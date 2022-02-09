# Checker.py

import os

i = 0

while os.path.exists("in%d" % i):
	os.system("cat in%d | ./main >check%d" % (i, i))

	rec = open("check%d" % i, "r")
	ans = open("out%d" % i, "r")

	recCtx = rec.read().strip('\n')
	ansCtx = ans.read().strip('\n')

	rec.close()
	ans.close()

	if recCtx != ansCtx:
		print("Test #%d: Wrong Answer" % i)
		print(("Expected: \n%s" % ansCtx) + "\n")
		print(("Received: \n%s" % recCtx) + "\n")
		break

	print("Test #%d: Accepted" % i)
	i += 1