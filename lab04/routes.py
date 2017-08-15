from flask import Flask, redirect, render_template, request, url_for
from server import app, user_input
import csv
from csv_fun import *
@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form["name"]
        zID = int(request.form["zID"])
        description = request.form["desc"]
        user_input.append([name, zID, description])
        #with open('example','a') as csv_out:
             #writer = csv.writer(csv_out)
             #writer.writerow([name, zID, description])
        write_to_csv("example.csv",[name, zID, description])
         
        return redirect(url_for("hello"))
    return render_template("index.html")

@app.route("/Hello")
def hello():
    print_from_csv("example.csv")
    
    return render_template("hello.html", all_users=user_input) 
