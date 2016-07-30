#!/bin/sh

run_test() {
	echo "# Running $1..."
	./$1 > $1.got 2>&1

	diff -up $1.got $1.expected

	# cleanup if good
	if [ $? -eq 0 ]; then
		cat $1.got
		rm $1.got
	else 
		export RSSGET_TESTS_STATUS=1
	fi
}

for test in `ls *-test`; do
	run_test $test
done

exit $RSSGET_TESTS_STATUS
