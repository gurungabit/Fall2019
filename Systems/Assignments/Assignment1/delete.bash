#!/bin/bash
read -p "Enter a course department code and number: " dept_code course_num
declare -u course=$dept_code
file_path="./data/$course$course_num.crs"
if [ ! -f $file_path ]; then
    echo "ERROR: course not found"
    exit 1
else
    echo -e "read dept_code dept_name \n
    read course_name \n
    read course_sched course_start course_end \n
    read course_hour \n
    read course_size \n
    export course_name
" > read_file.sh
    chmod 700 read_file.sh
    source ./read_file.sh < $file_path
    rm ./data/$course$course_num.crs
    echo "course number was successfully deleted"
    echo [$(date +%m/%d/Y)] DELETED: $dept_code $course_num $course_name >> ./data/queries.log
    
    rm ./read_file.sh
fi