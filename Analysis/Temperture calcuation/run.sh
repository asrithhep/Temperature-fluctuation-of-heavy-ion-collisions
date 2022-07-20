for i in {0..9}
do
for j in {0..9}
do
num1="$i"
num2="$j"
func='fitting.C('
foo="${func}${num1},${num2})"
root -b -q $foo
done
done

