#!/bin/bash
read -p "Please enter Department Code: " dept_code
read -p "Please enter Department Name: " dept_name
read -p "Please enter Course Number: " course_num
read -p "Please enter Course Name: " course_name 
read -p "Please enter Course Schedule: " course_sched 
read -p "Please enter Course Start Date: " course_start
read -p "Please enter Course End Date: " course_end
read -p "Please enter Course Credit Hour: " course_hour
read -p "Please enter initial Course enrollment: " course_size
declare -u code=$dept_code
filename=$code$course_num.crs
mkdir -p data
if [ -f data/$filename ]
then
	echo ERROR: course already exist
else
	echo $dept_code $dept_name > data/$filename
	echo $course_name >> data/$filename
	echo $course_sched $course_start $course_end >> data/$filename
	echo $course_hour >> data/$filename
	echo $course_size >> data/$filename
fi
