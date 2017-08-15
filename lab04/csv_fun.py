import csv
def write_to_csv(filename,data):
    with open('example.csv','a') as csv_out:
        writer = csv.writer(csv_out)
        writer.writerow(data)
    
def print_from_csv(filename):
   with open('example.csv','r') as csv_in:
        reader = csv.reader(csv_in)
        for row in reader:
            print(row)
    
