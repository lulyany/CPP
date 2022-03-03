###
 # @Date: 2021-11-28 16:33:16
 # @LastEditTime: 2021-11-28 19:58:00
 # @FilePath: /ve280/ve280/project5/rpc-test/test.sh
### 

echo "compiling"
g++ calc.cpp -o calc.out
g++ -fsanitize=address calc.cpp -o memorycalc.out
rm -rf myans diff leak
mkdir myans leak diff
for i in $(seq 0 7)
do  
    ./calc.out < rpc-test/$i.in > myans/$i.out
    diff -q myans/$i.out rpc-test/$i.out
    if [ $? = 0 ]; then 
        echo "test $i: Accept"
    else 
        echo "test $i: Fail"
        diff myans/$i.out rpc-test/$i.out > diff/$i.diff
    fi
    ./memorycalc.out < rpc-test/$i.in > leak/$i.out
    if [ $? = 0 ]; then 
        echo "test $i: no leak"
        rm -rf leak/$i.out
    else 
        echo "test $i: memory leak"
    fi
done
rmdir diff leak
if [ $? = 0 ]; then 
    echo "all passed"
    rm -rf myans calc.out memorycalc.out
else 
    echo "some failed"
fi 

