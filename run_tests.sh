EXEC=$1
TMP_OUT=$2

for i in {0..4..1}; do
  testname=$(printf "%01d" $i)
  time $EXEC < test/$testname.in > $TMP_OUT
  if ! diff -qwB test/$testname.out $TMP_OUT &>/dev/null; then
    echo "Test $testname failed"
  else
    echo "Test $testname passed"
  fi
done
rm $TMP_OUT
