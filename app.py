from flask import Flask
from a import *
app = Flask(__name__)

@app.route("/")
def main():
    return extract("ben")


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=3000)