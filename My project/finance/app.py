import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    products = db.execute("SELECT * from products where username = (SELECT username from users where id = ?)", session["user_id"])
    total_value = db.execute("SELECT cash from users where id = ?", session["user_id"] )

    return render_template("index.html", products = products, total_value = round(total_value[0]["cash"],2))



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        buy = request.form.get("buy")
        share = request.form.get("share", type=int)

        #check if symbol is correct
        symbol = lookup(buy)
        if not symbol:
            return apology("Please write correct symbol", 403)

        #check if share are positive and if not blank
        elif not share:
            return apology("Please provide your input the number of share you require", 403)

        elif share < 0:
            return apology("Please input stocks in positive integers", 403)

        total_val = share * symbol["price"]
        price = symbol["price"]


        name = db.execute("SELECT username from users where id = ?",  session["user_id"])

        bal = db.execute("SELECT cash from users where id = ?",   session["user_id"])
        psymbol = db.execute("SELECT symbol from products where username = ?",  name[0]["username"] )

        if total_val > bal[0]["cash"]:
            return apology("balance not sufficient", 403)
        flag = 0
        for row in psymbol:
            if row["symbol"] == symbol["symbol"]:
                flag = 1
                print("flag")

        new_bal = bal[0]["cash"] - total_val
        db.execute("UPDATE users SET cash = ? where id = ?", new_bal, session["user_id"])

        if flag == 0:
            dates = datetime.datetime.now()
            total = round(total_val,2)
            db.execute("INSERT INTO products (username, symbol, name, share, price, total, date) VALUES(?, ?, ?, ?, ?, ?, ?)", name[0]["username"], symbol["symbol"], symbol["name"], share, price, total, dates)
        else:
            shr = db.execute("SELECT share from products where username = ?", name[0]["username"])
            total = db.execute("SELECT total from products where username = ?", name[0]["username"])
            sums = round(total[0]["total"] +  total_val,2)
            total_shr = shr[0]["share"] + share
            dates = datetime.datetime.now()
            db.execute("UPDATE products SET share = ?, total = ?, date = ? where symbol = ?", total_shr , sums, dates, symbol["symbol"])
            flag = 0
        return redirect("/")


    return render_template("buy.html")




@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    buy = db.execute("SELECT * from products where username = (SELECT username from users where id = ?)", session["user_id"])
    sell = db.execute("SELECT * from sell where username = (SELECT username from users where id = ?)", session["user_id"])

    return render_template("history.html", buy = buy, sell = sell)
    #return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        quote = request.form.get("quote")
        symbol = lookup(quote)

        if not symbol:
            return apology("symbol not exist!!", 403)

        #return the list of quotes
        return render_template("quoted.html", symbols = symbol)

    #return apology("TODO")
    return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        #checking if the user provide correct inputs
        if not name:
            return apology("must provide username", 403)

        users = db.execute("SELECT * FROM users")

        for names in users:
            if names["username"] == name:
                return apology("username already exist!!", 403)

        if not password:
            return apology("must provide password", 403)

        if not confirmation:
            return apology("must provide confirmation password", 403)

        if password != confirmation:
            return apology("password is not macthing", 403)

        pwd = generate_password_hash(password)

        db.execute("INSERT INTO users (username,hash) VALUES(?,?)", name, pwd)

        return redirect("/login")

    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    #global variable
    symbol = db.execute("SELECT symbol from products where username = (SELECT username from users where id = ?)", session["user_id"])

    if request.method == "POST":
        share = request.form.get("share")
        sell = request.form.get("sell", type=int)

        if share == "Shares":
            return apology("Enter number of share")


        if not sell:
            return apology("Enter number of share",403)

        elif sell < 0:
            return apology("Please input positive number", 403)

        symbols = lookup(share)
        curr_price = sell * symbols["price"]

        #checking if you have enough share
        name = db.execute("SELECT username from users where id = ?", session["user_id"])
        current_share = db.execute("SELECT share FROM products where symbol = ?  AND username = ?", share , name[0]["username"])
        if  sell > current_share[0]["share"]:
            return apology("TOO MANY SHARES!!", 403)

        #update cash
        cash = db.execute("SELECT cash from users where username = ?", name[0]["username"] )
        final_price = cash[0]["cash"] + curr_price
        db.execute("UPDATE users SET cash = ? where username = ?",  final_price, name[0]["username"])


        #update new share
        new_share = current_share[0]["share"] - sell
        db.execute("UPDATE products SET share = ? where symbol = ? AND username = ?", new_share, share, name[0]["username"])
        total_shr = db.execute("SELECT total FROM products where symbol = ?  AND username = ?", share , name[0]["username"])
        total = curr_price - total_shr[0]["total"]
        db.execute("UPDATE products SET total = ? where symbol = ? AND username = ?", total, share, name[0]["username"])



        #insert into new table
        date = datetime.datetime.now()
        sold = -(sell)
        db.execute("INSERT into sell (username, symbol, price, share, date) VALUES(?,?,?,?,?)",name[0]["username"], share, symbols["price"], sold, date)

        val = 0
        db.execute("DELETE FROM products WHERE share = ?", val)
        return redirect("/")

    return render_template("sell.html", symbol = symbol)
    #return apology("TODO")
