#/usr/bin/python

import os,sys
import queue
import threading
import re

MAX = 256

class SearchInFile:
	def __init__(self, filepath):
		self.filepath = filepath
		self.pattern = "tencent-([\d]+)"

	def search(self, result):
		with open(self.filepath, "r") as f:
			file_content = f.read()
			subs = re.findall(self.pattern, file_content)
			for sub in subs:
				result[0] += int(sub)


class MyThread(threading.Thread):
	def __init__(self, files, result):
		self.files = files
		self.result = result
		threading.Thread.__init__(self)
	
	def run(self):
		while True:
			if self.files.qsize() > 0:
				searching = SearchInFile(self.files.get())
				searching.search(self.result)
			else:
				break

class Mscan:
	def start(self, localpath):
		files = queue.Queue()
		self.scan_file(files, localpath)
		threads = []
		scanResult = [0]
		threads_num = files.qsize() if files.qsize()<MAX else MAX
		for j in range(threads_num):
			threads.append(MyThread(files, scanResult))
		for x in threads:
			x.start()
		print(scanResult[0])
		return scanResult[0]

	def scan_file(self, files, localpath):
		for fn in os.listdir(localpath):
			if not os.path.isdir(fn):
				files.put(os.path.join(localpath, fn))
			else:
				self.scan_file(files, os.path.join(localpath, fn))

if __name__ == "__main__":	
	Mscan = Mscan()
	Mscan.start("/Users/emma/Work/alg/test/")
