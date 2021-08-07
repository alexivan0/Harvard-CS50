import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    #history = db.execute("SELECT * FROM history WHERE user_id = ? GROUP BY symbol", session["user_id"])
    #print(history)
    #cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    #balance = cash
    #for row in history:
        #row["price"] = lookup(row["symbol"])["price"]
        #row["total"] = row["price"] * row["shares"]
        #balance += row["total"]
        #print(row)
    #return render_template("index.html", history = history, cash = cash, balance = balance)
    portofolio = db.execute("SELECT * FROM portofolio WHERE user_id = ?", session["user_id"])
    cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    balance = cash
    for row in portofolio:
        row["price"] = lookup(row["symbol"])["price"]
        row["total"] = row["price"] * row["shares"]
        balance += row["total"]
    return render_template("index.html", portofolio = portofolio, cash = cash, balance = balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        if lookup(request.form.get("symbol")) == None:
            return apology("Invalid Symbol")
        usercash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        requiredcash = lookup(request.form.get("symbol"))["price"] * int(request.form.get("shares"))
        if usercash < requiredcash:
            return apology("Not enough money")
        else:
            newbalance = usercash - requiredcash
            datetime = db.execute("SELECT datetime('now')")[0]["datetime('now')"]
            db.execute("UPDATE users SET cash = ? WHERE id = ?", newbalance, session["user_id"])
            db.execute("INSERT INTO history (user_id, symbol, name, shares, price, total, transacted) VALUES (?, ?, ?, ?, ?, ?, ?)", session["user_id"], request.form.get("symbol"), lookup(request.form.get("symbol"))["name"], request.form.get("shares"), lookup(request.form.get("symbol"))["price"], (-1 * requiredcash), datetime)
            checksymbol = db.execute("SELECT * FROM portofolio WHERE user_id = ? AND symbol = ?", session["user_id"], request.form.get("symbol"))
            checkuser = db.execute("SELECT * FROM portofolio WHERE user_id = ? ", session["user_id"])
            print(checksymbol)
            print(checkuser)
            print(session["user_id"])
            print(request.form.get("symbol"))
            if checksymbol:
                newshares = checksymbol[0]["shares"] + int(request.form.get("shares"))
                db.execute("UPDATE portofolio SET shares = ? WHERE user_id = ? AND symbol = ?", newshares, session["user_id"], checksymbol[0]["symbol"])
                #db.execute("UPDATE portofolio SET cash = ? WHERE user_id = ? AND symbol = ?", newbalance, session["user_id"], checksymbol[0]["symbol"])
            else:
                db.execute("INSERT INTO portofolio (user_id, symbol, name, shares) VALUES (?, ?, ?, ?)", session["user_id"], request.form.get("symbol"), lookup(request.form.get("symbol"))["name"], request.form.get("shares"))
            flash("Bought!")
            return redirect("/")


@app.route("/history")
@login_required
def history():
    history = reversed(db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"]))
    return render_template("history.html", history = history)



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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = lookup(request.form.get("symbol"))
        if symbol == None:
            return apology("Invalid Symbol")
        return render_template("quoted.html", symbol = symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    else:
        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))
        rows = db.execute("SELECT * from users WHERE username = ?", username)
        if not request.form.get("username"):
            return apology("Username required")
        elif len(rows) != 0:
            return apology("Username already exists")
        elif not request.form.get("password"):
            return apology("Password required")
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password doesn't match")
        result = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password)
        #rows = db.execute("SELECT * from users WHERE username = ?", username)
        #session["user_id"] = rows[0]["id"]
        return redirect("/")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    shares = db.execute("SELECT symbol FROM portofolio WHERE user_id = ?", session["user_id"])
    if request.method == "GET":
        return render_template("sell.html", shares = shares)
    else:
        datetime = db.execute("SELECT datetime('now')")[0]["datetime('now')"]
        currentshares = db.execute("SELECT * FROM portofolio WHERE user_id = ? AND symbol = ?", session["user_id"], request.form.get("symbol"))[0]["shares"]
        askedshares = int(request.form.get("shares"))
        usercash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        sellcash = lookup(request.form.get("symbol"))["price"] * int(askedshares)
        newshares = currentshares - askedshares
        newbalance = usercash + sellcash
        if currentshares == askedshares:
            db.execute("DELETE FROM portofolio WHERE user_id = ? AND symbol = ?", session["user_id"], request.form.get("symbol"))
        elif currentshares < askedshares:
            return apology("Not enough shares!")
        else:
            db.execute("UPDATE portofolio SET shares = ? WHERE user_id = ? AND symbol = ?",newshares, session["user_id"], request.form.get("symbol"))
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newbalance, session["user_id"])
        db.execute("INSERT INTO history (user_id, symbol, name, shares, price, total, transacted) VALUES (?, ?, ?, ?, ?, ?, ?)", session["user_id"], request.form.get("symbol"), lookup(request.form.get("symbol"))["name"], (-1 * askedshares), lookup(request.form.get("symbol"))["price"], sellcash, datetime)
        flash("Sold!")
        return redirect("/")

@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def changepassword():
    """Change passord"""
    if request.method == "GET":
        return render_template("changepassword.html")
    else:
        userid = session["user_id"]
        oldpassword = request.form.get("oldpassword")
        newpassword = request.form.get("newpassword")
        confirmpassword = request.form.get("confirmpassword")
        currentpassword = db.execute("SELECT * FROM users WHERE id = ?", userid)[0]["hash"]
        if not check_password_hash(currentpassword, oldpassword):
            return apology("Incorrect current password")
        if not newpassword:
            return apology("Password can't be empty")
        elif newpassword != confirmpassword:
            return apology("Passwords don't match")
        elif check_password_hash(currentpassword, newpassword):
            return apology("New password can't be the same as old password")
        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(newpassword), userid)
        flash("Password changed!")
        return redirect("/")



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
