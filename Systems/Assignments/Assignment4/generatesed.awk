BEGIN {RS=""}
{
    printf("s~%sdept_code%s~%s~g\n",left,right,_code);
    printf("s~%sdept_name%s~%s~g\n",left,right,d_name);
    printf("s~%scourse_name%s~%s~g\n",left,right,c_name);
    printf("s~%scourse_start%s~%s~g\n",left,right,_start);
    printf("s~%scourse_end%s~%s~g\n",left,right,_end);
    printf("s~%scredit_hours%s~%s~g\n",left,right,_hour);
    printf("s~%snum_students%s~%s~g\n",left,right,_size);
    printf("s~%scourse_num%s~%s~g\n",left,right,_num);
    printf("s~%sdate%s~%s~g\n",left,right,date);
}