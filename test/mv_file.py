import os

files = ["Dump/dump"+str(i)+".txt" for i in range(1,54)]
outfiles = ["PreDump/predump"+str(i)+".txt" for i in range(1,54)]
for i in range(53):
    os.system("cp {} {}".format(files[i], outfiles[i]))
