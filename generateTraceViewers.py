#!/usr/bin/env python 

import os

TRACE_DIR = "traces"
PHP_DIR = "php"
OUTPUT_DIR = "traces"

PHP_TRACE_VIEWER_FILENAME = "traceViewer.php"

TRACE_EXTENSION = ".trace2048"

for filename in os.listdir(TRACE_DIR):
	if filename.endswith(TRACE_EXTENSION):
		tracePath = ".." + os.sep + TRACE_DIR + os.sep + filename
		outputPath = ".." + os.sep + OUTPUT_DIR + os.sep + filename.replace(TRACE_EXTENSION, ".html")
		os.system("cd %s; php %s %s > %s" % (PHP_DIR, PHP_TRACE_VIEWER_FILENAME, tracePath, outputPath))

