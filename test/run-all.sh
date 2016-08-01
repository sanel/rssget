#!/bin/sh

run_test() {
	echo "# Running $1..."
	./$1 > $1.got 2>&1

	if [ -f $1.expected ]; then
		diff -up $1.got $1.expected
		# cleanup if good
		if [ $? -eq 0 ]; then
			cat $1.got
			rm $1.got
		else
			export RSSGET_TESTS_STATUS=1
		fi
	else
		echo -e "\e[1;31m*** Missing ***\e[0m $1.expected - skipping '$1' test..."
	fi
}

for test in `ls *-test`; do
	run_test $test
	echo ""
done

exit $RSSGET_TESTS_STATUS
