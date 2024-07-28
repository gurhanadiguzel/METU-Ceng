import requests

from flask import Flask


app = Flask(__name__)


@app.route("/")
def main():
    nextPort = requests.get("http://localhost:10000?currentContainer=2").content.decode(
        "utf-8"
    )
    address = "http://localhost:" + nextPort
    response = requests.get(address).content.decode("utf-8")
    return "Replica Container 2 \n" + response


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=9002, debug=True)
