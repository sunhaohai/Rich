#!/bin/bash

if [ ! -n "$1" ]; then
    echo " usage:"
    echo "    ./auto.sh [testfilePath/ outputFilePath/ rightFilePath/] [./richPath]"
    echo " "
    echo "    ./auto.sh testfilePath/ outputFilePath/ rightFilePath/ ./richPath : 指定目录和指定rich"
    echo "    ./auto.sh testfilePath/ outputFilePath/ rightFilePath/ : 指定目录，默认使用auto.sh同目录的rich"
    echo "    ./auto.sh ./richPath : 指定rich，使用默认目录进行测试---[测试]"
    echo " "
    echo "   1.testfilePath   : 测试文件输入路径"
    echo "   2.outputFilePath : 输出文件路径"
    echo "   3.rightFilePath  : 正确的要对比的文件输入路径"
    echo "   3../richPath     : 默认与auto.sh同级目录（可选）"
    echo " "
    echo "    eg/test test: ./auto.sh test/testfile test/output ./test/rightfile"
    exit
fi

# set variable
OUT_FILE_NAME="dump"
RIGHT_FILE_NAME="right"
TEST_FILE_NAME="test"

# get absolute path
if [ ! -n "$2" ]; then
    # 默认输入文件路径
    TEST_FILE_PATH=./TestCase/
    # 默认输出文件路径
    OUT_FILE_PATH=./Dump/
    # 默认正确的文件路径
    RIGHT_FILE_PATH=./PreDump/
else
    # 输入文件路径
    TEST_FILE_PATH=$(pwd)/$1
    # 输出文件路径
    OUT_FILE_PATH=$(pwd)/$2
    # 正确的文件路径
    RIGHT_FILE_PATH=$(pwd)/$3
fi

rm -rf ${OUT_FILE_PATH}/*


# 记录成功或者失败的数量
let SUCCESS_INDEX=0
let FAIL_INDEX=0
# tag
let success=0


# 循环导入文件，进行测试
let index=0
for m in $(ls ${TEST_FILE_PATH})
do
	#echo ${TEST_FILE_PATH}/${m}
	let index+=1
    echo "正在输入第${index}个测试样例..."
    if [ ! -n "$4" ]; then
        ./rich "${OUT_FILE_PATH}dump${index}.txt" < "${TEST_FILE_PATH}/test${index}.txt"
    else
        $4 "${index}" < ${TEST_FILE_PATH}/${m}
    fi

done


# 生成测试函数
cd ./diff
make -s
cd ..

# 记录成功或者失败测试的个数
echo "开始分析输出文件"
let index=0
for m  in $(ls ${OUT_FILE_PATH})
do
    let index+=1
	echo ${OUT_FILE_PATH}/"dump${index}.txt" ":" ${RIGHT_FILE_PATH}/"right${index}.txt"
    echo "正在测试第${index}个测试样例..."
	./diff/diff ${OUT_FILE_PATH}/"dump${index}.txt" ${RIGHT_FILE_PATH}/"right${index}.txt"
    let state=$?
	# echo "结果：$?"
	if [ ${state} -eq  ${success} ]
    then
        SUCCESS[${SUCCESS_INDEX}]=${index}
        let SUCCESS_INDEX+=1
    else
        FAIL[${FAIL_INDEX}]="${index}:${state}"
        let FAIL_INDEX+=1
    fi
done

# 删除测试函数和中间文件
cd ./diff
make clean -s
cd ..

# 打印测试结果
if [ ${FAIL_INDEX} -eq  ${success} ]
then
    echo ""
    echo "${SUCCESS_INDEX}个样例全部通过～～～"
    echo "   \ 0 . 0 /"
    echo ""
else
    echo "测试成功样例总数：${SUCCESS_INDEX}个"
    echo "测试成功样例: ${SUCCESS[@]}"
    echo "测试失败样例总数：${FAIL_INDEX}个"
    echo "测试失败样例: ${FAIL[@]}"
    echo -e "成功率：%\c"
    echo "scale=2;${SUCCESS_INDEX} * 100 / ${index} " | bc
fi



