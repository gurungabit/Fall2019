import os
import glob
import shutil
import sys
import re
# check if all required arguments is passed in
if len(sys.argv) < 5:
    print("Usage: " + sys.argv[0] + " <dirname> <template> <date> <output>")
    sys.exit(1)
# check if output directory exits if it does REMOVE IT for new output
if os.path.isdir(sys.argv[4]):
    shutil.rmtree(sys.argv[4])
# check if output directory exits if it does not, create a new one!
if not os.path.isdir(sys.argv[4]):
    os.mkdir(sys.argv[4])

# check that the first arg is a directory
if not os.path.isdir(sys.argv[1]):
    print(sys.argv[1] + " is not a directory")
    sys.exit(1)


# assign read data from data file to dictionary keys
def assign_data(line, course_num, date):
    data = {'dept_code': line[0].split(" ")[0],
            'dept_name': ' '.join(str(separated) for separated in line[0].split()[1:]),
            'course_name': line[1].strip("\n"),
            'course_start': ' '.join(str(separated) for separated in line[2].split()[1:2]),
            'course_end': ' '.join(str(separated) for separated in line[2].split()[2:]),
            'credit_hours': line[3].strip("\n"),
            'num_students': line[4].strip("\n"),
            'course_num': str(course_num),
            'date': str(date) + "\n"}
    return data


# loop through files in directory
def assignment5(data_files):
    out_name = ""
    # For each file, read
    for file in data_files:
        # extracting file name so that I can use it to name the output file
        # finds names of files and adds it to a list based on the regex
        name = re.findall("[A-Z]{2,3}[0-9]{4}", file)
        # loops through the list and extracts just the name without extension
        for names in name:
            out_name = names
            # extracts last 4 number so that I can use it as the course_num
        course_num = int(re.search(r'[0-9]{4}', file).group())
        try:
            # Open the data file for reading
            with open(file, 'r') as f:
                # Read each line into a list
                lines = f.readlines()
                # Assign the read data into a dictionary
                item = assign_data(lines, course_num, sys.argv[3])
                # if num_students is greater then 50 open the template and replace accordingly
                if int(item['num_students']) > 50:
                    # open template file for reading
                    template_file = open(sys.argv[2], 'r')
                    # read whole file and assign it to a string
                    template = template_file.read()
                    # close file since we already have a copy
                    template_file.close()
                    if len(sys.argv) <= 5:
                        left = "[["
                        right = "]]"
                    else:
                        left = sys.argv[5]
                        right = sys.argv[6]
                    # replace defined pattern with items from the dictionary
                    Template = template.replace(left + "dept_code" + right, item['dept_code'])
                    template = Template
                    Template = template.replace(left + "dept_name" + right, item['dept_name'])
                    template = Template
                    Template = template.replace(left + "course_name" + right, item['course_name'])
                    template = Template
                    Template = template.replace(left + "course_start" + right, item['course_start'])
                    template = Template
                    Template = template.replace(left + "course_end" + right, item['course_end'])
                    template = Template
                    Template = template.replace(left + "credit_hours" + right, item['credit_hours'])
                    template = Template
                    Template = template.replace(left + "num_students" + right, item['num_students'])
                    template = Template
                    Template = template.replace(left + "course_num" + right, item['course_num'])
                    template = Template
                    Template = template.replace(left + "date" + right, item['date'])
                    template = Template
                    # create output file with specific name in specific directory
                    path_filename = sys.argv[4] + "/" + out_name + ".warn"
                    # open output file for writing
                    output_name = open(path_filename, 'w')
                    # write the new replaced file
                    output_name.write(Template)
        except IOError:
            print("File could not be read or wrong file type")
        f.close()
    sys.exit()


# use glob and add each file from directory to a list
data_files = glob.glob(sys.argv[1] + "/*")
# print(data_files)
# modify the list so that only a file with matching pattern remains on the list
r = re.compile("data\\\\[A-Z]{2,3}[0-9]{4}.crs")
# filtering out the list according to the regex pattern above
new_list = list(filter(r.match, data_files))
# print(new_list)
assignment5(new_list)
