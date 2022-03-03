###
 # @Date: 2021-11-28 19:28:03
 # @LastEditTime: 2021-11-28 19:57:49
 # @FilePath: /ve280/ve280/project5/call-test/test.sh
### 
echo "compiling"
g++ call.cpp -o call.out
g++ -fsanitize=address call.cpp -o memorycall.out
rm -rf myans diff leak
mkdir myans diff leak
for i in $(seq 0 5)
do  
    ./call.out < call-test/$i.in > myans/$i.out
    diff -q myans/$i.out call-test/$i.out
    if [ $? = 0 ]; then 
        echo "test $i: Accept"
    else 
        echo "test $i: Fail"
        diff myans/$i.out call-test/$i.out > diff/$i.diff
    fi
    ./memorycall.out < call-test/$i.in > leak/$i.out
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
    rm -rf myans call.out memorycall.out
else 
    echo "some failed"
fi 


