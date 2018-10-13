!/bin/bash

if [-e "./bin/code"]; then
	./code $1
else
	echo "First run compile.sh to compile the code"
fi