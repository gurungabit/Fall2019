#!/bin/bash
read -p "Enter a department code and course number: " code num
declare -u course=$code
file_path="./data/$course$num.crs"
if [ ! -f $file_path ]; then
    echo "ERROR: course not found"
    exit 1
else
    echo -e "read dept_code dept_name \n
    read course_name \n
    read course_sched course_start course_end \n
    read course_hour \n
    read course_size \n

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
    
    echo Course department: $dept_code $dept_name
    echo Course number: $num
    echo Course name: $course_name
    echo Scheduled days: $course_sched
    echo Course start: $course_start
    echo Course end: $course_end
    echo Credit hour: $course_hour
    echo Enrolled Students: $course_size
    
    rm ./read_file.sh
fi

