#!/bin/bash
read -p "Enter Department code: " dept_code
read -p "Enter Department name: " dept_name
read -p "Enter Course number: " course_num
read -p "Enter Course name: " course_name
read -p "Enter Course meeting days: " course_sched
read -p "Enter Course start date: " course_start
read -p "Enter Course end date: " course_end
read -p "Enter Course credit hour: " course_hour
read -p "Enter Course enrollment: " course_size
declare -u course=$dept_code
file_path="./data/$course$course_num.crs"
if [ ! -f $file_path ]; then
    echo "ERROR: course not found"
    exit 1
else
    echo -e "read dept_code dept_name
read old_course_name
read old_course_sched old_course_start old_course_end
read old_course_hour
read old_course_size
export old_dept_code 
export old_dept_name
export old_course_name
export old_course_sched
export old_course_start
export old_course_end
export old_course_hour
export old_course_size
" > file_read.sh
    chmod 700 file_read.sh
    source ./file_read.sh < $file_path
    if [ -z "$dept_name" ]; then
        dept_name=$old_dept_name
    fi
    if [ -z "$course_name" ]; then
        course_name=$old_course_name
    fi
    if [ -z "$course_sched" ]; then
        course_sched=$old_course_sched
    fi
    if [ -z "$course_start" ]; then
        course_start=$old_course_start
    fi
    if [ -z "$course_end" ]; then
        course_end=$old_course_end
    fi
    if [ -z "$course_hour" ]; then
        course_hour=$old_course_hour
    fi
    if [ -z "$course_size" ]; then
        course_size=$old_course_size
    fi
    
    echo $dept_code $dept_name > data/$course$course_num.crs
	echo $course_name >> data/$course$course_num.crs
	echo $course_sched $course_start $course_end >> data/$course$course_num.crs
	echo $course_hour >> data/$course$course_num.crs
	echo $course_size >> data/$course$course_num.crs
    echo [`date`] UPDATED: $dept_code $course_num $course_name >> ./data/queries.log
    
    rm ./file_read.sh
fi