# Math64 - Half Automated

This directory was created by copying `math32` and using `sed -e 's/32/64/g'
-i.bak ./*` to convert all occurrences of 32. Needless to say, this command is
not really refined and is confirmed to have a large list of false positives. So
whenever regenerating math64, iterate over all `math64/*.go` files and undo all
conversion that _do not make sense_.
