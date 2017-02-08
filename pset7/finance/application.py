from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/", methods=["GET"])
@login_required
def index():
    
    if request.method == "GET":
        
        portfolio_all = db.execute("SELECT symbol from portfolio where id = :user_id", user_id=session["user_id"])
        
        portfolio_dict = {}
        
        overall_value = 0
        
        for item in portfolio_all:
            symbol = item["symbol"]
            quote = lookup(symbol)
            name = quote["name"]
            curr_price = quote["price"]
            
            num_shares = db.execute("SELECT symbol, num_shares FROM portfolio WHERE id = :user_id GROUP BY symbol", user_id=session["user_id"])
            lengthOfSharesDict = len(num_shares)
            
            for i in range(0, lengthOfSharesDict):
                if num_shares[i]['symbol'] == symbol:
                    num_shares = num_shares[i]['num_shares']
                    break

            total = curr_price * num_shares
            overall_value = overall_value + total
            total = usd(total)
            
            portfolio_dict[symbol] = [symbol, name, num_shares, curr_price, total]
            
        cash_available = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
        users_cash = cash_available[0]['cash']
        overall_value = overall_value + users_cash
        users_cash = usd(users_cash)
        overall_value = usd(overall_value)

        return render_template("index.html",portfolio_all=portfolio_dict, cash=overall_value, users_cash=users_cash)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    
    if request.method == "POST":
        
        # grab the symbol user inputted, check if it's real, grab relatant data using lookup
        symbol = request.form.get("symbol")
        
        try:
            num_shares = float(request.form.get("num_shares"))
        except:
            return apology("Please only input the symbol in the symbol section")

        if num_shares <= 0:
            return apology("Please input a positive number of shares")
        quote = lookup(symbol)
        if not quote:
            return apology("That was an incorrect symbol, please try again")
            
        
        cost_of_shares = num_shares * quote["price"]    
        user_id = session["user_id"]
            
        cash_available = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)
        users_cash = cash_available[0]['cash']
        if users_cash < cost_of_shares:
            return apology("sorry, you don't have enough cash to purchase that")
        
        purchase_shares = db.execute("UPDATE portfolio SET num_shares = num_shares + :num_shares WHERE symbol = :symbol and id = :user_id", num_shares=num_shares, symbol = quote["symbol"], user_id = user_id)
        if not purchase_shares:
            purchase_shares = db.execute("INSERT into portfolio(id, symbol, num_shares) VALUES(:user_id, :symbol, :num_shares)", user_id = user_id, symbol = quote["symbol"], num_shares = num_shares) 

        update_cash = db.execute("UPDATE users SET cash = cash - :cost_of_shares WHERE id= :user_id", cost_of_shares = cost_of_shares, user_id = user_id)
        
        cost_of_shares = usd(cost_of_shares)
        #update the history table
        db.execute("INSERT INTO history(id, symbol, action, num_shares, price) VALUES(:user_id, :symbol, 'buy', :num_shares, :price)", user_id=user_id, symbol=quote["symbol"], num_shares=num_shares, price=cost_of_shares)
        
        flash('Shares bought successfully!', 'text-success')
        return redirect(url_for("index"))
    
    return render_template('buy.html')
    
@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """User changes their password"""
    
    if request.method == "POST":
        
        # ensure user inputted information in all fields
        if not request.form.get("current_password"):
            return apology("please type your current password")
        if not request.form.get("current_password_retype"):
            return apology("please retype your current password")
        if not request.form.get("new_password"):
            return apology("please provide a new password")
        if not request.form.get("new_password_retype"):
            return apology("please retype your new password")
            
        # check if user inputted correct iterations of current and new pass    
        if request.form.get("current_password") != request.form.get("current_password_retype"):
            return apology("Your current and retyped current passwords do not match, please try again")
        if request.form.get("new_password") != request.form.get("new_password_retype"):
            return apology("Your new password and retyped new password do not match, please try again")
            
        # get current pass from database and check if user input is correct
        rows = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=session["user_id"])
        if not pwd_context.verify(request.form.get("current_password"), rows[0]["hash"]):
            return apology("Your password does not match what you typed in current password, please try again")
            
            
        # encrypt new pass for hash, keep the baddies out!
        hashedPass = pwd_context.encrypt(request.form.get("new_password"))
        
        # change user's password
        db.execute("UPDATE users SET hash = :hashedPass WHERE id = :user_id", hashedPass=hashedPass, user_id=session["user_id"])
        
        # success flash and redirect user to index landing page
        flash('Password changed successfully!', 'text-success')
        return redirect(url_for("index"))
    
    return render_template("password.html")
    
@app.route("/profile", methods=["GET", "POST"])
@login_required
def profile():
    """Profile page for user"""
    
    if request.method == "GET":
    
        user_info = db.execute("SELECT username, cash FROM users WHERE id = :user_id", user_id=session["user_id"])
        print(user_info)
        
        return render_template("profile.html", user_info=user_info)
    
    return redirect(url_for("password"))

@app.route("/history", methods=["GET"])
@login_required
def history():
    """Show history of transactions."""
    
    if request.method == "GET":
        
        # grab all user's date from history
        history_content = db.execute("SELECT * FROM history WHERE id = :user_id", user_id=session["user_id"])
    
        return render_template("history.html", history_content=history_content)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in.""" 

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    if request.method == "POST":
        
        # get the symbol the user wants
        symbol = request.form.get("symbol")
        
        # get the quote for the stock
        quote = lookup(symbol)
        
        # error check for a real symbol
        if not quote:
            return apology("incorrect symbol, ensure you are spelling the symbol correctly")
        
        # save the name, price and symbol
        stock_name = quote["name"]
        stock_price = quote["price"]
        stock_symbol = quote["symbol"]
        
        return render_template('quoted.html', name=stock_name, price=stock_price, symbol=stock_symbol)
        
    return render_template('quote.html')

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmPassword = request.form.get("confirmPassword")
        
        
        # error checking, empty username? empty pass or retyped pass? pass/retyped not the same?
        if not username:
            return apology("Please enter a valid username")
        elif not password:
            return apology("Please enter a password")
        elif not confirmPassword:
            return apology("Please retype your password")
        elif confirmPassword != password:
            return apology("Passwords did not match, please retry to register")
            
            
        # hash the pass! keep the baddies out
        hashedPass = pwd_context.encrypt(password)
        
        
        # Insert user into the database check if user already exists
        result = db.execute("INSERT INTO users(username, hash) VALUES(:username, :hash)", username = request.form.get("username"), hash = hashedPass)
        if not result:
            return apology("Sorry, that username is already registered")
            
            
        # grab user's info to get the id
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        
        # remember the user for the session to log them in
        session["user_id"] = rows[0]["id"]
    
        # redirect user to home page
        return redirect(url_for("index"))
        
        
    return render_template('register.html')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    
    if request.method == "POST":
        
        # grab user information, get the lookup of the symbol
        symbol = request.form.get("symbol")
        if not symbol.isalpha():
            return apology("Please only input the symbol in the symbol section")
            
        try:
            num_shares = float(request.form.get("num_shares"))
        except:
            return apology("Please only input the symbol in the symbol section")

        if num_shares <= 0:
            return apology("Please input a positive amount of shares")
        quote = lookup(symbol)
        if not quote:
            return apology("that wasn't a correct symbol, please try again")
        share_current_price = quote["price"]
            
        # check if the user actually owns that stock/amount of that stock
        users_current_stock = db.execute("SELECT num_shares FROM portfolio where id = :user_id and symbol = :symbol", user_id=session["user_id"], symbol=symbol)
        if not users_current_stock:
            return apology("You don't own any of that stock, please try again")
            
        users_current_stock = users_current_stock[0]["num_shares"]
        print(users_current_stock)
        if users_current_stock < num_shares:
            return apology("Sorry you don't own many shares that of that stock, please try again")
            
        
        # update portfolio and minus that stock and the amount (log as a negative sale)
        db.execute("UPDATE portfolio SET num_shares = num_shares - :num_shares WHERE symbol = :symbol and id = :user_id", num_shares=num_shares, symbol = quote["symbol"], user_id = session["user_id"])
        
        # update their cash - add stock price to their available cash
        db.execute("UPDATE users SET cash = cash + :price WHERE id = :user_id", price=share_current_price, user_id=session["user_id"])
        
        user_sell_all = share_current_price * num_shares
        user_sell_all = usd(user_sell_all)
        
        # add the transaction to the history table
        db.execute("INSERT INTO history(id, symbol, action, num_shares, price) VALUES(:user_id, :symbol, 'sell', :num_shares, :price)", user_id=session["user_id"], symbol=quote["symbol"], num_shares=num_shares, price=user_sell_all)
        
        # present flash message success! redirect to index landing page
        flash('Shares sold successfully!', 'text-success')
        return redirect(url_for("index"))

    return render_template('sell.html')
