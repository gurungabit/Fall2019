#!/bin/bash
if [ $# -lt 4 ]; then
    echo "Usage: $0 requires at least 4 parameters"
    exit 1    
fi 
data=$1

if [ -d $4 ]; then
  rm -rf ./$4
fi
mkdir output
  
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
" > gread_file.sh
    chmod 700 gread_file.sh
for file in $data/*; do
    echo -e ${file##*/} > gcrsname.txt
    num=`sed -E 's/([A-Z]{0,3})([0-9]{4})\.crs/\2/g' gcrsname.txt`
    rm gcrsname.txt
if [[ $file =~ ([A-Z]{0,3})([0-9]{4})\.crs ]]; then
    source ./gread_file.sh < $file
    if [[ $course_size > 50 ]]; then
      if [ $# -eq 6 ]; then
        gawk -f generatesed.awk -v "_code=$dept_code" -v "d_name=$dept_name" -v "c_name=$course_name" -v "_num=$num" -v "_start=$course_start" -v "_end=$course_end" -v "_hour=$course_hour" -v "_size=$course_size" -v "date=$3" -v "left=$5" -v "right=$6" $file > gsedfile.sed  
      else
        gawk -f generatesed.awk -v "_code=$dept_code" -v "d_name=$dept_name" -v "c_name=$course_name" -v "_num=$num" -v "_start=$course_start" -v "_end=$course_end" -v "_hour=$course_hour" -v "_size=$course_size" -v "date=$3" -v "left="\\\\[\\\\["" -v "right="\\\\]\\\\]"" $file > gsedfile.sed        
      fi
      sed -f gsedfile.sed $2 > ./output/$dept_code$num.warn
    fi
else
    echo "ERROR: not a .crs file"
    exit 1
fi
done
rm gread_file.sh gsedfile.sed