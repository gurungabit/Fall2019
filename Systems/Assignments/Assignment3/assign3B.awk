BEGIN{temp="nope" 
      temp2="Nope"
      time=0}
  {
    if(match($1, temp))
    {
      temp="NOPE"
    }
    else
    {
      print "User: " $1
      temp=$1
    }
      printf("%12s","");
      for(i = 8; i<=NF; i++)
      {
        printf("%s ", $i);
      }
      printf("\n");
      if($5 ~ /[A-Z].*/)
      {
            if(match($1, temp2))
            {
              temp2="NOPE"
            }
            else
            {
              old=$5
              oldline=$0
              temp2=$1
            }
      }
      else
      {
        if($5 > time)
        {
          time=$5
          new=$5
          newline=$0
        }
      }
  }
END{
        printf("\n");
        print "Earliest Start Time :" 
        print oldline
        printf("\n");
        print "Latest Start Time :" 
        print newline
}
