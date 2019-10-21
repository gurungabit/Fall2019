#!/bin/bash
read -p "Enter a course department code and number: " dept_code course_num
read -p "Enter an enrollment change amount: " amount

declare -u course=$dept_code
filename=$course$course_num.crs
file_path="./data/$filename"
if [ ! -f $file_path ]; then 
    echo "ERROR: course not found"
    exit 1
else
    echo -e "read dept_code dept_name
read course_name
read course_sched course_start course_end
read course_hour
read course_size
export dept_code 
export dept_name
export course_name
export course_sched
export course_start
export course_end
export course_hour
export course_size
" > read_file.sh
    chmod 700 read_file.sh
    source ./read_file.sh < $file_path
    size=$course_size
	echo $dept_code $dept_name > data/$filename
	echo $course_name >> data/$filename
	echo $course_sched $course_start $course_end >> data/$filename
	echo $course_hour >> data/$filename
	echo $((size + $amount)) >> data/$filename
    echo [`date`] ENROLLMENT: $dept_code $course_num $course_name changed by $amount>> ./data/queries.log

    rm ./read_file.sh
fi